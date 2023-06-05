#ifndef SYSTEM_TIMER_H
#define	SYSTEM_TIMER_H

#include "STD_TYPES.h"
#include "RCC_DRIV.h"

/*SYSTEM TIMER REGISTERS*/
#define STCTRL_REG			(*(volatile uint32_t*)(0xE000E010))
#define STRELOAD_REG		(*(volatile uint32_t*)(0xE000E014))
#define STCURRENT_REG		(*(volatile uint32_t*)(0xE000E018))
	
/*STCTRL_REG BITS*/
#define SYSTICK_EN_BIT			0
#define SYSTICK_INTEN_BIT		1
#define SYSTICK_CLKSRC_BIT	2
#define SYSTICK_COUNT_BIT		16


/*SYSTICK_TICK_TIME = (pow(10,9) / F_CPU)*/
/*SYSTICK_MAX_TIME  = (pow(2,24)*1000 / F_CPU*/


#define F_CPU_HZ 	(F_CPU / 1000000UL)	
#define SYSTICK_TICK_TIME 	((float)1000 / F_CPU_HZ)
#define SYSTICK_MAX_TIME		((float)16777215 / (float)(F_CPU_HZ * 1000UL))

void CORTEXM4_SYSTICK_Init(void);

void CORTEXM4_SYSTICK_Wait(double64_t delay_ms);

void CORTEXM4_SYSTICK_Delay(uint32_t delay_ms);

uint32_t CORTEXM4_SYSTICK_GetCurrentTime(void);


#endif







