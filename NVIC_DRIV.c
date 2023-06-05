
#include "STD_TYPES.h"
#include "CPU_CONFIGURATIONS.h"
#include "BIT_MATH.h"
#include "NVIC_DRIV.h"
#include "cmsis_armcc.h"




/******FUNCTIONS IMPLEMENTATION******/
void CORTEXM4_NVIC_EnableIRQ(IRQn_Type IRQ_NUM)
{
	( NVIC_ISER0_REG[ (IRQ_NUM / 32) ] ) = 1 << (IRQ_NUM % 32); 
}

void CORTEXM4_NVIC_DisableIRQ(IRQn_Type IRQ_NUM)
{
	( NVIC_ICER0_REG[ (IRQ_NUM / 32) ] ) = 1 << (IRQ_NUM % 32);
}

void CORTEXM4_NVIC_SetPending(IRQn_Type IRQ_NUM)
{
	( NVIC_ISPR0_REG[ (IRQ_NUM / 32) ] ) = 1 << (IRQ_NUM % 32);
}

void CORTEXM4_NVIC_ClearPending(IRQn_Type IRQ_NUM)
{
	( NVIC_ICPR0_REG[ (IRQ_NUM / 32) ] ) = 1 << (IRQ_NUM % 32);
}

uint32_t CORTEXM4_NVIC_GetPending(IRQn_Type IRQ_NUM)
{
	/*1: Pending , 0: Not Pending*/
	return (( NVIC_IABR0_REG[ (IRQ_NUM / 32) ] ) >> (IRQ_NUM % 32)) & 1;
}

uint32_t CORTEXM4_NVIC_GetActive(uint8_t IRQ_NUM)
{
	/*1: Active , 0: Not Active*/
	return (( NVIC_IABR0_REG[ (IRQ_NUM / 32) ] ) >> (IRQ_NUM % 32)) & 1;
}

uint32_t CORTEXM4_PSR_GetIRQ(void)
{
	uint32_t ISR_n = 0;
	
	__ASM("MRS R0, PSR");
	
	__ASM("mov ISR_n, R0");
	
	ISR_n = (ISR_n & 0xFF) - 16;
	
	return ISR_n ;
}

void CORTEXM4_NVIC_Trigger(IRQn_Type IRQ_NUM)
{
	*NVIC_STIR_REG = IRQ_NUM;
}

void CORTEXM4_NVIC_SetPriority(IRQn_Type IRQ_NUM , uint8_t PRIO_N)
{
	( NVIC_IPR0_REG[ ((uint32_t)IRQ_NUM >> 2UL) ] ) =  ( ((uint32_t)PRIO_N << 4UL) << (((uint32_t)IRQ_NUM % 4UL)*8) ) ; 
}


void CORTEXM4_SCB_PRIORITY_GROUPING(uint8_t PRI_GROUP)
{
	switch(PRI_GROUP)
	{
		case PRI_GR_x_x_x_x: 
												
			SCB_AIRCR_REG = (SCB_AIRCR_REG & 0xF8FF) | ((0x5FA << 16) | (0UL << 8));
		break;
		
		case PRI_GR_x_x_x_y: 
												
			SCB_AIRCR_REG = (SCB_AIRCR_REG & 0xF8FF) | ((0x5FA << 16) | (4UL << 8));
		break;
		
		case PRI_GR_x_x_y_y:  
												
			SCB_AIRCR_REG = (SCB_AIRCR_REG & 0xF8FF) | ((0x5FA << 16) | (5UL << 8));
		break;
		
		case PRI_GR_x_y_y_y: 
												
			SCB_AIRCR_REG = (SCB_AIRCR_REG & 0xF8FF) | ((0x5FA << 16) | (6UL << 8));
		break;
		
		case PRI_GR_y_y_y_y: 
													
			SCB_AIRCR_REG = (SCB_AIRCR_REG & 0xF8FF) | ((0x5FA << 16) | (7UL << 8));
		break;
		
		default: break;
		
	}
	
}
/*****************************************************/
