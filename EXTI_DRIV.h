

#ifndef EXTI_DRIV_H_
#define EXTI_DRIV_H_

#include "STD_TYPES.h"
#include "DIO_PROGRAM.h"

/*****Registers used in EXTI*****/
#define EXTI_BASE 	0x40013C00

#define EXTI_IMR_REG						( * ( volatile uint32_t * ) ( EXTI_BASE + 0x00 ) )
#define EXTI_EMR_REG						( * ( volatile uint32_t * ) ( EXTI_BASE + 0x04 ) )
#define EXTI_RTSR_REG						( * ( volatile uint32_t * ) ( EXTI_BASE + 0x08 ) )
#define EXTI_FTSR_REG						( * ( volatile uint32_t * ) ( EXTI_BASE + 0x0C ) )
#define EXTI_SWIER_REG					( * ( volatile uint32_t * ) ( EXTI_BASE + 0x10 ) )
#define EXTI_PR_REG							( * ( volatile uint32_t * ) ( EXTI_BASE + 0x14 ) )

#define SYSCFG_BASE	0x40013800

#define SYSCFG_EXTICR1_REG			(  ( volatile uint32_t * ) ( SYSCFG_BASE + 0x08 ) )
#define SYSCFG_EXTICR2_REG			(  ( volatile uint32_t * ) ( SYSCFG_BASE + 0x0C ) )
#define SYSCFG_EXTICR3_REG			(  ( volatile uint32_t * ) ( SYSCFG_BASE + 0x10 ) )
#define SYSCFG_EXTICR4_REG			(  ( volatile uint32_t * ) ( SYSCFG_BASE + 0x14 ) )
	

typedef enum
{
	EXTI_LINE0,  EXTI_LINE1,  EXTI_LINE2,
	EXTI_LINE3,  EXTI_LINE4,  EXTI_LINE5,
	EXTI_LINE6,  EXTI_LINE7,  EXTI_LINE8,
	EXTI_LINE9,  EXTI_LINE10, EXTI_LINE11,
	EXTI_LINE12, EXTI_LINE13, EXTI_LINE14,
	EXTI_LINE15, EXTI_LINE16, EXTI_LINE17,
	EXTI_LINE18, EXTI_LINE19, EXTI_LINE20,
	EXTI_LINE21, EXTI_LINE22
	
}EXTI_LINES_t;


typedef enum
{
	EXTI_RISING,
	EXTI_FALLING
	
}EXTI_EDGE_t;


typedef enum
{
	EXTI_INTERRUPT,
	EXTI_EVENT
	
}EXTI_INTR_EVENT_t;


void MCAL_EXTI_Config (GPIO_PORT_t Port ,GPIO_Pin_t Pin , EXTI_EDGE_t Edge_Select);

void MCAL_EXTI_Trigger(EXTI_LINES_t Line_Num);

uint8_t MCAL_EXTI_GetPending(void);











#endif
