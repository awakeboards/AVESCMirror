#define NTC_TEMP_MOTOR(beta)	(((NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR]) / 1000.0) - 1.0) / 0.00385)

// Awake settings
#define ERPM_DIVIDER 5

#define MCCONF_M_INVERT_DIRECTION		true

// Limits
#define MCCONF_L_CURRENT_MAX			180.0	// Current limit in Amperes (Upper)
#define MCCONF_L_CURRENT_MIN			-10.0	// Current limit in Amperes (Lower)
#define MCCONF_L_IN_CURRENT_MAX			110.0	// Input current limit in Amperes (Upper)
#define MCCONF_L_IN_CURRENT_MIN			-0.0	// Input current limit in Amperes (Lower)

// FOC
#define MCCONF_FOC_CURRENT_KP			0.0178
#define MCCONF_FOC_CURRENT_KI			45.56
#define MCCONF_FOC_MOTOR_L				1.4248e-05
#define MCCONF_FOC_MOTOR_R				0.015
#define MCCONF_FOC_MOTOR_FLUX_LINKAGE	0.015787
#define MCCONF_FOC_MOTOR_LD_LQ_DIFF		0.0
#define MCCONF_FOC_OBSERVER_GAIN		4.01e6		// Can be something like 600 / L
