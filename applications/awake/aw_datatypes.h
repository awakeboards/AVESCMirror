#ifndef AVESC_AW_DATATYPES_H
#define AVESC_AW_DATATYPES_H

typedef enum {
    AW_CAN_MOTOR_MSG_FRAME = 3,
    AW_CAN_TB_THROTTLE_FRAME = 17,
    AW_CAN_TB_BOARD_ID = 20,
    AW_CAN_AVESC_FAULT_FRAME = 29,
    AW_CAN_TB_MBS_TYPE = 50,
    AW_CAN_TB_AVESC_VERSION = 51
} aw_can_type;

typedef enum {
    AW_PM_ECO = 0,
    AW_PM_SPORT = 1,
    AW_PM_EXTREME = 2,
    AW_PM_SLOW = 3
} aw_ride_mode;

typedef enum {
    AW_BOARD_RV = 0,
    AW_BOARD_RV1 = 1,
    AW_BOARD_RV3 = 2,
    AW_BOARD_RVS = 3,
    AW_BOARD_FOIL = 4,
    AW_BOARD_RVRS = 5,
} aw_board_type;

typedef enum {
    AW_MOTOR_UNKNOWN = 0,
    AW_MOTOR_ASTRO = 1,
    AW_MOTOR_AMOTOR = 2,
    AW_MOTOR_FOIL = 3
} aw_motor_type;

typedef enum {
    AW_SHUNT_100 = 1,
    AW_SHUNT_200 = 2
} aw_shunt_type;

typedef struct {
    aw_board_type board_type;
    aw_motor_type motor_type;
    aw_shunt_type shunt_type;
} aw_config;

#endif //AVESC_AW_DATATYPES_H
