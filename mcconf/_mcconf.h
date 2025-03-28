// Shared limits
#ifndef MCCONF_L_MAX_ABS_CURRENT
#define MCCONF_L_MAX_ABS_CURRENT		350.0	// The maximum absolute current above which a fault is generated
#endif
#ifndef MCCONF_L_MIN_VOLTAGE
#define MCCONF_L_MIN_VOLTAGE			60.0		// Minimum input voltage
#endif
#ifndef MCCONF_L_MAX_VOLTAGE
#define MCCONF_L_MAX_VOLTAGE			105.0	// Maximum input voltage
#endif
#ifndef MCCONF_L_BATTERY_CUT_START
#define MCCONF_L_BATTERY_CUT_START		66.0	// Start limiting the positive current at this voltage
#endif
#ifndef MCCONF_L_BATTERY_CUT_END
#define MCCONF_L_BATTERY_CUT_END		64.0		// Limit the positive current completely at this voltage
#endif
#ifndef MCCONF_L_RPM_MAX
#define MCCONF_L_RPM_MAX				100000.0	// The motor speed limit (Upper)
#endif
#ifndef MCCONF_L_RPM_MIN
#define MCCONF_L_RPM_MIN				-100000.0	// The motor speed limit (Lower)
#endif
#ifndef MCCONF_L_RPM_START
#define MCCONF_L_RPM_START				0.8		// Fraction of full speed where RPM current limiting starts
#endif
#ifndef MCCONF_L_SLOW_ABS_OVERCURRENT
#define MCCONF_L_SLOW_ABS_OVERCURRENT	true	// Use the filtered (and hence slower) current for the overcurrent fault detection
#endif
#ifndef MCCONF_L_MIN_DUTY
#define MCCONF_L_MIN_DUTY				0.005	// Minimum duty cycle
#endif
#ifndef MCCONF_L_MAX_DUTY
#define MCCONF_L_MAX_DUTY				0.95	// Maximum duty cycle
#endif
#ifndef MCCONF_L_CURR_MAX_RPM_FBRAKE
#define MCCONF_L_CURR_MAX_RPM_FBRAKE	300		// Maximum electrical RPM to use full brake at
#endif
#ifndef MCCONF_L_CURR_MAX_RPM_FBRAKE_CC
#define MCCONF_L_CURR_MAX_RPM_FBRAKE_CC	1500	// Maximum electrical RPM to use full brake at with current control
#endif
#ifndef MCCONF_L_LIM_TEMP_FET_START
#define MCCONF_L_LIM_TEMP_FET_START		120.0	// MOSFET temperature where current limiting should begin
#endif
#ifndef MCCONF_L_LIM_TEMP_FET_END
#define MCCONF_L_LIM_TEMP_FET_END		125.0	// MOSFET temperature where everything should be shut off
#endif
#ifndef MCCONF_L_LIM_TEMP_MOTOR_START
#define MCCONF_L_LIM_TEMP_MOTOR_START	165.0	// MOTOR temperature where current limiting should begin
#endif
#ifndef MCCONF_L_LIM_TEMP_MOTOR_END
#define MCCONF_L_LIM_TEMP_MOTOR_END		170.0	// MOTOR temperature where everything should be shut off
#endif
#ifndef MCCONF_L_LIM_TEMP_ACCEL_DEC
#define MCCONF_L_LIM_TEMP_ACCEL_DEC		0.0		// Decrease temperature limits this much during acceleration
#endif
#ifndef MCCONF_L_WATT_MAX
#define MCCONF_L_WATT_MAX				1500000.0	// Maximum wattage output
#endif
#ifndef MCCONF_L_WATT_MIN
#define MCCONF_L_WATT_MIN				-1500000.0	// Minimum wattage output (braking)
#endif
#ifndef MCCONF_L_CURRENT_MAX_SCALE
#define MCCONF_L_CURRENT_MAX_SCALE		1.0	// Maximum current scale
#endif
#ifndef MCCONF_L_CURRENT_MIN_SCALE
#define MCCONF_L_CURRENT_MIN_SCALE		1.0	// Minimum current scale
#endif
#ifndef MCCONF_L_DUTY_START
#define MCCONF_L_DUTY_START				1.0 // Start limiting current at this duty cycle
#endif

// Current control parameters
#ifndef MCCONF_CC_GAIN
#define MCCONF_CC_GAIN					0.0046	// Current controller error gain
#endif
#ifndef MCCONF_CC_MIN_CURRENT
#define MCCONF_CC_MIN_CURRENT			1.00	// Minimum allowed current
#endif
#ifndef MCCONF_CC_STARTUP_BOOST_DUTY
#define MCCONF_CC_STARTUP_BOOST_DUTY	0.01	// The lowest duty cycle to use in current control mode (has to be > MCPWM_MIN_DUTY_CYCLE)
#endif
#ifndef MCCONF_CC_RAMP_STEP
#define MCCONF_CC_RAMP_STEP				0.04	// Maximum duty cycle ramping step in CC mode
#endif

// FOC shared
#ifndef MCCONF_FOC_F_SW
#define MCCONF_FOC_F_SW					20000.0
#endif
#ifndef MCCONF_FOC_DT_US
#define MCCONF_FOC_DT_US				0.5 // Microseconds for dead time compensation
#endif
#ifndef MCCONF_FOC_ENCODER_INVERTED
#define MCCONF_FOC_ENCODER_INVERTED		false
#endif
#ifndef MCCONF_FOC_ENCODER_OFFSET
#define MCCONF_FOC_ENCODER_OFFSET		180.0
#endif
#ifndef MCCONF_FOC_ENCODER_RATIO
#define MCCONF_FOC_ENCODER_RATIO		7.0
#endif
#ifndef MCCONF_FOC_SENSOR_MODE
#define MCCONF_FOC_SENSOR_MODE			FOC_SENSOR_MODE_SENSORLESS
#endif
#ifndef MCCONF_FOC_PLL_KP
#define MCCONF_FOC_PLL_KP				2000.0
#endif
#ifndef MCCONF_FOC_PLL_KI
#define MCCONF_FOC_PLL_KI				30000.0
#endif

#ifndef MCCONF_FOC_OBSERVER_GAIN_SLOW
#define MCCONF_FOC_OBSERVER_GAIN_SLOW	0.05	// Observer gain scale at minimum duty cycle
#endif
#ifndef MCCONF_FOC_DUTY_DOWNRAMP_KP
#define MCCONF_FOC_DUTY_DOWNRAMP_KP		10.0	// PI controller for duty control when decreasing the duty
#endif
#ifndef MCCONF_FOC_DUTY_DOWNRAMP_KI
#define MCCONF_FOC_DUTY_DOWNRAMP_KI		200.0	// PI controller for duty control when decreasing the duty
#endif
#ifndef MCCONF_FOC_OPENLOOP_RPM
#define MCCONF_FOC_OPENLOOP_RPM			1200.0	// Openloop RPM (sensorless low speed or when finding index pulse)
#endif
#ifndef MCCONF_FOC_OPENLOOP_RPM_LOW
#define MCCONF_FOC_OPENLOOP_RPM_LOW		0.0		// Fraction of OPENLOOP_RPM at minimum motor current
#endif
#ifndef MCCONF_FOC_D_GAIN_SCALE_START
#define MCCONF_FOC_D_GAIN_SCALE_START	0.9		// Start reducing D axis current controller gain at this modulation
#endif
#ifndef MCCONF_FOC_D_GAIN_SCALE_MAX_MOD
#define MCCONF_FOC_D_GAIN_SCALE_MAX_MOD	0.2		// D axis currnet controller gain at maximum modulation
#endif
#ifndef MCCONF_FOC_SL_OPENLOOP_HYST
#define MCCONF_FOC_SL_OPENLOOP_HYST		0.1		// Time below min RPM to activate openloop (s)
#endif
#ifndef MCCONF_FOC_SL_OPENLOOP_TIME
#define MCCONF_FOC_SL_OPENLOOP_TIME		0.1	// Time to remain in openloop after ramping (s)
#endif
#ifndef MCCONF_FOC_SL_OPENLOOP_T_LOCK
#define MCCONF_FOC_SL_OPENLOOP_T_LOCK	0.0		// Time to lock motor in beginning of open loop sequence
#endif
#ifndef MCCONF_FOC_SL_OPENLOOP_T_RAMP
#define MCCONF_FOC_SL_OPENLOOP_T_RAMP	0.0		// Time to ramp up motor to openloop speed
#endif
#ifndef MCCONF_FOC_HALL_TAB_0
#define MCCONF_FOC_HALL_TAB_0			255
#endif
#ifndef MCCONF_FOC_HALL_TAB_1
#define MCCONF_FOC_HALL_TAB_1			255
#endif
#ifndef MCCONF_FOC_HALL_TAB_2
#define MCCONF_FOC_HALL_TAB_2			255
#endif
#ifndef MCCONF_FOC_HALL_TAB_3
#define MCCONF_FOC_HALL_TAB_3			255
#endif
#ifndef MCCONF_FOC_HALL_TAB_4
#define MCCONF_FOC_HALL_TAB_4			255
#endif
#ifndef MCCONF_FOC_HALL_TAB_5
#define MCCONF_FOC_HALL_TAB_5			255
#endif
#ifndef MCCONF_FOC_HALL_TAB_6
#define MCCONF_FOC_HALL_TAB_6			255
#endif
#ifndef MCCONF_FOC_HALL_TAB_7
#define MCCONF_FOC_HALL_TAB_7			255
#endif
#ifndef MCCONF_FOC_HALL_INTERP_ERPM
#define MCCONF_FOC_HALL_INTERP_ERPM		500		// Do not interpolate hall sensors below this ERPM
#endif
#ifndef MCCONF_FOC_SL_ERPM
#define MCCONF_FOC_SL_ERPM				2500.0	// ERPM above which only the observer is used
#endif
#ifndef MCCONF_FOC_SAMPLE_V0_V7
#define MCCONF_FOC_SAMPLE_V0_V7			false	// Run control loop in both v0 and v7 (requires phase shunts)
#endif
#ifndef MCCONF_FOC_SAMPLE_HIGH_CURRENT
#define MCCONF_FOC_SAMPLE_HIGH_CURRENT	false	// High current sampling mode (requires three shunts)
#endif
#ifndef MCCONF_FOC_SAT_COMP
#define MCCONF_FOC_SAT_COMP				0.0		// Stator saturation compensation
#endif
#ifndef MCCONF_FOC_TEMP_COMP
#define MCCONF_FOC_TEMP_COMP			false	// Motor temperature compensation
#endif
#ifndef MCCONF_FOC_TEMP_COMP_BASE_TEMP
#define MCCONF_FOC_TEMP_COMP_BASE_TEMP	20.0	// Motor temperature compensation base temperature
#endif
#ifndef MCCONF_FOC_CURRENT_FILTER_CONST
#define MCCONF_FOC_CURRENT_FILTER_CONST	0.1		// Filter constant for the filtered currents
#endif
#ifndef MCCONF_FOC_CC_DECOUPLING
#define MCCONF_FOC_CC_DECOUPLING		FOC_CC_DECOUPLING_BEMF // Current controller decoupling
#endif
#ifndef MCCONF_FOC_OBSERVER_TYPE
#define MCCONF_FOC_OBSERVER_TYPE		FOC_OBSERVER_ORTEGA_ORIGINAL // Position observer type for FOC
#endif
#ifndef MCCONF_FOC_HFI_VOLTAGE_START
#define MCCONF_FOC_HFI_VOLTAGE_START	20 // HFI voltage at start when resolving ambiguity
#endif
#ifndef MCCONF_FOC_HFI_VOLTAGE_RUN
#define MCCONF_FOC_HFI_VOLTAGE_RUN		4 // HFI voltage during tracking
#endif
#ifndef MCCONF_FOC_HFI_VOLTAGE_MAX
#define MCCONF_FOC_HFI_VOLTAGE_MAX		10 // HFI voltage during tracking at max current
#endif
#ifndef MCCONF_FOC_SL_ERPM_HFI
#define MCCONF_FOC_SL_ERPM_HFI			2000.0	// ERPM above which only the observer is used
#endif
#ifndef MCCONF_FOC_HFI_START_SAMPLES
#define MCCONF_FOC_HFI_START_SAMPLES	65 // Sample this often at start to resolve ambiguity
#endif
#ifndef MCCONF_FOC_HFI_OBS_OVR_SEC
#define MCCONF_FOC_HFI_OBS_OVR_SEC		0.001 // Continue using observer for this long when entering HFI speed
#endif
#ifndef MCCONF_FOC_HFI_SAMPLES
#define MCCONF_FOC_HFI_SAMPLES			HFI_SAMPLES_16 // Samples per motor revolution for HFI
#endif

// GPD
#ifndef MCCONF_GPD_BUFFER_NOTIFY_LEFT
#define MCCONF_GPD_BUFFER_NOTIFY_LEFT	200		// Notify when the buffer space left is less than this
#endif
#ifndef MCCONF_GPD_BUFFER_INTERPOL
#define MCCONF_GPD_BUFFER_INTERPOL		0		// Buffer interpolation
#endif
#ifndef MCCONF_GPD_CURRENT_FILTER_CONST
#define MCCONF_GPD_CURRENT_FILTER_CONST	0.1		// Current filter constant
#endif
#ifndef MCCONF_GPD_CURRENT_KP
#define MCCONF_GPD_CURRENT_KP			0.03
#endif
#ifndef MCCONF_GPD_CURRENT_KI
#define MCCONF_GPD_CURRENT_KI			50.0
#endif

// Misc
#ifndef MCCONF_M_FAULT_STOP_TIME
#define MCCONF_M_FAULT_STOP_TIME		500	// Ignore commands for this duration in msec when faults occur
#endif
#ifndef MCCONF_M_RAMP_STEP
#define MCCONF_M_RAMP_STEP				0.02	// Duty cycle ramping step (1000 times/sec) at maximum duty cycle
#endif
#ifndef MCCONF_M_CURRENT_BACKOFF_GAIN
#define MCCONF_M_CURRENT_BACKOFF_GAIN	0.5		// The error gain of the current limiting algorithm
#endif
#ifndef MCCONF_M_ENCODER_COUNTS
#define MCCONF_M_ENCODER_COUNTS			8192	// The number of encoder counts
#endif
#ifndef MCCONF_FOC_ENCODER_SIN_GAIN
#define MCCONF_FOC_ENCODER_SIN_GAIN		1.0		// Sine error gain of the sin/cos encoder
#endif
#ifndef MCCONF_FOC_ENCODER_SIN_OFFSET
#define MCCONF_FOC_ENCODER_SIN_OFFSET		1.65	// Sine offset of the sin/cos encoder
#endif
#ifndef MCCONF_FOC_ENCODER_COS_GAIN
#define MCCONF_FOC_ENCODER_COS_GAIN		1.0		// Cosine error gain of the sin/cos encoder
#endif
#ifndef MCCONF_FOC_ENCODER_COS_OFFSET
#define MCCONF_FOC_ENCODER_COS_OFFSET		1.65	// Cosine offset of the sin/cos encoder
#endif
#ifndef MCCONF_FOC_ENCODER_SINCOS_FILTER
#define MCCONF_FOC_ENCODER_SINCOS_FILTER	0.5		// Sin/Cos Encoder signal filter constant
#endif
#ifndef MCCONF_M_SENSOR_PORT_MODE
#define MCCONF_M_SENSOR_PORT_MODE		SENSOR_PORT_MODE_HALL // The mode of the hall_encoder port
#endif
#ifndef MCCONF_M_DRV8301_OC_MODE
#define MCCONF_M_DRV8301_OC_MODE		0 // DRV8301 over current protection mode
#endif
#ifndef MCCONF_M_DRV8301_OC_ADJ
#define MCCONF_M_DRV8301_OC_ADJ			16 // DRV8301 over current protection threshold
#endif
#ifndef MCCONF_M_BLDC_F_SW_MIN
#define MCCONF_M_BLDC_F_SW_MIN			3000 // Minimum switching frequency in bldc mode
#endif
#ifndef MCCONF_M_BLDC_F_SW_MAX
#define MCCONF_M_BLDC_F_SW_MAX			35000 // Maximum switching frequency in bldc mode
#endif
#ifndef MCCONF_M_DC_F_SW
#define MCCONF_M_DC_F_SW				25000 // Switching frequency in dc mode
#endif
#ifndef MCCONF_M_NTC_MOTOR_BETA
#define MCCONF_M_NTC_MOTOR_BETA			3380.0 // Beta value for motor termistor
#endif
#ifndef MCCONF_M_OUT_AUX_MODE
#define MCCONF_M_OUT_AUX_MODE			OUT_AUX_MODE_OFF // Auxiliary output mode
#endif
#ifndef MCCONF_M_MOTOR_TEMP_SENS_TYPE
#define MCCONF_M_MOTOR_TEMP_SENS_TYPE	TEMP_SENSOR_NTC_10K_25C // Motor temperature sensor type
#endif
#ifndef MCCONF_M_PTC_MOTOR_COEFF
#define MCCONF_M_PTC_MOTOR_COEFF		0.61 // %/K coefficient for motor PTC sensor
#endif
#ifndef MCCONF_M_HALL_EXTRA_SAMPLES
#define MCCONF_M_HALL_EXTRA_SAMPLES		1 // Extra samples for filtering when reading hall sensors
#endif

// Default settings
#ifndef MCCONF_DEFAULT_MOTOR_TYPE
#define MCCONF_DEFAULT_MOTOR_TYPE		2
#endif
#ifndef MCCONF_PWM_MODE
#define MCCONF_PWM_MODE					1 // Default PWM mode
#endif
#ifndef MCCONF_SENSOR_MODE
#define MCCONF_SENSOR_MODE				0 // Sensor mode
#endif
#ifndef MCCONF_COMM_MODE
#define MCCONF_COMM_MODE				0	// The commutation mode to use
#endif

// BMS
#ifndef MCCONF_BMS_TYPE
#define MCCONF_BMS_TYPE					BMS_TYPE_VESC
#endif
#ifndef MCCONF_BMS_T_LIMIT_START
#define MCCONF_BMS_T_LIMIT_START		45
#endif
#ifndef MCCONF_BMS_T_LIMIT_END
#define MCCONF_BMS_T_LIMIT_END			65
#endif
#ifndef MCCONF_BMS_SOC_LIMIT_START
#define MCCONF_BMS_SOC_LIMIT_START		0.05
#endif
#ifndef MCCONF_BMS_SOC_LIMIT_END
#define MCCONF_BMS_SOC_LIMIT_END		0
#endif

// Setup Info - UNUSED
#ifndef MCCONF_SI_MOTOR_POLES
#define MCCONF_SI_MOTOR_POLES			10 // Motor pole count
#endif
#ifndef MCCONF_SI_GEAR_RATIO
#define MCCONF_SI_GEAR_RATIO			1 // Gear ratio
#endif
#ifndef MCCONF_SI_WHEEL_DIAMETER
#define MCCONF_SI_WHEEL_DIAMETER		0.083 // Wheel Diameter
#endif
#ifndef MCCONF_SI_BATTERY_TYPE
#define MCCONF_SI_BATTERY_TYPE			BATTERY_TYPE_LIION_3_0__4_2 // Battery Type
#endif
#ifndef MCCONF_SI_BATTERY_CELLS
#define MCCONF_SI_BATTERY_CELLS			22 // Battery Cells
#endif
#ifndef MCCONF_SI_BATTERY_AH
#define MCCONF_SI_BATTERY_AH			24.0 // Battery amp hours
#endif

// Speed PID parameters
#ifndef MCCONF_S_PID_KP
#define MCCONF_S_PID_KP					0.0003	// Proportional gain
#endif
#ifndef MCCONF_S_PID_KI
#define MCCONF_S_PID_KI					0.0005	// Integral gain
#endif
#ifndef MCCONF_S_PID_KD
#define MCCONF_S_PID_KD					1e-5	// Derivative gain
#endif
#ifndef MCCONF_S_PID_KD_FILTER
#define MCCONF_S_PID_KD_FILTER			0.1	// Derivative filter
#endif
#ifndef MCCONF_S_PID_MIN_RPM
#define MCCONF_S_PID_MIN_RPM			1200.0	// Minimum allowed RPM
#endif
#ifndef MCCONF_S_PID_ALLOW_BRAKING
#define MCCONF_S_PID_ALLOW_BRAKING		1	// Allow braking in speed control mode
#endif
#ifndef MCCONF_S_PID_RAMP_ERPMS_S
#define MCCONF_S_PID_RAMP_ERPMS_S		30000	// Default Speed Input Ramp
#endif

// Position PID parameters
#ifndef MCCONF_P_PID_KP
#define MCCONF_P_PID_KP					0.03	// Proportional gain
#endif
#ifndef MCCONF_P_PID_KI
#define MCCONF_P_PID_KI					0.0		// Integral gain
#endif
#ifndef MCCONF_P_PID_KD
#define MCCONF_P_PID_KD					0.0004	// Derivative gain
#endif
#ifndef MCCONF_P_PID_KD_FILTER
#define MCCONF_P_PID_KD_FILTER			0.2		// Derivative filter
#endif
#ifndef MCCONF_P_PID_ANG_DIV
#define MCCONF_P_PID_ANG_DIV			1.0		// Divide angle by this value
#endif

// BLDC
#ifndef MCCONF_SL_MIN_RPM
#define MCCONF_SL_MIN_RPM				150		// Auto-commutate below this RPM
#endif
#ifndef MCCONF_SL_MIN_ERPM_CYCLE_INT_LIMIT
#define MCCONF_SL_MIN_ERPM_CYCLE_INT_LIMIT	1100.0	// Minimum RPM to calculate the BEMF coupling from
#endif
#ifndef MCCONF_SL_CYCLE_INT_LIMIT
#define MCCONF_SL_CYCLE_INT_LIMIT		62.0	// Flux integrator limit 0 ERPM
#endif
#ifndef MCCONF_SL_BEMF_COUPLING_K
#define MCCONF_SL_BEMF_COUPLING_K		600.0	// Input voltage to bemf coupling constant
#endif
#ifndef MCCONF_SL_PHASE_ADVANCE_AT_BR
#define MCCONF_SL_PHASE_ADVANCE_AT_BR	0.8		// Flux integrator limit percentage at MCPWM_CYCLE_INT_START_RPM_BR ERPM
#endif
#ifndef MCCONF_SL_CYCLE_INT_BR
#define MCCONF_SL_CYCLE_INT_BR			80000.0	// RPM border between the START and LOW interval
#endif
#ifndef MCCONF_SL_MAX_FB_CURR_DIR_CHANGE
#define MCCONF_SL_MAX_FB_CURR_DIR_CHANGE	10.0	// Maximum current during full brake during which a direction change is allowed
#endif

// BLDC hall sensor table
#ifndef MCCONF_HALL_TAB_0
#define MCCONF_HALL_TAB_0				-1
#endif
#ifndef MCCONF_HALL_TAB_1
#define MCCONF_HALL_TAB_1				1
#endif
#ifndef MCCONF_HALL_TAB_2
#define MCCONF_HALL_TAB_2				3
#endif
#ifndef MCCONF_HALL_TAB_3
#define MCCONF_HALL_TAB_3				2
#endif
#ifndef MCCONF_HALL_TAB_4
#define MCCONF_HALL_TAB_4				5
#endif
#ifndef MCCONF_HALL_TAB_5
#define MCCONF_HALL_TAB_5				6
#endif
#ifndef MCCONF_HALL_TAB_6
#define MCCONF_HALL_TAB_6				4
#endif
#ifndef MCCONF_HALL_TAB_7
#define MCCONF_HALL_TAB_7				-1
#endif
#ifndef MCCONF_HALL_ERPM
#define MCCONF_HALL_ERPM				2000.0	// ERPM above which sensorless commutation is used in hybrid mode
#endif
