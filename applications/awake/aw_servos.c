#include "aw_servos.h"

// (PWM_PERCENTAGE_TO_WIDTH expects 0-10000 scale)
#define SERVO_MIN_PERCENT 350
#define SERVO_MID_PERCENT 750
#define SERVO_MAX_PERCENT 1150

// Helper to map int16_t value to PWM percentage duty cycle in the range [SERVO_MIN_PERCENT, SERVO_MAX_PERCENT]
static inline uint16_t map_servo_duty(int16_t value) {
    return (uint16_t)((((int32_t)value - INT16_MIN) * (SERVO_MAX_PERCENT - SERVO_MIN_PERCENT)) /
                      (INT16_MAX - INT16_MIN)) + SERVO_MIN_PERCENT;
}

// Timer configuration
static PWMConfig pwmcfg = {
    .frequency = 1000000, // 1 MHz timer clock (for fine resolution)
    .period = 20000,      // 20 ms period (50 Hz frequency)
    .callback = NULL,
    .channels = {
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}
    },
    .cr2 = 0,
};

void aw_init_servos(void) {
    // Start PWM Timer (TIM3)
    pwmStart(&PWMD3, &pwmcfg);

    // Initialize pins for PWM output
    palSetPadMode(GPIOC, 6, PAL_MODE_ALTERNATE(2)); // PC6 -> TIM3 CH1
    palSetPadMode(GPIOC, 7, PAL_MODE_ALTERNATE(2)); // PC7 -> TIM3 CH2
    palSetPadMode(GPIOC, 8, PAL_MODE_ALTERNATE(2)); // PC8 -> TIM3 CH3
    palSetPadMode(GPIOC, 9, PAL_MODE_ALTERNATE(2)); // PC9 -> TIM3 CH4

    // Set all servos to middle position using PWM_PERCENTAGE_TO_WIDTH
    pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, SERVO_MID_PERCENT));
    pwmEnableChannel(&PWMD3, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, SERVO_MID_PERCENT));
    pwmEnableChannel(&PWMD3, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, SERVO_MID_PERCENT));
    pwmEnableChannel(&PWMD3, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, SERVO_MID_PERCENT));
}

void aw_update_servos(int16_t servo1, int16_t servo2, int16_t servo3, int16_t servo4) {
    pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, map_servo_duty(servo1)));
    pwmEnableChannel(&PWMD3, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, map_servo_duty(servo2)));
    pwmEnableChannel(&PWMD3, 2, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, map_servo_duty(servo3)));
    pwmEnableChannel(&PWMD3, 3, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, map_servo_duty(servo4)));
}
