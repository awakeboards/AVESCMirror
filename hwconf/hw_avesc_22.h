#ifndef HW_AVESC_20_H_
#define HW_AVESC_20_H_

#include "timestamp.h"

#define _STRINGIZE(x) #x
#define STRINGIZE(x) _STRINGIZE(x)

	// motor type
#ifdef ASTRO
#define M_NAME "ASTRO"
#endif
#ifdef AMOTOR
#define M_NAME "AMOTOR"
#endif
#ifdef FOIL
#define M_NAME "FOIL"
#endif

	// board type
#ifdef B_RV1
#define B_NAME "RV1"
#endif
#ifdef B_RV3
#define B_NAME "RV3"
#endif
#ifdef B_RVS
#define B_NAME "RVS"
#endif
#ifdef B_FOIL
#define B_NAME "FOIL"
#endif

	// shunt type
#ifdef SHUNT100
#define S_NAME "S100"
#endif
#ifdef SHUNT200
#define S_NAME "S200"
#endif

#define HW_NAME	"AVESC_2_3_"STRINGIZE(VTYPE)"_"M_NAME"_"S_NAME

#define DEV 0

// HW properties
#define HW_HAS_3_SHUNTS

// Macros
#define LED_GREEN_GPIO			GPIOC
#define LED_GREEN_PIN			15
#define LED_RED_GPIO			GPIOC
#define LED_RED_PIN				14

#define LED_GREEN_ON()			palSetPad(LED_GREEN_GPIO, LED_GREEN_PIN)
#define LED_GREEN_OFF()			palClearPad(LED_GREEN_GPIO, LED_GREEN_PIN)
#define LED_RED_ON()			palSetPad(LED_RED_GPIO, LED_RED_PIN)
#define LED_RED_OFF()			palClearPad(LED_RED_GPIO, LED_RED_PIN)

#define IS_DRV_FAULT()			(!palReadPad(GPIOD, 2))
#define GATE_DRIVER_RESET_ON()  palSetPad(GPIOC, 12)
#define GATE_DRIVER_RESET_OFF()	palClearPad(GPIOC, 12)

#define INVERTED_SHUNT_POLARITY

/*
 * ADC Vector
 *
 * 0  (1):	IN0		SENS1
 * 1  (2):	IN1		SENS2
 * 2  (3):	IN2		SENS3
 * 3  (1):	IN10	CURR1
 * 4  (2):	IN11	CURR2
 * 5  (3):	IN12	CURR3
 * 6  (1):	IN5		ADC_EXT1
 * 7  (2):	IN6		ADC_EXT2
 * 8  (3):	IN3		TEMP_MOS
 * 9  (1):	IN14	TEMP_MOTOR
 * 10 (2):	IN15	ADC_EXT3
 * 11 (3):	IN13	AN_IN
 * 12 (1):	Vrefint
 * 13 (2):	IN0		SENS1
 * 14 (3):	IN1		SENS2
 * 15 (1):  IN8		TEMP_MOS_2
 * 16 (2):  IN9		TEMP_MOS_3
 * 17 (3):  IN3		SENS3
 */

#define HW_ADC_CHANNELS			18
#define HW_ADC_INJ_CHANNELS		3
#define HW_ADC_NBR_CONV			6

// ADC Indexes
#define ADC_IND_SENS1			0
#define ADC_IND_SENS2			1
#define ADC_IND_SENS3			2
#define ADC_IND_CURR1			3
#define ADC_IND_CURR2			4
#define ADC_IND_CURR3			5
#define ADC_IND_VIN_SENS		11
#define ADC_IND_EXT				6
#define ADC_IND_EXT2			7
#define ADC_IND_EXT3			10
#define ADC_IND_TEMP_MOS		8
#define ADC_IND_TEMP_MOS_2		15
#define ADC_IND_TEMP_MOS_3		16
#define ADC_IND_TEMP_MOTOR		9
#define ADC_IND_VREFINT			12

// ADC macros and settings

// Component parameters (can be overridden)
#ifndef V_REG
#define V_REG					3.3
#endif
#ifndef VIN_R1
#define VIN_R1					47000.0
#endif
#ifndef VIN_R2
#define VIN_R2					1000.0
#endif

#define AW_SHUNT100_CURRENT_AMP_GAIN		50.0
#define AW_SHUNT100_CURRENT_SHUNT_RES		0.0001

#define AW_SHUNT200_CURRENT_AMP_GAIN		20.0
#define AW_SHUNT200_CURRENT_SHUNT_RES		0.0002

#ifndef CURRENT_AMP_GAIN
#define CURRENT_AMP_GAIN		1.0 // actual value is part of CURRENT_SHUNT_RES
#endif
#ifndef CURRENT_SHUNT_RES
#define CURRENT_SHUNT_RES		aw_hw_avesc_shunt_factor()
#endif

#define HW_MAX_CURRENT_OFFSET				4096	// don't check for current offset
#define MCCONF_MAX_CURRENT_UNBALANCE		100.0	// [Amp] More than this unbalance trips the fault likely a INA240 or motor damaged


// Input voltage
#define GET_INPUT_VOLTAGE()		((V_REG / 4095.0) * (float)ADC_Value[ADC_IND_VIN_SENS] * ((VIN_R1 + VIN_R2) / VIN_R2))

// NTC Termistors
#define NTC_RES(adc_val)		(10000.0 / ((4095.0 / (float)adc_val) - 1.0))
#define NTC_TEMP(adc_ind)		avesc_get_temp()

#define NTC_RES_MOTOR(adc_val)	(4700.0 * (float)adc_val / (4096.0-(float)adc_val))


//model uses second degree polinomial fit
#ifdef ASTRO
//#define NTC_TEMP_MOTOR(beta)	(NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR])*NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR])*(-5.833711E-05) + NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR])*0.287332 - 1.284209E+02) 
#define NTC_TEMP_MOTOR(beta) 70.0
#endif

//model uses first degree polinomial fit
#ifdef AMOTOR
//#define NTC_TEMP_MOTOR(beta)	(((NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR]) / 1000.0) - 1.0) / 0.00385)
#define NTC_TEMP_MOTOR(beta) 70.0
#endif

//model uses first degree polinomial fit
#ifdef FOIL
#define NTC_TEMP_MOTOR(beta) 	(((NTC_RES_MOTOR(ADC_Value[ADC_IND_TEMP_MOTOR]) / 1000.0) - 1.0) / 0.00385)
//#define NTC_TEMP_MOTOR(beta) 70.0
#endif

#define NTC_TEMP_MOS1()			(1.0 / ((logf(NTC_RES(ADC_Value[ADC_IND_TEMP_MOS]) / 10000.0) / 3380.0) + (1.0 / 298.15)) - 273.15)
#define NTC_TEMP_MOS2()			(1.0 / ((logf(NTC_RES(ADC_Value[ADC_IND_TEMP_MOS_2]) / 10000.0) / 3380.0) + (1.0 / 298.15)) - 273.15)
#define NTC_TEMP_MOS3()			(1.0 / ((logf(NTC_RES(ADC_Value[ADC_IND_TEMP_MOS_3]) / 10000.0) / 3380.0) + (1.0 / 298.15)) - 273.15)

// Voltage on ADC channel
#define ADC_VOLTS(ch)			((float)ADC_Value[ch] / 4096.0 * V_REG)

// Double samples in beginning and end for positive current measurement.
// Useful when the shunt sense traces have noise that causes offset.
#ifndef CURR1_DOUBLE_SAMPLE
#define CURR1_DOUBLE_SAMPLE		0
#endif
#ifndef CURR2_DOUBLE_SAMPLE
#define CURR2_DOUBLE_SAMPLE		0
#endif
#ifndef CURR3_DOUBLE_SAMPLE
#define CURR3_DOUBLE_SAMPLE		0
#endif

// COMM-port ADC GPIOs
#define HW_ADC_EXT_GPIO			GPIOA
#define HW_ADC_EXT_PIN			5
#define HW_ADC_EXT2_GPIO		GPIOA
#define HW_ADC_EXT2_PIN			6

// UART Peripheral
#define HW_UART_DEV				SD3
#define HW_UART_GPIO_AF			GPIO_AF_USART3
#define HW_UART_TX_PORT			GPIOB
#define HW_UART_TX_PIN			10
#define HW_UART_RX_PORT			GPIOB
#define HW_UART_RX_PIN			11

// Permanent UART Peripheral (for NRF51)
#define HW_UART_P_BAUD			115200
#define HW_UART_P_DEV			SD4
#define HW_UART_P_GPIO_AF		GPIO_AF_UART4
#define HW_UART_P_TX_PORT		GPIOC
#define HW_UART_P_TX_PIN		10
#define HW_UART_P_RX_PORT		GPIOC
#define HW_UART_P_RX_PIN		11

//#ifdef HW75_300_REV_3
// NRF SWD
//#define NRF5x_SWDIO_GPIO		GPIOA
//#define NRF5x_SWDIO_PIN			15
//#define NRF5x_SWCLK_GPIO		GPIOB
//#define NRF5x_SWCLK_PIN			3
//#endif

// ICU Peripheral for servo decoding
#define HW_USE_SERVO_TIM4
#define HW_ICU_TIMER			TIM4
#define HW_ICU_TIM_CLK_EN()		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE)
#define HW_ICU_DEV				ICUD4
#define HW_ICU_CHANNEL			ICU_CHANNEL_1
#define HW_ICU_GPIO_AF			GPIO_AF_TIM4
#define HW_ICU_GPIO				GPIOB
#define HW_ICU_PIN				6

// I2C Peripheral
#define HW_I2C_DEV				I2CD2
#define HW_I2C_GPIO_AF			GPIO_AF_I2C2
#define HW_I2C_SCL_PORT			GPIOB
#define HW_I2C_SCL_PIN			10
#define HW_I2C_SDA_PORT			GPIOB
#define HW_I2C_SDA_PIN			11

// Hall/encoder pins
#define HW_HALL_ENC_GPIO1		GPIOC
#define HW_HALL_ENC_PIN1		6
#define HW_HALL_ENC_GPIO2		GPIOC
#define HW_HALL_ENC_PIN2		7
#define HW_HALL_ENC_GPIO3		GPIOC
#define HW_HALL_ENC_PIN3		8
#define HW_ENC_TIM				TIM3
#define HW_ENC_TIM_AF			GPIO_AF_TIM3
#define HW_ENC_TIM_CLK_EN()		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE)
#define HW_ENC_EXTI_PORTSRC		EXTI_PortSourceGPIOC
#define HW_ENC_EXTI_PINSRC		EXTI_PinSource8
#define HW_ENC_EXTI_CH			EXTI9_5_IRQn
#define HW_ENC_EXTI_LINE		EXTI_Line8
#define HW_ENC_EXTI_ISR_VEC		EXTI9_5_IRQHandler
#define HW_ENC_TIM_ISR_CH		TIM3_IRQn
#define HW_ENC_TIM_ISR_VEC		TIM3_IRQHandler

// SPI pins
#define HW_SPI_DEV				SPID1
#define HW_SPI_GPIO_AF			GPIO_AF_SPI1
#define HW_SPI_PORT_NSS			GPIOA
#define HW_SPI_PIN_NSS			4
#define HW_SPI_PORT_SCK			GPIOA
#define HW_SPI_PIN_SCK			5
#define HW_SPI_PORT_MOSI		GPIOA
#define HW_SPI_PIN_MOSI			7
#define HW_SPI_PORT_MISO		GPIOA
#define HW_SPI_PIN_MISO			6

// Measurement macros
#define ADC_V_L1				ADC_Value[ADC_IND_SENS1]
#define ADC_V_L2				ADC_Value[ADC_IND_SENS2]
#define ADC_V_L3				ADC_Value[ADC_IND_SENS3]
#define ADC_V_ZERO				(ADC_Value[ADC_IND_VIN_SENS] / 2)

// Macros
#define READ_HALL1()			palReadPad(HW_HALL_ENC_GPIO1, HW_HALL_ENC_PIN1)
#define READ_HALL2()			palReadPad(HW_HALL_ENC_GPIO2, HW_HALL_ENC_PIN2)
#define READ_HALL3()			palReadPad(HW_HALL_ENC_GPIO3, HW_HALL_ENC_PIN3)

// Override dead time.
#define HW_DEAD_TIME_NSEC		1000.0


// Setting limits
#define HW_LIM_CURRENT			-300.0, 300.0
#define HW_LIM_CURRENT_IN		-200.0, 200.0
#define HW_LIM_CURRENT_ABS		0.0, 350.0
#define HW_LIM_VIN				20.0, 120.0
#define HW_LIM_ERPM				-200e3, 200e3
#define HW_LIM_DUTY_MIN			0.0, 0.1
#define HW_LIM_DUTY_MAX			0.0, 0.95
#define HW_LIM_TEMP_FET			-40.0, 125.0

// HW-specific functions
float avesc_get_temp(void);
float aw_hw_avesc_shunt_factor(void);

#endif /* HW_AVESC_20_H_ */
