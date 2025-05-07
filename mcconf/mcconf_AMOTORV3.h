// 88mm diameter, 203mm length, measured 73 KV, introduced to FW on 15. 7. 2024
// PH-D85L195-73KV part number

#define NTC_TEMP_MOTOR(beta) 	(1.0 / ((logf(NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR]) / 230000.0) / 4537.0) + (1.0 / 298.15)) - 273.15)

// Awake settings
#define AW_ERPM_DIVIDER                 5
#define AW_CURRENT_RAMP_LIMIT           1000    // A/s - the fastest overall change of current allowed
#define AW_MIN_ACTIVE_CURRENT           10      // A - minimal current during a normal motor operation

// Duty limiter to prevent idle-run oscillation
#define AW_DUTY_LIMITER_MIN 0.20 // min. duty cycle limit we apply
#define AW_DUTY_LIMITER_MAX_CURRENT 0.20 // % of max motor L current where dynamic duty cycle limiter stops operating
#define AW_DUTY_LIMITER_FILTER 0.7 // smaller value allows for smaller max current and still keeps motor running smoothly, but also delays the response of the filter at startup

#define MCCONF_M_INVERT_DIRECTION		true

#define MCCONF_CC_MIN_CURRENT           AW_MIN_ACTIVE_CURRENT

// Limits
#if AW_BOARD == DEF_AW_BOARD_RVEXPLORE
    #define MCCONF_L_CURRENT_MAX			190.0	// Current limit in Amperes (Upper)
    #define MCCONF_L_CURRENT_MIN			-20.0	// Current limit in Amperes (Lower)
    #define MCCONF_L_IN_CURRENT_MAX			110.00	// Input current limit in Amperes (Upper)
    #define MCCONF_L_IN_CURRENT_MIN			-20.0	// Input current limit in Amperes (Lower)
#else // DEF_AW_BOARD_RVULTIMATE and DEF_AW_BOARD_RVEXPLOREBRABUS
    #define MCCONF_L_CURRENT_MAX			190.0	// Current limit in Amperes (Upper)
    #define MCCONF_L_CURRENT_MIN			-20.0	// Current limit in Amperes (Lower)
    #define MCCONF_L_IN_CURRENT_MAX			110.00	// Input current limit in Amperes (Upper)
    #define MCCONF_L_IN_CURRENT_MIN			-20.0	// Input current limit in Amperes (Lower)
#endif

// FOC
#define MCCONF_FOC_CURRENT_KP			0.0150
#define MCCONF_FOC_CURRENT_KI			15.34
#define MCCONF_FOC_MOTOR_L				15.00e-06
#define MCCONF_FOC_MOTOR_R				0.0144 // measured with mOhm meter
#define MCCONF_FOC_MOTOR_FLUX_LINKAGE	0.016538
#define MCCONF_FOC_MOTOR_LD_LQ_DIFF		0.0
#define MCCONF_FOC_OBSERVER_GAIN		1.4e06

#define MCCONF_FOC_OPENLOOP_RPM			1200.0
#define MCCONF_FOC_OPENLOOP_RPM_LOW		0.25
#define MCCONF_FOC_SL_OPENLOOP_HYST		0.1
#define MCCONF_FOC_SL_OPENLOOP_T_LOCK	0.01
#define MCCONF_FOC_SL_OPENLOOP_T_RAMP	0.02
#define MCCONF_FOC_SL_OPENLOOP_TIME		0.02

#if AW_BOARD == DEF_AW_BOARD_RVEXPLORE
    #define MCCONF_L_RPM_MAX				+(5500 * AW_ERPM_DIVIDER)	// The motor speed limit (Upper)
    #define MCCONF_L_RPM_MIN				-(5500 * AW_ERPM_DIVIDER)	// The motor speed limit (Upper)
    #undef AW_CURRENT_RAMP_LIMIT
    #define AW_CURRENT_RAMP_LIMIT           100    // A/s - the fastest overall change of current allowed
#endif
