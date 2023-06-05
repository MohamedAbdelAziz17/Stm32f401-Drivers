#ifndef TIMER_DRIV_H_
#define TIMER_DRIV_H_

#include "STD_TYPES.h"


/*Power Clock in RCC*/
#define CLK_EN_TIM1 23
#define CLK_EN_TIM2 8
#define CLK_EN_TIM3 9
#define CLK_EN_TIM4 10
#define CLK_EN_TIM5 11
#define CLK_EN_TIM9  24
#define CLK_EN_TIM10 25
#define CLK_EN_TIM11 26




/*TIMERS BASE ADDRESSES*/
#define TIM1_BASEADDR		0x40010000

#define TIM2_BASEADDR		0x40000000
#define TIM3_BASEADDR		0x40000400
#define TIM4_BASEADDR		0x40000800
#define TIM5_BASEADDR		0x40000C00

#define TIM9_BASEADDR		0x40014000
#define TIM10_BASEADDR	0x40000400
#define TIM11_BASEADDR	0x40000800



/*TIMERS REGISTERS OFFSET*/
#define TIMx_CR1_OFFSET			0x00
#define TIMx_CR2_OFFSET			0x04
#define TIMx_SMCR_OFFSET		0x08
#define TIMx_DIER_OFFSET		0x0C
#define TIMx_SR_OFFSET			0x10
#define TIMx_EGR_OFFSET			0x14
#define TIMx_CCMR1_OFFSET		0x18
#define TIMx_CCMR2_OFFSET		0x1C
#define	TIMx_CCER_OFFSET		0x20
#define TIMx_CNT_OFFSET			0x24
#define TIMx_PSC_OFFSET			0x28
#define TIMx_ARR_OFFSET			0x2C
#define TIMx_RCR_OFFSET			0x30
#define TIMx_CCR1_OFFSET		0x34
#define TIMx_CCR2_OFFSET		0x38 
#define TIMx_CCR3_OFFSET		0x3C
#define TIMx_CCR4_OFFSET		0x40
#define TIMx_BDTR_OFFSET		0x44	


/*Configurations*/
#define UP_COUNT 			0
#define DOWN_COUNT 		1

#define PWM_MODE_1 	0
#define PWM_MODE_2 	1

#define TIMER_POLLING 	0
#define TIMER_INTERRUPT 1
#define TIMER_PWM				3
#define TIMER_ICU				4
#define TIMER_OnePulse	5

typedef enum
{
	_TIM1,
	_TIM2,
	_TIM3,
	_TIM4,
	_TIM5,
	_TIM9,
	_TIM10,
	_TIM11,
	
}enumTIM_t;

typedef enum
{
	CCR1,
	CCR2,
	CCR3,
	CCR4
	
}enumTIMCCRx_t;

typedef struct
{
	enumTIM_t TIMER_NUM;
	enumTIMCCRx_t	TIMER_PWM_CH;
	uint8_t 	TIMER_DIR;
	uint8_t 	TIMER_MODE;
	
}strCONFIG_t;




/*Functions Prototypes*/
void 		    MCAL_TIMER_Init(strCONFIG_t* config);

void	 		  MCAL_TIMER_PollingDelay(strCONFIG_t* config, uint32_t delay);

void 				MCAL_TIMER_InterruptDelay(strCONFIG_t* config, void (*CallBackFunc)(void) ,uint32_t delay);
	
uint16_t	  MCAL_TIMER_GetCurrentTime(strCONFIG_t* config);

void 				MCAL_TIMER_PWMInit(strCONFIG_t* config);

void 				MCAL_TIMER_SetPWM(strCONFIG_t* config ,uint16_t freq ,float32_t duty_cycle);

uint16_t 		MCAL_TIMER_ICU(strCONFIG_t* config);

void 				MCAL_TIMER_OnePulseInit(strCONFIG_t* config);

void 				MCAL_TIMER_OnePulse(strCONFIG_t* config ,uint16_t delay ,uint16_t length);




#endif
