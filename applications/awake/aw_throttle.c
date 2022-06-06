#include "aw_throttle.h"

// Private variables
static const float* aw_curve_extreme;
static const float* aw_curve_sport;
static const float* aw_curve_eco;
static const float* aw_curve_kids;
static float aw_min_active_current;

// Private functions
static void aw_set_current(float dt, float current);
static float aw_startup_current_logic(systime_t time_zero_throttle);
static float aw_throttle_to_current(uint8_t throttle, uint8_t mode);

void aw_init_throttle(void) {
    if (((app_configuration*) app_get_configuration())->app_awake.board_type == AW_BOARD_FOIL) {
        aw_curve_extreme = aw_curve_foil_extreme;
        aw_curve_sport = aw_curve_foil_sport;
        aw_curve_eco = aw_curve_foil_eco;
        aw_curve_kids = aw_curve_foil_kids; // slow mode

        aw_min_active_current = AW_FOIL_MIN_ACTIVE_CURRENT;
    } else {
        aw_curve_extreme = aw_curve_ravik_extreme;
        aw_curve_sport = aw_curve_ravik_sport;
        aw_curve_eco = aw_curve_ravik_eco;
        aw_curve_kids = aw_curve_ravik_kids; // slow mode

        aw_min_active_current = AW_RAVIK_MIN_ACTIVE_CURRENT;
    }
}

void aw_handle_throttle(uint8_t throttle, uint8_t mode) {
    static systime_t time_last = 0; // holds last time this function was called
    static systime_t time_zero_throttle = 0; // holds last time zero throttle was requested

    float dt = ST2MS(chVTGetSystemTimeX() - time_last) / 1000.0;

    if (throttle > 0 && fabsf(mcpwm_foc_get_rpm()) < AW_MIN_STABLE_RPM) { // startup logic
        aw_set_current(dt, aw_startup_current_logic(time_zero_throttle));
    } else if (throttle > 0) { // normal operation logic
        aw_set_current(dt, aw_throttle_to_current(throttle, mode));
    } else { // no throttle logic (throttle = 0)
        aw_set_current(dt, 0);
        time_zero_throttle = chVTGetSystemTimeX();
    }

    time_last = chVTGetSystemTimeX();
}

static void aw_set_current(float dt, float current) {
    static float current_old = 0;

    if (dt > 0) {
        float dcurrent = (current - current_old) / dt; // A/s
        if (dcurrent > AW_CURRENT_RAMP_LIMIT) {
            current = current_old + AW_CURRENT_RAMP_LIMIT * dt;
        } else if (dcurrent < -AW_CURRENT_RAMP_LIMIT) {
            current = current_old - AW_CURRENT_RAMP_LIMIT * dt;
        }
    }

    mc_interface_set_current(current);

    current_old = current;
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

    // throttle curve data
    float i_p;
    if (mode == AW_PM_EXTREME) {
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
