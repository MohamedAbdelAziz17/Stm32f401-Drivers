#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "System_Timer.h"


void CORTEXM4_SYSTICK_Init()
{
	CLR_BIT(STCTRL_REG , SYSTICK_EN_BIT); 		/*Disbale Systick*/
	
	STRELOAD_REG = 0x00FFFFFF;								/*Reload with any value*/

	STCURRENT_REG = 0;												/*Put Any Value Clears Current register + Clears Count Flag*/

	SET_BIT(STCTRL_REG , SYSTICK_CLKSRC_BIT); /*Choose system clock*/
	
	SET_BIT(STCTRL_REG , SYSTICK_EN_BIT); 		/*Enable Systick*/

}

void CORTEXM4_SYSTICK_Wait(double64_t delay_ms)
{
			/*Clear Current and Clear Flag*/
			STCURRENT_REG = 0;
		
			/*Put Calculations Reload values*/
			STRELOAD_REG = ( ( delay_ms * 1000000 ) / SYSTICK_TICK_TIME ) - 1;
	
			/*Poll on SYSTICK_COUNT_BIT*/
			while( GET_BIT(STCTRL_REG, SYSTICK_COUNT_BIT) != 1 );
				
}

void CORTEXM4_SYSTICK_Delay(uint32_t delay_ms)
{
	float32_t counter = ( (float)delay_ms / SYSTICK_MAX_TIME ) ;
	
	float32_t fractional_part = ( (counter - (uint32_t)counter) * SYSTICK_MAX_TIME ) ;
	
	for(uint8_t i = 1 ; i <= counter ; i++)
		{
			CORTEXM4_SYSTICK_Wait(SYSTICK_MAX_TIME);
		}
		
		if( fractional_part > 0 )	
		{
			CORTEXM4_SYSTICK_Wait(fractional_part+1);
		}
		
}

uint32_t CORTEXM4_SYSTICK_GetCurrentTime(void)
{
	return (SYSTICK_TICK_TIME * STCURRENT_REG);
}
