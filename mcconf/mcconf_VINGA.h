#define NTC_TEMP_MOTOR(beta) 	(((NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR]) / 1000.0) - 1.0) / 0.00385)

// Awake settings
#define ERPM_DIVIDER 5

#define MCCONF_M_INVERT_DIRECTION		true

// Limits
#define MCCONF_L_CURRENT_MAX			195.0	// Current limit in Amperes (Upper)
#define MCCONF_L_CURRENT_MIN			-2.0	// Current limit in Amperes (Lower)
#define MCCONF_L_IN_CURRENT_MAX			120.00	// Input current limit in Amperes (Upper)
#define MCCONF_L_IN_CURRENT_MIN			-0.0	// Input current limit in Amperes (Lower)

// FOC
#define MCCONF_FOC_CURRENT_KP			0.0106
#define MCCONF_FOC_CURRENT_KI			22.14
#define MCCONF_FOC_MOTOR_L				8.6e-06
#define MCCONF_FOC_MOTOR_R				0.012
#define MCCONF_FOC_MOTOR_FLUX_LINKAGE	0.007543
#define MCCONF_FOC_MOTOR_LD_LQ_DIFF		0.0
#define MCCONF_FOC_OBSERVER_GAIN		17.58e6		// Can be something like 600 / L
