#ifndef _AW_SERVOS_H
#define _AW_SERVOS_H

#include <math.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "stm32f4xx_conf.h"
#include "pwm.h"

void aw_init_servos(void);

void aw_update_servos(int16_t servo1, int16_t servo2, int16_t servo3, int16_t servo4);

#endif
