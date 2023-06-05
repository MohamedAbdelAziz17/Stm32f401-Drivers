#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "IWDG_DRIV.h"


void MCAL_IWDG_Init(uint16_t value)
{
	IWDG_KR_REG = IWDG_WRITE_ACCESS;
	
	while( GET_BIT(IWDG_SR_REG , SR_PVU) != 0);
	
	IWDG_PR_REG = PRESCALAR_CONFIG;
	
	while( GET_BIT(IWDG_SR_REG , SR_RVU) != 0);
	
	IWDG_RLR_REG = value;
	
}

void MCAL_IWDG_Start(void)
{
	IWDG_KR_REG = IWDG_START_COUNT;
}

void MCAL_IWDG_Refresh(void)
{
	IWDG_KR_REG = IWDG_RELOAD;
}
