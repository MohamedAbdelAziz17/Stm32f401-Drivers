#include "STD_TYPES.h"
#include "CPU_CONFIGURATIONS.h"
#include "BIT_MATH.h"
#include "EXTI_DRIV.h"
#include "RCC_DRIV.h"

const uint32_t ArrNVIC_Num[] = {EXTI0_IRQn,EXTI1_IRQn,EXTI2_IRQn,EXTI3_IRQn,EXTI4_IRQn,
																EXTI9_5_IRQn , EXTI9_5_IRQn , EXTI9_5_IRQn , EXTI9_5_IRQn , EXTI9_5_IRQn , EXTI15_10_IRQn, 
																EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn};

void MCAL_EXTI_Config (GPIO_PORT_t Port ,GPIO_Pin_t Pin , EXTI_EDGE_t Edge_Select)
{
	/*Enable NVIC Gate*/
	CORTEXM4_NVIC_EnableIRQ(ArrNVIC_Num[Pin]);
	
	/*Enable Clock to System Configuration*/
	MCAL_RCC_ClockEnable(SYSCFG);
	
	/*Enable Clock to GPIO*/
	switch(Port)
	{
		case _IO_GPIOA:
			MCAL_RCC_ClockEnable(GPIOA);
		break;
		
		case _IO_GPIOB:
			MCAL_RCC_ClockEnable(GPIOB);
		break;
		
		case _IO_GPIOC:
			MCAL_RCC_ClockEnable(GPIOC);
		break;
		default:break;
	}
	
	
	
	
	/*Choose Event or Interrupt*/
	/*if(INTR_EVENT_Select == EXTI_EVENT)
	{
		EXTI_EMR_REG |= (1 << Pin); 
	}
	else
	{
		EXTI_IMR_REG |= (1 << Pin); 
	}*/
	
	/*Choose Interrupt*/
	EXTI_IMR_REG |= (1 << Pin); 
	
	/*Choose Edge*/
	if(Edge_Select == EXTI_RISING)
	{
		EXTI_RTSR_REG |= (1 << Pin);
	}
	else
	{
		EXTI_FTSR_REG |= (1 << Pin);
	}
	
	/*Configure Pin*/
	MCAL_GPIO_PIN_INPUT(Port  , (GPIO_Pin_t)Pin , _IO_PULL_DOWN);
	
	/*Choose the Pin to be Source for External Line*/
	SYSCFG_EXTICR1_REG[Pin >> 2] = Port << ((Pin % 4) * 4);
	
}

void MCAL_EXTI_Trigger(EXTI_LINES_t Line_Num)
{
	EXTI_SWIER_REG |= (1 << Line_Num);
}

uint8_t MCAL_EXTI_GetPending(void)
{
	return EXTI_PR_REG;
}
/*****************************************************/
