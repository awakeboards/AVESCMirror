#include "aw_throttle.h"

#include "app_awake.h"

// Private variables
static const float* aw_curve_brabus;
static const float* aw_curve_extreme;
static const float* aw_curve_sport;
static const float* aw_curve_eco;
static const float* aw_curve_kids;
static float aw_min_active_current;

// Private functions
static float aw_startup_current_logic(systime_t time_zero_throttle);
static float aw_throttle_to_current(uint8_t throttle, uint8_t mode);

void aw_init_throttle(void) {
    if (((app_configuration*) app_get_configuration())->app_awake.board_type == AW_BOARD_VINGA) {
        aw_curve_brabus = aw_curve_vinga_extreme; // not used
        aw_curve_extreme = aw_curve_vinga_extreme;
        aw_curve_sport = aw_curve_vinga_sport;
        aw_curve_eco = aw_curve_vinga_eco;
        aw_curve_kids = aw_curve_vinga_kids; // slow mode

        aw_min_active_current = AW_VINGA_MIN_ACTIVE_CURRENT;
    } else { // Ravik series boards
        aw_curve_brabus = aw_curve_ravik_brabus; // only for RVBRABUS boards
        aw_curve_extreme = aw_curve_ravik_extreme;
        aw_curve_sport = aw_curve_ravik_sport;
        aw_curve_eco = aw_curve_ravik_eco;
        aw_curve_kids = aw_curve_ravik_kids; // slow mode

        aw_min_active_current = AW_RAVIK_MIN_ACTIVE_CURRENT;
    }
}

void aw_handle_throttle(uint8_t throttle, uint8_t mode) {
    static systime_t time_zero_throttle = 0; // holds last time zero throttle was requested

    if (((app_configuration*) app_get_configuration())->app_awake.locked) {
        return; // CM is locked, we do not allow throttle control
    }

    if (mode == AW_PM_BRABUS
        && ((app_configuration*) app_get_configuration())->app_awake.board_type != AW_BOARD_RVBRABUS) {
        mode = AW_PM_EXTREME; // If BRABUS mode is requested on a non-Brabus board, set it to extreme mode
    }

    if (throttle > 0 && fabsf(mcpwm_foc_get_rpm()) < AW_MIN_STABLE_RPM) { // startup logic
        aw_set_current(aw_startup_current_logic(time_zero_throttle));
    } else if (throttle > 0) { // normal operation logic
        aw_set_current(aw_throttle_to_current(throttle, mode));
    } else { // no throttle logic (throttle = 0)
        aw_set_current(0);
        time_zero_throttle = chVTGetSystemTimeX();
    }
}

static float aw_startup_current_logic(systime_t time_zero_throttle) {
    float startup_duration = ST2MS(chVTGetSystemTimeX() - time_zero_throttle) / 1000.0;
    float startup_current = 0;

    // if not in timeout yet, do startup current logic
    if (startup_duration < AW_STARTUP_TIMEOUT) {
        startup_current = AW_STARTUP_CURRENT_INITIAL + AW_STARTUP_CURRENT_RAMP * startup_duration;
        if (startup_current > AW_STARTUP_CURRENT_MAX)
            startup_current = AW_STARTUP_CURRENT_MAX;
    } else {
        mc_interface_fault_stop(FAULT_CODE_BRK, false, false);
    }

    return startup_current;
}

static float aw_throttle_to_current(uint8_t throttle, uint8_t mode) {
    // throttle range safety check
    throttle = throttle > 99 ? 99 : throttle;

    if (mode == AW_PM_BRABUS) { // boost current limits for Brabus mode
        ((volatile mc_configuration*) mc_interface_get_configuration())->l_current_max =
                MCCONF_L_CURRENT_MAX * AW_BRABUS_CURRENT_BOOST;
        ((volatile mc_configuration*) mc_interface_get_configuration())->l_in_current_max =
                MCCONF_L_IN_CURRENT_MAX * AW_BRABUS_CURRENT_IN_BOOST;
    } else { // reset to default
        ((volatile mc_configuration*) mc_interface_get_configuration())->l_current_max = MCCONF_L_CURRENT_MAX;
        ((volatile mc_configuration*) mc_interface_get_configuration())->l_in_current_max = MCCONF_L_IN_CURRENT_MAX;
    }

    // throttle curve data
    float i_p;
    if (mode == AW_PM_BRABUS) {
        i_p = aw_curve_brabus[throttle];
    } else if (mode == AW_PM_EXTREME) {
        i_p = aw_curve_extreme[throttle];
    } else if (mode == AW_PM_SPORT) {
        i_p = aw_curve_sport[throttle];
    } else if (mode == AW_PM_ECO) {
        i_p = aw_curve_eco[throttle];
    } else { // kids/slow/safety
        i_p = aw_curve_kids[throttle];
    }

    // relative current to amperes
    float current = i_p * mc_interface_get_configuration()->l_current_max;

    // limit minimal current for smoother startup
    return current < aw_min_active_current ? aw_min_active_current : current;
}
