

#ifndef NVIC_DRIV_H_
#define NVIC_DRIV_H_

#include "STD_TYPES.h"
#include "CPU_CONFIGURATIONS.h"


/*****Registers used in NVIC*****/

/*NVIC SET ENABLE REGISTERS*/
#define NVIC_ISER0_REG					(  ( volatile uint32_t * ) ( 0xE000E100 ) )

/*NVIC CLR ENABLE REGISTERS*/
#define NVIC_ICER0_REG					(  ( volatile uint32_t * ) ( 0xE000E180 ) )

/*NVIC SET PENDING REGISTERS*/
#define NVIC_ISPR0_REG					(  ( volatile uint32_t * ) ( 0xE000E200 ) )

/*NVIC CLEAR PENDING REGISTERS*/
#define NVIC_ICPR0_REG					(  ( volatile uint32_t * ) ( 0xE000E280 ) )

/*NVIC GET ACTIVE REGISTERS*/
#define NVIC_IABR0_REG					(  ( volatile uint32_t * ) ( 0xE000E300 ) )

/*NVIC SOFTWARE TRIGGER INTERRUPT REGISTER:*/
#define NVIC_STIR_REG						(  ( volatile uint32_t * ) ( 0xE000EF00 ) )

/*SYSTEM CONTROL BLOCK: SCR REGISTER*/
/*Set bit 1 to trigger any interrupt in unprivilege mode*/
#define SCB_CCR_REG							( * ( volatile uint32_t * ) ( 0xE000ED14 ) )

/*NVIC INTERRUPT PRIORITY REGISTERS*/
#define NVIC_IPR0_REG						(  ( volatile uint32_t * ) ( 0xE000E400 ) )

/*SCB PRIORITY GROUPING*/
#define SCB_AIRCR_REG						( * ( volatile uint32_t * ) (  0xE000ED0C ) )
#define PRI_GR_x_x_x_x		0		/*GROUP BITS [7:4] , SUB GROUP NONE*/
#define PRI_GR_x_x_x_y		1		/*GROUP BITS [7:5] , SUB GROUP [4]*/
#define PRI_GR_x_x_y_y		2		/*GROUP BITS [7:6] , SUB GROUP [5:4]*/
#define PRI_GR_x_y_y_y		3		/*GROUP BITS [7] 	 , SUB GROUP [6:4]*/
#define PRI_GR_y_y_y_y		4		/*GROUP BITS NONE  , SUB GROUP [7:4]*/

void CORTEXM4_NVIC_EnableIRQ(IRQn_Type IRQ_NUM);

void CORTEXM4_NVIC_DisableIRQ(IRQn_Type IRQ_NUM);

void CORTEXM4_NVIC_SetPending(IRQn_Type IRQ_NUM);

void CORTEXM4_NVIC_ClearPending(IRQn_Type IRQ_NUM);

uint32_t CORTEXM4_NVIC_GetPending(IRQn_Type IRQ_NUM);

uint32_t CORTEXM4_NVIC_GetActive(uint8_t IRQ_NUM);

uint32_t CORTEXM4_PSR_GetIRQ(void);

void CORTEXM4_NVIC_Trigger(IRQn_Type IRQ_NUM);

void CORTEXM4_NVIC_SetPriority(IRQn_Type IRQ_NUM , uint8_t PRIO_N);

void CORTEXM4_SCB_PRIORITY_GROUPING(uint8_t PRI_GROUP);











#endif
