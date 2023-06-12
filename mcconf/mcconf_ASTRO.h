#define NTC_TEMP_MOTOR(beta)	(NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR])*NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR])*(-5.833711E-05) + NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR])*0.287332 - 1.284209E+02)

// Awake settings
#define ERPM_DIVIDER 5

// Limits
#define MCCONF_L_CURRENT_MAX			200.0	// Current limit in Amperes (Upper)
#define MCCONF_L_CURRENT_MIN			-10.0	// Current limit in Amperes (Lower)
#define MCCONF_L_IN_CURRENT_MAX			120.0	// Input current limit in Amperes (Upper)
#define MCCONF_L_IN_CURRENT_MIN			-0.0	// Input current limit in Amperes (Lower)

// FOC
#define MCCONF_FOC_CURRENT_KP			0.0166
#define MCCONF_FOC_CURRENT_KI			31.76
#define MCCONF_FOC_MOTOR_L				1.3312e-05
#define MCCONF_FOC_MOTOR_R				0.0130
#define MCCONF_FOC_MOTOR_FLUX_LINKAGE	0.014768
#define MCCONF_FOC_MOTOR_LD_LQ_DIFF		0.0
#define MCCONF_FOC_OBSERVER_GAIN		4.45e6		// Can be something like 600 / L
