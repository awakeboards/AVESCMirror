#include "app_awake.h"

// Threads
static THD_FUNCTION(aw_thread, arg);
static THD_WORKING_AREA(aw_thread_wa, 2048);

// Private variables
static volatile bool stop_now = true;
static volatile bool is_running = false;

static volatile bool tb_id_requested = false;
static volatile systime_t tb_last_throttle_frame = 0;

// Function prototypes
static void tb_send_state(void);
static void tb_send_id(void);
static void tb_send_mbs_type(void);
static void tb_handle_faults(void);
static bool tb_can_sid_callback(uint32_t id, uint8_t *data_in, uint8_t len);
static bool tb_can_eid_callback(uint32_t eid, uint8_t *data_in, uint8_t len);

// Global variables for testing system
volatile bool aw_tst_enable = false;
volatile uint8_t aw_tst_throttle = 0;
volatile uint8_t aw_tst_mode = 0;

void app_custom_start(void) {
    // init throttle curves and settings
    aw_init_throttle();

    // init can communication
	comm_can_set_sid_rx_callback(tb_can_sid_callback);
	comm_can_set_eid_rx_callback(tb_can_eid_callback);

	stop_now = false;
	chThdCreateStatic(aw_thread_wa, sizeof(aw_thread_wa), NORMALPRIO, aw_thread,
			NULL);
}

void app_custom_stop(void) {
	comm_can_set_sid_rx_callback(0);

	stop_now = true;
	while (is_running) {
		chThdSleepMilliseconds(1);
	}
}

void app_custom_configure(app_configuration *conf) {
    (void) conf;
}

void aw_set_current(float current) {
	static systime_t time_last = 0; // Holds last time this function was called
	static float current_old = 0;

	float dt = ST2MS(chVTGetSystemTimeX() - time_last) / 1000.0;
	if (dt > 0) {
		float dcurrent = (current - current_old) / dt; // A/s

		// Apply ramp limit only when increasing magnitude (moving away from zero)
		if ((fabsf(current) > fabsf(current_old)) && (fabsf(dcurrent) > AW_CURRENT_RAMP_LIMIT)) {
			current = current_old + copysignf(AW_CURRENT_RAMP_LIMIT, dcurrent) * dt;
		}
	}

	mc_interface_set_current(current);

	current_old = current;
	time_last = chVTGetSystemTimeX();
}

static THD_FUNCTION(aw_thread, arg) {
	(void) arg;

	chRegSetThreadName("Awake TB App");
	is_running = true;

    aw_led_indication indication;
	for (;;) {
		if (stop_now) {
			is_running = false;
			break;
		}

        // Check if HW is supported
        if(!aw_is_hw_supported()) {
            mc_interface_fault_stop(FAULT_CODE_OVER_TEMP_MOTOR, false, false); // FAULT_CODE_OVER_TEMP_MOTOR can't be reported, so we re-use this fault for AVESC_HW
        }

        indication = AW_LED_ON;

        // Send default states
		tb_send_state();
		tb_handle_faults();

        // TB ID handler
		if (tb_id_requested) {
			tb_send_id();
			tb_send_mbs_type();
			tb_id_requested = false;
		}

        // Check if test mode is active
        if (aw_tst_enable) {
            aw_handle_throttle(aw_tst_throttle, aw_tst_mode);
            indication = AW_LED_BLINK;
        }

        // Low level safety, if no throttle for 5s, cut-off throttle
        // Other safety mechanisms should catch this first
        if(chVTGetSystemTimeX() - tb_last_throttle_frame > MS2ST(5000)) {
            if (tb_last_throttle_frame > 0) { // disable throttle only if we got any throttle packets before
                aw_handle_throttle(0, AW_PM_SLOW);
                indication = AW_LED_OFF;
            } else {
                indication = AW_LED_BLINK;
            }
        }

        // LED main loop indication part 1
        if(indication == AW_LED_BLINK || indication == AW_LED_ON)
            ledpwm_set_intensity(LED_GREEN, 1);
		chThdSleepMilliseconds(20); // ~20 Hz main loop (first 20 ms sleep)

        // LED main loop indication part 2
        if(indication == AW_LED_BLINK || indication == AW_LED_OFF)
		    ledpwm_set_intensity(LED_GREEN, 0);
        chThdSleepMilliseconds(20); // ~20 Hz main loop (second 20 ms sleep)

		timeout_reset();
	}
}

static bool tb_can_sid_callback(uint32_t id, uint8_t *data_in, uint8_t len) {
	(void) len;

	switch (id) {
	case AW_CAN_TB_THROTTLE_FRAME:
        if (len == 3 && data_in[2] == true) {
            aw_handle_throttle(data_in[0], AW_PM_BRABUS);
        } else {
            aw_handle_throttle(data_in[0], data_in[1]);
        }
        tb_last_throttle_frame = chVTGetSystemTimeX();
		return true;
	case AW_CAN_TB_BOARD_ID:
		tb_id_requested = true;
		return true;
    case AW_CAN_TB_MBS_TYPE:
        // only configure the ones that can be changed
        //((app_configuration*) app_get_configuration())->app_awake.motor_type = data_in[0]; // not configurable
        ((app_configuration*) app_get_configuration())->app_awake.board_type = data_in[1];
        //((app_configuration*) app_get_configuration())->app_awake.shunt_type = data_in[2];  // not configurable
        if (len > 3) // for backwards compatibility we need to check length
            ((app_configuration*) app_get_configuration())->app_awake.locked = data_in[3];
        conf_general_store_app_configuration((app_configuration*) app_get_configuration());
        return true;
    case AW_CAN_TB_LOCK_CONTROL:
        if (len == 1) {
            ((app_configuration*) app_get_configuration())->app_awake.locked = data_in[0];
            conf_general_store_app_configuration((app_configuration*) app_get_configuration());
        } else if (len == 0) {
            uint8_t locked = ((app_configuration*) app_get_configuration())->app_awake.locked;
            comm_can_transmit_sid(AW_CAN_TB_LOCK_CONTROL, &locked, 1);
        }
        return true;
    case AW_CAN_TB_AVESC_VERSION:
        {
            uint16_t version = VTYPE;

            uint16_t features = AW_FEATURE_BASE;
            features |= AW_FEATURE_DIRECT_CURRENT_CONTROL;
            features |= AW_FEATURE_SET_CURRENT_LIMITS;

            uint8_t buff[4] = {0};

            memcpy(buff, &version, 2);
            memcpy(buff + 2, &features, 2);

            comm_can_transmit_sid(AW_CAN_TB_AVESC_VERSION, buff, 4);
        }
        return true;
    case AW_CAN_AVESC_SET_CURRENT_LIMITS:
        {
            int32_t ind = 0;
            float max_motor_current = (float) buffer_get_uint16(data_in, &ind) / 10.0f;
            float max_battery_current = (float) buffer_get_uint16(data_in, &ind) / 10.0f;
            ((volatile mc_configuration*) mc_interface_get_configuration())->l_current_max = max_motor_current;
            ((volatile mc_configuration*) mc_interface_get_configuration())->l_in_current_max = max_battery_current;
        }
        return true;
	default:
		return false;
	}
}

static bool tb_can_eid_callback(uint32_t eid, uint8_t *data_in, uint8_t len) { // NOLINT(readability-non-const-parameter)
    (void) len;
    (void) data_in;

    uint8_t id = eid & 0xFF;
    CAN_PACKET_ID cmd = eid >> 8;

    // EXT packet is addressed at this VESC
    if (id == 255 || id == app_get_configuration()->controller_id) {
        // if current, rpm or duty command is received, we consider it a throttle frame too
        // allowing alt mode where instead of AW_CAN_TB_THROTTLE_FRAME, direct current, duty or rpm control is possible
        if (cmd == CAN_PACKET_SET_CURRENT || cmd == CAN_PACKET_SET_RPM || cmd == CAN_PACKET_SET_DUTY) {
            tb_last_throttle_frame = chVTGetSystemTimeX();
        }
    }

    return false; // mark all packets as not processed, we "spectate" EXT packets only, not process them
}

static void tb_send_state(void) {
	uint16_t MotorRPM = (uint16_t)(
			mc_interface_get_rpm() / (float) AW_ERPM_DIVIDER);
	int16_t ESCTemperature = (int16_t) (mc_interface_temp_fet_filtered() * 1e1f);
	int16_t MotorTemperature = (int16_t) (mc_interface_temp_motor_filtered() * 1e1f);

	uint8_t data_out[8];
	data_out[0] = MotorRPM & 0xFF;
	data_out[1] = (MotorRPM >> 8) & 0xFF;
	data_out[2] = ESCTemperature & 0xFF;
	data_out[3] = (ESCTemperature >> 8) & 0xFF;
	data_out[4] = MotorTemperature & 0xFF;
	data_out[5] = (MotorTemperature >> 8) & 0xFF;
	data_out[6] = 0;
	data_out[7] = 0xFF;
	comm_can_transmit_sid(AW_CAN_MOTOR_MSG_FRAME, data_out, 8);
}

static void tb_send_id(void) {
	uint8_t data_out[5];
	for (uint8_t i = 0; i < 3; ++i) {
		uint32_t id_32 = STM32_UUID[i];

		memcpy(data_out, &id_32, 4);
		data_out[4] = i;

		comm_can_transmit_sid(AW_CAN_TB_BOARD_ID, data_out, 5);

		chThdSleepMilliseconds(5);
	}
}

static void tb_send_mbs_type(void) {
	uint8_t data_out[] = {
        app_get_configuration()->app_awake.motor_type,
        app_get_configuration()->app_awake.board_type,
        app_get_configuration()->app_awake.shunt_type,
        app_get_configuration()->app_awake.locked,
    };
	comm_can_transmit_sid(AW_CAN_TB_MBS_TYPE, data_out, 4);
}

static void tb_handle_faults(void) {
	mc_fault_code fault = mc_interface_get_fault();
	if (fault != FAULT_CODE_NONE && fault != FAULT_CODE_OVER_VOLTAGE
			&& fault != FAULT_CODE_UNDER_VOLTAGE
			&& fault != FAULT_CODE_BOOTING_FROM_WATCHDOG_RESET) {
		comm_can_transmit_sid(AW_CAN_AVESC_FAULT_FRAME, (uint8_t *) &fault, 1);
	}
}
