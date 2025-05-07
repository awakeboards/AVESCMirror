#ifndef AVESC_AW_DATATYPES_H
#define AVESC_AW_DATATYPES_H

// Boards
#define DEF_AW_BOARD_RV1                1
#define DEF_AW_BOARD_RV3                2
#define DEF_AW_BOARD_RVS                3
#define DEF_AW_BOARD_VINGA              4
#define DEF_AW_BOARD_RVEXPLORE          5 // beginner board
#define DEF_AW_BOARD_RVBRABUS           6 // BRABUS x Awake Shadow
#define DEF_AW_BOARD_RVULTIMATE         7 // old S
#define DEF_AW_BOARD_RVADVENTURE        8 // old 3
#define DEF_AW_BOARD_RVEXPLOREBRABUS    9 // BRABUS x Awake Shadow Explore

typedef enum {
    AW_BOARD_RV = 0,
    AW_BOARD_RV1 = DEF_AW_BOARD_RV1,
    AW_BOARD_RV3 = DEF_AW_BOARD_RV3,
    AW_BOARD_RVS = DEF_AW_BOARD_RVS,
    AW_BOARD_VINGA = DEF_AW_BOARD_VINGA,
    AW_BOARD_RVEXPLORE = DEF_AW_BOARD_RVEXPLORE,
    AW_BOARD_RVBRABUS = DEF_AW_BOARD_RVBRABUS,
    AW_BOARD_RVULTIMATE = DEF_AW_BOARD_RVULTIMATE,
    AW_BOARD_RVADVENTURE = DEF_AW_BOARD_RVADVENTURE,
    AW_BOARD_RVEXPLOREBRABUS = DEF_AW_BOARD_RVEXPLOREBRABUS
} aw_board_type;

// Motors
#define DEF_AW_MOTOR_ASTRO              1
#define DEF_AW_MOTOR_AMOTOR             2
#define DEF_AW_MOTOR_VINGA              3
#define DEF_AW_MOTOR_AMOTORV3           4

typedef enum {
    AW_MOTOR_UNKNOWN = 0,
    AW_MOTOR_ASTRO = DEF_AW_MOTOR_ASTRO,
    AW_MOTOR_AMOTOR = DEF_AW_MOTOR_AMOTOR,
    AW_MOTOR_VINGA = DEF_AW_MOTOR_VINGA,
    AW_MOTOR_AMOTORV3 = DEF_AW_MOTOR_AMOTORV3
} aw_motor_type;

// Shunts
#define DEF_AW_SH100            1
#define DEF_AW_SH200            2

typedef enum {
    AW_SHUNT_100 = DEF_AW_SH100,
    AW_SHUNT_200 = DEF_AW_SH200
} aw_shunt_type;

// PCB types
#define DEF_AW_PCB_AVESC23     0
#define DEF_AW_PCB_AVESC25     1

typedef enum {
    AW_AVESC_2_3 = DEF_AW_PCB_AVESC23,
    AW_AVESC_2_5 = DEF_AW_PCB_AVESC25
} aw_hw_type;

typedef enum {
    AW_CAN_MOTOR_MSG_FRAME = 3,
    AW_CAN_TB_THROTTLE_FRAME = 17,
    AW_CAN_TB_BOARD_ID = 20,
    AW_CAN_AVESC_FAULT_FRAME = 29,
    AW_CAN_TB_MBS_TYPE = 50,
    AW_CAN_TB_AVESC_VERSION = 51,
    AW_CAN_TB_LOCK_CONTROL = 52,
    AW_CAN_AVESC_SET_CURRENT_LIMITS = 53,
    AW_CAN_AVESC_SET_SERVOS = 54,
    AW_CAN_AVESC_SET_LED = 55
} aw_can_type;

typedef enum {
    AW_PM_ECO = 0,
    AW_PM_SPORT = 1,
    AW_PM_EXTREME = 2,
    AW_PM_SLOW = 3,
    AW_PM_BRABUS = 4
} aw_ride_mode;

typedef struct {
    aw_board_type board_type;
    aw_motor_type motor_type;
    aw_shunt_type shunt_type;
    bool locked;
} aw_config;

#endif //AVESC_AW_DATATYPES_H
