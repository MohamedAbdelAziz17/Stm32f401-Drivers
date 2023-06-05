#ifndef DIO_PROGRAM_H
#define	DIO_PROGRAM_H

#include "STD_TYPES.h"

/*GPIO PORTA Registers*/
#define GPIOA_MODER_REG			(*(volatile uint32_t*)(0x40020000))
#define GPIOA_OTYPER_REG		(*(volatile uint32_t*)(0x40020004))
#define GPIOA_OSPEED_REG		(*(volatile uint32_t*)(0x40020008))
#define GPIOA_PUPDR_REG			(*(volatile uint32_t*)(0x4002000C))
#define GPIOA_IDR_REG				(*(volatile uint32_t*)(0x40020010))
#define GPIOA_ODR_REG				(*(volatile uint32_t*)(0x40020014))
#define GPIOA_BSRR_REG			(*(volatile uint32_t*)(0x40020018))
#define GPIOA_AFRL_REG			(*(volatile uint32_t*)(0x40020020))
#define GPIOA_AFRH_REG			(*(volatile uint32_t*)(0x40020024))
	
/*GPIO PORTB Registers*/
#define GPIOB_MODER_REG			(*(volatile uint32_t*)(0x40020400))
#define GPIOB_OTYPER_REG		(*(volatile uint32_t*)(0x40020404))
#define GPIOB_OSPEED_REG		(*(volatile uint32_t*)(0x40020408))
#define GPIOB_PUPDR_REG			(*(volatile uint32_t*)(0x4002040C))
#define GPIOB_IDR_REG				(*(volatile uint32_t*)(0x40020410))
#define GPIOB_ODR_REG				(*(volatile uint32_t*)(0x40020414))
#define GPIOB_BSRR_REG			(*(volatile uint32_t*)(0x40020418))
#define GPIOB_AFRL_REG			(*(volatile uint32_t*)(0x40020420))
#define GPIOB_AFRL_REG			(*(volatile uint32_t*)(0x40020420))
#define GPIOB_AFRH_REG			(*(volatile uint32_t*)(0x40020424))
	
/*GPIO PORTC Registers*/
#define GPIOC_MODER_REG			(*(volatile uint32_t*)(0x40020800))
#define GPIOC_OTYPER_REG		(*(volatile uint32_t*)(0x40020804))
#define GPIOC_OSPEED_REG		(*(volatile uint32_t*)(0x40020808))
#define GPIOC_PUPDR_REG			(*(volatile uint32_t*)(0x4002080C))
#define GPIOC_IDR_REG				(*(volatile uint32_t*)(0x40020810))
#define GPIOC_ODR_REG				(*(volatile uint32_t*)(0x40020814))
#define GPIOC_BSRR_REG			(*(volatile uint32_t*)(0x40020818))
#define GPIOC_AFRL_REG			(*(volatile uint32_t*)(0x40020820))
#define GPIOC_AFRH_REG			(*(volatile uint32_t*)(0x40020824))

/*RCC Clock Enable Register*/
#define RCC_AHB1ENR_REG			(*(volatile uint32_t*)(0x40023830))

/*Pin Mode*/
#define _IO_INPUT						0
#define _IO_OUTPUT					1
#define _IO_ALT_FUNC_MODE		2
#define _IO_ANALOG_MODE			3

/*Output Type*/
#define _IO_PUSH_PULL			0
#define _IO_OPEN_DRAIN		1

/*Output Speed*/
#define _IO_LOW_SPEED				0
#define _IO_MED_SPEED				1
#define _IO_HIGH_SPEED			2
#define _IO_VHIGH_SPEED			3

/*Input Type*/
#define _IO_NO_PULL_UP_DOWN			0
#define _IO_PULL_UP							1
#define _IO_PULL_DOWN						2

/*Pin States*/
#define _IO_PIN_HIGH	1
#define _IO_PIN_LOW		0

typedef enum
{
	_IO_PIN0,
	_IO_PIN1,
	_IO_PIN2,
	_IO_PIN3,
	_IO_PIN4,
	_IO_PIN5,
	_IO_PIN6,
	_IO_PIN7,
	_IO_PIN8,
	_IO_PIN9,
	_IO_PIN10,
	_IO_PIN11,
	_IO_PIN12,
	_IO_PIN13,
	_IO_PIN14,
	_IO_PIN15
	
} GPIO_Pin_t;

typedef enum
{
	_IO_GPIOA,
	_IO_GPIOB,
	_IO_GPIOC
	
} GPIO_PORT_t;

typedef enum
{
	AF0_SYSTEM,
	AF1_TIM1_2,
	AF2_TIM3_5,
	AF3_TIM9_11,
	AF4_I2C1_3,
	AF5_SPI1_4,
	AF6_SPI3,
	AF7_USART1_2,
	AF8_USART16,
	AF9_I2C2_2,
	AF12_SDIO,
	
} GPIO_ALT_FUNC_t;

void MCAL_GPIO_PIN_OUTPUT(GPIO_PORT_t PORT  ,GPIO_Pin_t u8Pin , uint8_t u8Output_Type, uint8_t u8_Input_Type ,uint8_t	u8Output_Speed);

void MCAL_GPIO_PIN_INPUT(GPIO_PORT_t PORT  ,GPIO_Pin_t u8Pin , uint8_t u8_Input_Type);

void MCAL_GPIO_WRITE_PIN(GPIO_PORT_t Port , GPIO_Pin_t u8Pin , uint8_t u8Pin_State);

uint8_t MCAL_GPIO_READ_PIN(GPIO_PORT_t Port , GPIO_Pin_t u8Pin);

void MCAL_GPIO_PIN_ALTERNATIVE(GPIO_PORT_t Port , GPIO_Pin_t u8Pin ,GPIO_ALT_FUNC_t u8Alt_Func);

void MCAL_GPIO_PIN_AnalogMode(GPIO_PORT_t Port , GPIO_Pin_t u8Pin);

#endif


