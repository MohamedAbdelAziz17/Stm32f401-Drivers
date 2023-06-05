#ifndef IWDG_DRIV_H_
#define IWDG_DRIV_H_

#include "STD_TYPES.h"


#define IWDG_KR_REG		(*(volatile uint32_t*)(0x40003000))
#define IWDG_PR_REG		(*(volatile uint32_t*)(0x40003004))
#define IWDG_RLR_REG	(*(volatile uint32_t*)(0x40003008))
#define IWDG_SR_REG		(*(volatile uint32_t*)(0x4000300C))
	
#define SR_PVU	0
#define SR_RVU	1
	
#define IWDG_START_COUNT				0xCCCC
#define IWDG_RELOAD							0xAAAA
#define IWDG_WRITE_ACCESS				0x5555

typedef enum
{
	DIVIDER4,
	DIVIDER8,
	DIVIDER16,
	DIVIDER32,
	DIVIDER64,
	DIVIDER128,
	DIVIDER256,

}IWDG_PRE;

#define PRESCALAR_CONFIG	DIVIDER32


void MCAL_IWDG_Init(uint16_t value);

void MCAL_IWDG_Start(void);

void MCAL_IWDG_Refresh(void);














#endif
