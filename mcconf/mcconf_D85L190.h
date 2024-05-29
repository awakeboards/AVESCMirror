// A bit longer version as D85L165 motor, measured 78 KV

#define NTC_TEMP_MOTOR(beta) 	(1.0 / ((logf(NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR]) / 230000.0) / 4537.0) + (1.0 / 298.15)) - 273.15)

// Awake settings
#define ERPM_DIVIDER 5

#define MCCONF_M_INVERT_DIRECTION		false

// Limits
#define MCCONF_L_CURRENT_MAX			200.0	// Current limit in Amperes (Upper)
#define MCCONF_L_CURRENT_MIN			-2.0	// Current limit in Amperes (Lower)
#define MCCONF_L_IN_CURRENT_MAX			120.00	// Input current limit in Amperes (Upper)
#define MCCONF_L_IN_CURRENT_MIN			-0.0	// Input current limit in Amperes (Lower)

// FOC
#define MCCONF_FOC_CURRENT_KP			0.0156
#define MCCONF_FOC_CURRENT_KI			15.78
#define MCCONF_FOC_MOTOR_L				15.64e-06
#define MCCONF_FOC_MOTOR_R				0.0135 // measured with mOhm meter
#define MCCONF_FOC_MOTOR_FLUX_LINKAGE	0.015011
#define MCCONF_FOC_MOTOR_LD_LQ_DIFF		0.0
#define MCCONF_FOC_OBSERVER_GAIN		4.44e6
