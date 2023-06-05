

#ifndef RCC_DRIV_H_
#define RCC_DRIV_H_

#include "STD_TYPES.h"
#include "NVIC_DRIV.h"
#include "CPU_CONFIGURATIONS.h"




/*DEFINES*/
#define Clock_HSE 		0
#define Clock_HSI 		1

#define PLL_Enable 		0
#define PLL_Disable 	1



#if USER_PLL == PLL_Enable
#define F_CPU 84000000UL				/***Configurable***/

#elif USER_PLL == PLL_Disable
#if USER_CLOCK == Clock_HSE
#define F_CPU F_HSE
#elif USER_CLOCK == Clock_HSI
#define F_CPU F_HSI
#endif

#endif
/************************************/



#define PWR_BASE_ADDR					0x40007000
#define PWR_CR_REG						(*(volatile uint32_t*)(PWR_BASE_ADDR + 0x00))
#define PWR_CSR_REG						(*(volatile uint32_t*)(PWR_BASE_ADDR + 0x04))
	

/*REGISTERS used in Reset Clock Control RCC*/
#define RCC_BASE_ADDR					0x40023800 

/*RCC CR REGISTER*/
typedef struct
{
	uint32_t HSION		:1;
	uint32_t HSIRDY		:1;
	uint32_t 					:1;
	uint32_t HSITRIM	:5;
	uint32_t HSICAL		:8;
	uint32_t HSEON		:1;
	uint32_t HSERDY		:1;
	uint32_t HSEBYP		:1;
	uint32_t CSSON		:1;
	uint32_t 					:4;
	uint32_t PLLON		:1;
	uint32_t PLLRDY		:1;
	uint32_t PLLI2SON	:1;
	uint32_t PLLI2SRDY:1;
	uint32_t 					:4;
	
}RCC_CR_StrType;

typedef union
{
	uint32_t REG;
	RCC_CR_StrType REG_BITS;
	
}RCC_CR_TAG;

#define RCC_CR 	(( volatile RCC_CR_TAG * ) (RCC_BASE_ADDR + 0x00))

/*RCC PLL configuration REGISTER*/
typedef struct
{
	uint32_t SW			:2;
	uint32_t SWS		:2;
	uint32_t HPRE		:4;
	uint32_t 				:2;
	uint32_t PPRE1	:3;
	uint32_t PPRE2	:3;
	uint32_t RTCPRE	:5;
	uint32_t MCO1		:2;
	uint32_t I2SSC	:1;
	uint32_t MCO1PRE:3;
	uint32_t MCO2PRE:3;
	uint32_t MCO2		:2;
	
}RCC_CFGR_StrType;

typedef union
{
	uint32_t REG;
	RCC_CFGR_StrType REG_BITS;
	
}RCC_CFGR_TAG;

#define RCC_CFGR 	(( volatile RCC_CFGR_TAG * ) (RCC_BASE_ADDR + 0x08))

/*RCC clock configuration REGISTER*/
typedef struct
{
	uint32_t PLLM			:6;
	uint32_t PLLN			:9;
	uint32_t 					:1;
	uint32_t PLLP			:2;
	uint32_t 					:4;
	uint32_t PLLSRC		:1;
	uint32_t 					:1;
	uint32_t PLLQ			:4;
	uint32_t 					:4;
	
}RCC_PLLCFGR_StrType;

typedef union
{
	uint32_t REG;
	RCC_PLLCFGR_StrType REG_BITS;
	
}RCC_PLLCFGR_TAG;

#define RCC_PLLCFGR 	(( volatile RCC_PLLCFGR_TAG * ) (RCC_BASE_ADDR + 0x04))

/*RCC AHB1 peripheral reset Register*/
typedef struct
{
	uint32_t GPIOARST		:1;
	uint32_t GPIOBRST		:1;
	uint32_t GPIOCRST		:1;
	uint32_t GPIODRST		:1;
	uint32_t GPIOERST		:1;
	uint32_t 						:2;
	uint32_t GPIOHRST	:1;
	uint32_t 						:4;
	uint32_t CRCRST			:1;
	uint32_t 						:8;
	uint32_t DMA1RST		:1;
	uint32_t DMA2RST		:1;
	uint32_t 						:9;

	
}RCC_AHB1RSTR_StrType;

typedef union
{
	uint32_t REG;
	RCC_AHB1RSTR_StrType REG_BITS;
	
}RCC_AHB1RSTR_TAG;

#define RCC_AHB1RSTR 	(( volatile RCC_AHB1RSTR_TAG * ) (RCC_BASE_ADDR + 0x10))

/*RCC APB1 peripheral reset Register*/
typedef struct
{
	uint32_t TIM2RST		:1;
	uint32_t TIM3RST		:1;
	uint32_t TIM4RST		:1;
	uint32_t TIM5RST		:1;
	uint32_t 						:7;
	uint32_t WWDGRST		:1;
	uint32_t 						:2;
	uint32_t SPI2RST		:1;
	uint32_t SPI3RST		:1;
	uint32_t 						:1;
	uint32_t USART2RST	:1;
	uint32_t 						:3;
	uint32_t I2C1RST		:1;
	uint32_t I2C2RST		:1;
	uint32_t I2C3RST		:1;
	uint32_t 						:4;
	uint32_t PWRRST			:1;
	uint32_t 						:3;
	
}RCC_APB1RSTR_StrType;

typedef union
{
	uint32_t REG;
	RCC_APB1RSTR_StrType REG_BITS;
	
}RCC_APB1RSTR_TAG;

#define RCC_APB1RSTR 	(( volatile RCC_APB1RSTR_TAG * ) (RCC_BASE_ADDR + 0x20))

/*RCC APB2 peripheral reset Register*/
typedef struct
{
	uint32_t TIM1RST		:1;
	uint32_t 						:3;
	uint32_t USART1RST	:1;
	uint32_t USART6RST	:1;
	uint32_t 						:2;
	uint32_t ADC1RST		:1;
	uint32_t 						:2;
	uint32_t SDIORST		:1;
	uint32_t SPI1RST		:1;
	uint32_t SPI4RST		:1;
	uint32_t SYSCFGRST	:1;
	uint32_t 						:1;
	uint32_t TIM9RST		:1;
	uint32_t TIM10RST		:1;
	uint32_t TIM11RST		:1;
	uint32_t 						:13;
	
}RCC_APB2RSTR_StrType;

typedef union
{
	uint32_t REG;
	RCC_APB2RSTR_StrType REG_BITS;
	
}RCC_APB2RSTR_TAG;

#define RCC_APB2RSTR	(( volatile RCC_APB2RSTR_TAG * ) (RCC_BASE_ADDR + 0x24))

/*RCC clock control & status Register*/
typedef struct
{
	uint32_t LSION		:1;
	uint32_t LSIRDY		:1;
	uint32_t 					:22;
	uint32_t RMVF			:1;
	uint32_t BORRSTF	:1;
	uint32_t PINRSTF	:1;
	uint32_t PORRSTF	:1;
	uint32_t SFTRSTF	:1;
	uint32_t WDGRSTF	:8;
	uint32_t WWDGRSTF	:1;
	uint32_t LPWRRSTF	:1;
	
}RCC_CSR_StrType;

typedef union
{
	uint32_t REG;
	RCC_CSR_StrType REG_BITS;
	
}RCC_CSR_TAG;

#define RCC_CSR 	(( volatile RCC_CSR_TAG * ) (RCC_BASE_ADDR + 0x74))

/*RCC AHB1 peripheral Clock Enable Register*/
typedef struct
{
	uint32_t GPIOAEN		:1;
	uint32_t GPIOBEN		:1;
	uint32_t GPIOCEN		:1;
	uint32_t GPIODEN		:1;
	uint32_t GPIOEEN		:1;
	uint32_t 						:2;
	uint32_t GPIOHEN		:1;
	uint32_t 						:4;
	uint32_t CRCEN			:1;
	uint32_t 						:8;
	uint32_t DMA1EN			:1;
	uint32_t DMA2EN			:1;
	uint32_t 						:9;

	
}RCC_AHB1ENR_StrType;

typedef union
{
	uint32_t REG;
	RCC_AHB1ENR_StrType REG_BITS;
	
}RCC_AHB1ENR_TAG;

#define RCC_AHB1ENR 	(( volatile RCC_AHB1ENR_TAG * ) (RCC_BASE_ADDR + 0x30))


/*RCC APB1 peripheral Clock Enable Register*/
typedef struct
{
	uint32_t TIM2EN		:1;
	uint32_t TIM3EN		:1;
	uint32_t TIM4EN		:1;
	uint32_t TIM5EN		:1;
	uint32_t 					:7;
	uint32_t WWDGEN		:1;
	uint32_t 					:2;
	uint32_t SPI2EN		:1;
	uint32_t SPI3EN		:1;
	uint32_t 					:1;
	uint32_t USART2EN	:1;
	uint32_t 					:3;
	uint32_t I2C1EN		:1;
	uint32_t I2C2EN		:1;
	uint32_t I2C3EN		:1;
	uint32_t 					:4;
	uint32_t PWREN		:1;
	uint32_t 					:3;
	
}RCC_APB1ENR_StrType;

typedef union
{
	uint32_t REG;
	RCC_APB1ENR_StrType REG_BITS;
	
}RCC_APB1ENR_TAG;

#define RCC_APB1ENR 	(( volatile RCC_APB1ENR_TAG * ) (RCC_BASE_ADDR + 0x40))

/*RCC APB2 peripheral Clock Enable Register*/
typedef struct
{
	uint32_t TIM1EN		:1;
	uint32_t 					:3;
	uint32_t USART1EN	:1;
	uint32_t USART6EN	:1;
	uint32_t 					:2;
	uint32_t ADC1EN		:1;
	uint32_t 					:2;
	uint32_t SDIOEN		:1;
	uint32_t SPI1EN		:1;
	uint32_t SPI4EN		:1;
	uint32_t SYSCFGEN	:1;
	uint32_t 					:1;
	uint32_t TIM9EN		:1;
	uint32_t TIM10EN	:1;
	uint32_t TIM11EN	:1;
	uint32_t 					:13;
	
}RCC_APB2ENR_StrType;

typedef union
{
	uint32_t REG;
	RCC_APB2ENR_StrType REG_BITS;
	
}RCC_APB2ENR_TAG;

#define RCC_APB2ENR	(( volatile RCC_APB2ENR_TAG * ) (RCC_BASE_ADDR + 0x44))





/*Peripherals to CHOOSE*/
typedef enum
{	
	GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOH,
	DMA1 , DMA2,	/*0 --> 7*/
	
	TIM2, TIM3 , TIM4, TIM5,
	SPI2, SPI3,
	WWDG,
	USART2,
	I2C1 , I2C2, I2C3,
	PWR,	/*8 --> 19*/
	
	SYSCFG,
	ADC1,
	SDIO,
	TIM1, TIM9, TIM10, TIM11,
	USART1, USART6,
	SPI1, SPI4, /*20 --> 30*/

}enumPeripherals_t;

/*Peripherals Reset/Enable BITS*/
typedef enum
{
	/*AHB1*/
	GPIOARST = 0, GPIOBRST = 1, GPIOCRST = 2, GPIODRST = 3, GPIOERST = 4, GPIOHRST = 5,
	DMA1RST = 6, DMA2RST = 7,
	
	/*APB1*/
	TIM2RST = 0, TIM3RST = 1, TIM4RST = 2, TIM5RST = 3,
	SPI2RST = 14 , SPI3RST = 15,
	WWDGRST = 11,
	USART2RST = 17,
	I2C1RST = 21, I2C2RST = 22, I2C3RST = 23,
	PWRRST = 28,
	
	/*APB2*/
	ADC1RST = 8,
	SDIORST = 11,
	TIM1RST = 0,TIM9RST = 16, TIM10RST = 17, TIM11RST = 18,
	USART1RST = 4,  USART6RST = 5,
	SPI1RST = 11, SPI4RST = 12,SYSCFGEN = 14

}enumPeripheralsBITS_t;



/*Reset Functions Prototypes*/
void MCAL_RCC_SystemReset(void);

void MCAL_RCC_PerphReset(enumPeripherals_t Perph);

uint8_t MCAL_RCC_GetResetFlag(void);
/****************************/

/*Clock Functions Prototypes*/
void MCAL_RCC_ClockEnable(uint8_t Peripheral);

void MCAL_RCC_Clock_Config(void);


#endif



/*
#define RCC_BASE_ADDR					(*(volatile uint32_t *) (0x40023800)) 

#define RCC_CR_REG						RCC_BASE_ADDR[0]
#define RCC_PLLCFGR_REG				RCC_BASE_ADDR[1]
#define RCC_CFGR_REG					RCC_BASE_ADDR[2]
#define RCC_CIR_REG						RCC_BASE_ADDR[3]
#define RCC_AHB1RSTR_REG			RCC_BASE_ADDR[4]
#define RCC_AHB2RSTR_REG			RCC_BASE_ADDR[5]
#define RCC_APB1RSTR_REG			RCC_BASE_ADDR[6]
#define RCC_APB2RSTR_REG			RCC_BASE_ADDR[7]
#define RCC_AHB1ENR_RE				RCC_BASE_ADDR[8]
#define RCC_AHB2ENR_REG				RCC_BASE_ADDR[9]
#define RCC_AHB1LPENR_REG			RCC_BASE_ADDR[10]
#define RCC_AHB2LPENR_REG			RCC_BASE_ADDR[11]
#define RCC_APB1LPENR_REG			RCC_BASE_ADDR[12]
#define RCC_APB2LPENR_REG			RCC_BASE_ADDR[13]
#define RCC_BDCR_REG					RCC_BASE_ADDR[14]
#define RCC_CSR_REG						RCC_BASE_ADDR[15]
#define RCC_SSCGR_REG					RCC_BASE_ADDR[16]
#define RCC_PLLI2SCFGR_REG		RCC_BASE_ADDR[16]
#define RCC_DCKCFGR_REG				RCC_BASE_ADDR[16]
*/
