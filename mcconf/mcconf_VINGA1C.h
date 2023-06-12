#define NTC_TEMP_MOTOR(beta) 	(((NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR]) / 1000.0) - 1.0) / 0.00385)

// Awake settings
#define ERPM_DIVIDER 5

// Limits
#define MCCONF_L_CURRENT_MAX			195.0	// Current limit in Amperes (Upper)
#define MCCONF_L_CURRENT_MIN			-2.0	// Current limit in Amperes (Lower)
#define MCCONF_L_IN_CURRENT_MAX			120.00	// Input current limit in Amperes (Upper)
#define MCCONF_L_IN_CURRENT_MIN			-0.0	// Input current limit in Amperes (Lower)

// FOC
#define MCCONF_FOC_CURRENT_KP			0.0159
#define MCCONF_FOC_CURRENT_KI			16.20
#define MCCONF_FOC_MOTOR_L				15.95e-06
#define MCCONF_FOC_MOTOR_R				0.014
#define MCCONF_FOC_MOTOR_FLUX_LINKAGE	0.006122
#define MCCONF_FOC_MOTOR_LD_LQ_DIFF		0.0
#define MCCONF_FOC_OBSERVER_GAIN		26.68e6		// Can be something like 600 / L
