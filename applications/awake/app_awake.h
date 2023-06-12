#ifndef _APP_AWAKE_H
#define _APP_AWAKE_H

#include <string.h>

#include "app.h"
#include "ch.h"
#include "hal.h"

#include "ledpwm.h"
#include "mc_interface.h"
#include "comm_can.h"
#include "hw.h"
#include "timeout.h"
#include "buffer.h"

#include "aw_throttle.h"

typedef enum {
    AW_LED_BLINK = 0,
    AW_LED_OFF = 1,
    AW_LED_ON = 2
} aw_led_indication;

typedef enum {
    AW_FEATURE_BASE = 0,
    AW_FEATURE_DIRECT_CURRENT_CONTROL = 1 << 0,
} aw_avesc_features;

#endif
