#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_DRIV.h"
#include "WWDG_DRIV.h"


void MCAL_WWDG_Init(Wdg_ConfigType user_config)
{
	MCAL_RCC_ClockEnable(WWDG);
	
	/*Set Prescalar*/
	WWDG_CFR->REG_BITS.WDGTB = 3;
	
	/*Set Window Value*/
	
	
}

void MCAL_WWDG_Start(void)
{
	/*Set Activiation Bit*/
	
}

void MCAL_WWDG_Stop(void)
{
	/*Clear Activiation Bit*/
	
}

void MCAL_WWDG_Refresh(uint8_t timeout)
{
	/*Reload Counter Value*/
	
}
