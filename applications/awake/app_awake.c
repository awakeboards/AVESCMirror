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

// Global variables for testing system
volatile bool aw_tst_enable = false;
volatile uint8_t aw_tst_throttle = 0;
volatile uint8_t aw_tst_mode = 0;

void app_custom_start(void) {
    // init throttle curves and settings
    aw_init_throttle();

    // init can communication
	comm_can_set_sid_rx_callback(tb_can_sid_callback);

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
		aw_handle_throttle(data_in[0], data_in[1]);
        tb_last_throttle_frame = chVTGetSystemTimeX();
		return true;
	case AW_CAN_TB_BOARD_ID:
		tb_id_requested = true;
		return true;
    case AW_CAN_TB_MBS_TYPE:
        // only configure the ones that can be changed
        //((app_configuration*) app_get_configuration())->app_awake.motor_type = data_in[0]; // not configurable
        ((app_configuration*) app_get_configuration())->app_awake.board_type = data_in[1];
        //((app_configuration*) app_get_configuration())->app_awake.shunt_type = data_in[2];
        conf_general_store_app_configuration((app_configuration*) app_get_configuration());
        return true;
    case AW_CAN_TB_AVESC_VERSION:
        {
            uint16_t version = VTYPE;
            comm_can_transmit_sid(AW_CAN_TB_AVESC_VERSION, (uint8_t*) &version, 2);
        }
        return true;
	default:
		return false;
	}
}

static void tb_send_state(void) {
	uint16_t MotorRPM = (uint16_t)(
			mc_interface_get_rpm() / (float) ERPM_DIVIDER);
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
    };
	comm_can_transmit_sid(AW_CAN_TB_MBS_TYPE, data_out, 3);
}

static void tb_handle_faults(void) {
	mc_fault_code fault = mc_interface_get_fault();
	if (fault != FAULT_CODE_NONE && fault != FAULT_CODE_OVER_VOLTAGE
			&& fault != FAULT_CODE_UNDER_VOLTAGE
			&& fault != FAULT_CODE_BOOTING_FROM_WATCHDOG_RESET) {
		comm_can_transmit_sid(AW_CAN_AVESC_FAULT_FRAME, (uint8_t *) &fault, 1);
	}
}
