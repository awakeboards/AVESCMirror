#ifndef HW_AVESC_20_H_
#define HW_AVESC_20_H_

/////////////////////////////
/////////////////////////////
// Supported HW: AVESC 2.5 //
/////////////////////////////
/////////////////////////////

// HW properties
#define HW_HAS_3_SHUNTS
#define HW_HAS_PHASE_SHUNTS

// Macros
#define LED_GREEN_GPIO			GPIOC
#define LED_GREEN_PIN			15
#define LED_RED_GPIO			GPIOC
#define LED_RED_PIN				14

#define LED_GREEN_ON()			palSetPad(LED_GREEN_GPIO, LED_GREEN_PIN)
#define LED_GREEN_OFF()			palClearPad(LED_GREEN_GPIO, LED_GREEN_PIN)
#define LED_RED_ON()			palSetPad(LED_RED_GPIO, LED_RED_PIN)
#define LED_RED_OFF()			palClearPad(LED_RED_GPIO, LED_RED_PIN)

#define IS_DRV_FAULT()			(false)

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

#define V_REG					3.3
#define VIN_R1					47000.0
#define VIN_R2					1000.0

#define AW_SH100_CURRENT_AMP_GAIN		50.0
#define AW_SH100_CURRENT_SHUNT_RES		0.0001

#define AW_SH200_CURRENT_AMP_GAIN		20.0
#define AW_SH200_CURRENT_SHUNT_RES		0.0002

#ifndef CURRENT_AMP_GAIN
#define CURRENT_AMP_GAIN		1.0 // actual value is part of CURRENT_SHUNT_RES
#endif
#ifndef CURRENT_SHUNT_RES
#define CURRENT_SHUNT_RES		aw_hw_avesc_shunt_factor()
#endif

#define MCCONF_FOC_F_SW					30000.0

#define HW_MAX_CURRENT_OFFSET				4096	// don't check for current offset
#define MCCONF_MAX_CURRENT_UNBALANCE		100.0	// [Amp] More than this unbalance trips the fault likely a INA240 or motor damaged

// Input voltage
#define GET_INPUT_VOLTAGE()		((V_REG / 4095.0) * (float)ADC_Value[ADC_IND_VIN_SENS] * ((VIN_R1 + VIN_R2) / VIN_R2))

// NTC Termistors
#define NTC_RES(adc_val)		(10000.0 / ((4095.0 / (float)adc_val) - 1.0))
#define NTC_TEMP(adc_ind)		avesc_get_temp()

#define NTC_MOTOR_RESISTOR_DIVIDER          10000.0
#define NTC_RES_MOTOR(adc_val)	(NTC_MOTOR_RESISTOR_DIVIDER * (float)adc_val / (4096.0-(float)adc_val))

#define NTC_TEMP_MOS1()			(1.0 / ((logf(NTC_RES(ADC_Value[ADC_IND_TEMP_MOS]) / 10000.0) / 3380.0) + (1.0 / 298.15)) - 273.15)
#define NTC_TEMP_MOS2()			(1.0 / ((logf(NTC_RES(ADC_Value[ADC_IND_TEMP_MOS_2]) / 10000.0) / 3380.0) + (1.0 / 298.15)) - 273.15)
#define NTC_TEMP_MOS3()			(1.0 / ((logf(NTC_RES(ADC_Value[ADC_IND_TEMP_MOS_3]) / 10000.0) / 3380.0) + (1.0 / 298.15)) - 273.15)

// Voltage on ADC channel
#define ADC_VOLTS(ch)			((float)ADC_Value[ch] / 4096.0 * V_REG)

// Double samples in beginning and end for positive current measurement.
// Useful when the shunt sense traces have noise that causes offset.
#define CURR1_DOUBLE_SAMPLE		0
#define CURR2_DOUBLE_SAMPLE		0
#define CURR3_DOUBLE_SAMPLE		0

// Measurement macros
#define ADC_V_L1				ADC_Value[ADC_IND_SENS1]
#define ADC_V_L2				ADC_Value[ADC_IND_SENS2]
#define ADC_V_L3				ADC_Value[ADC_IND_SENS3]
#define ADC_V_ZERO				(ADC_Value[ADC_IND_VIN_SENS] / 2)

// Override dead time.
#define HW_DEAD_TIME_NSEC		300.0

// Setting limits
#define HW_LIM_CURRENT			-300.0, 300.0
#define HW_LIM_CURRENT_IN		-200.0, 200.0
#define HW_LIM_CURRENT_ABS		0.0, 350.0
#define HW_LIM_VIN				20.0, 120.0
#define HW_LIM_ERPM				-200e3, 200e3
#define HW_LIM_DUTY_MIN			0.0, 0.1
#define HW_LIM_DUTY_MAX			0.0, 0.95
#define HW_LIM_TEMP_FET			-40.0, 125.0

/////////////////////////////////////////////
// Required but unused hw configuration below
/////////////////////////////////////////////

// COMM-port ADC GPIOs
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

// I2C Peripheral
#define HW_I2C_DEV				I2CD2
#define HW_I2C_GPIO_AF			GPIO_AF_I2C2
#define HW_I2C_SCL_PORT			GPIOB
#define HW_I2C_SCL_PIN			10
#define HW_I2C_SDA_PORT			GPIOB
#define HW_I2C_SDA_PIN			11

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

#define HW_ADC_EXT_GPIO			GPIOA
#define HW_ADC_EXT_PIN			5

// ICU Peripheral for servo decoding
#define HW_USE_SERVO_TIM4
#define HW_ICU_TIMER			TIM4
#define HW_ICU_TIM_CLK_EN()		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE)
#define HW_ICU_DEV				ICUD4
#define HW_ICU_CHANNEL			ICU_CHANNEL_1
#define HW_ICU_GPIO_AF			GPIO_AF_TIM4
#define HW_ICU_GPIO				GPIOB
#define HW_ICU_PIN				6

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
#define HW_ENC_TIM_ISR_CH		TIM7_IRQn
#define HW_ENC_TIM_ISR_VEC		TIM7_IRQHandler
#define READ_HALL1()			palReadPad(HW_HALL_ENC_GPIO1, HW_HALL_ENC_PIN1)
#define READ_HALL2()			palReadPad(HW_HALL_ENC_GPIO2, HW_HALL_ENC_PIN2)
#define READ_HALL3()			palReadPad(HW_HALL_ENC_GPIO3, HW_HALL_ENC_PIN3)

/////////////////////////////////////////////
// Required but unused hw configuration above
/////////////////////////////////////////////

// this can be used by any file
extern aw_hw_type avesc_hw_type;

// HW-specific functions
float avesc_get_temp(void);
float aw_hw_avesc_shunt_factor(void);
bool aw_is_hw_supported(void);

#endif /* HW_AVESC_20_H_ */
