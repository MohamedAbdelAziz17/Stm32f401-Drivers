#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_DRIV.h"
#include "TIMER_DRIV.h"
#include "NVIC_DRIV.h"
#include "UART.h"
#include "DIO_PROGRAM.h"

typedef volatile uint32_t* vol_u32ptr;


void (*timer1_ptr_to_fn)(void) 	= (void*)0;
void (*timer2_ptr_to_fn)(void) 	= (void*)0;
void (*timer3_ptr_to_fn)(void) 	= (void*)0;
void (*timer4_ptr_to_fn)(void) 	= (void*)0;
void (*timer5_ptr_to_fn)(void) 	= (void*)0;
void (*timer9_ptr_to_fn)(void) 	= (void*)0;
void (*timer10_ptr_to_fn)(void) = (void*)0;
void (*timer11_ptr_to_fn)(void) = (void*)0;

const uint32_t CLK_EN_ARR[] = {CLK_EN_TIM1, CLK_EN_TIM2 , CLK_EN_TIM3 , CLK_EN_TIM4 , CLK_EN_TIM5 
	, CLK_EN_TIM9 , CLK_EN_TIM10 , CLK_EN_TIM11};

const static uint32_t ArrBaseAddr[] = {TIM1_BASEADDR ,TIM2_BASEADDR ,TIM3_BASEADDR ,
						TIM4_BASEADDR ,TIM5_BASEADDR ,TIM9_BASEADDR ,TIM10_BASEADDR , TIM11_BASEADDR};

const uint32_t ArrCCR_OFFSET[] = {TIMx_CCR1_OFFSET , TIMx_CCR2_OFFSET , TIMx_CCR3_OFFSET , TIMx_CCR4_OFFSET};





/*Functions Implementation*/																
void 		MCAL_TIMER_Init(strCONFIG_t* config)
{
	uint32_t TIMx_BaseAddr = ArrBaseAddr[config->TIMER_NUM];

	/*Enable Power Clock*/
	MCAL_RCC_ClockEnable(CLK_EN_ARR[config->TIMER_NUM]);
	
	/*Enable Power to GPIO*/
	MCAL_RCC_ClockEnable(GPIOA);
	MCAL_RCC_ClockEnable(GPIOB);	
	
	/*Choose Direction*/
	ASSIGN_BIT( (*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CR1_OFFSET)) , 4 ,config->TIMER_DIR);
	
	/*Set Prescalar Value*/
#if USER_PLL == PLL_Enable
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_PSC_OFFSET)) = ((F_CPU/1000)/4)-1; 	/*F_ClK_CNT = 2000Hz*/
#elif USER_PLL == PLL_Disable
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_PSC_OFFSET)) = ((F_CPU/1000))-1;    /*counter freq = 1000hz*/
#endif
	
	/*Enable Interrupt if user chose TIMER_INTERRUPT*/
	if(config->TIMER_MODE == TIMER_INTERRUPT)
	{
		CORTEXM4_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);	/*NVIC Gate*/
		SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_DIER_OFFSET)), 0); /*Local Gate*/
	}
	
	/*Enable Timer*/
	SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CR1_OFFSET)), 0);
	
}


void  	MCAL_TIMER_PollingDelay(strCONFIG_t* config, uint32_t delay)
{
	uint32_t TIMx_BaseAddr = ArrBaseAddr[config->TIMER_NUM];

	/*Clear Update Flag*/
	CLR_BIT( (*(vol_u32ptr)(TIMx_BaseAddr + TIMx_SR_OFFSET)) , 0);
	
	/*Set AutoReload Value*/
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_ARR_OFFSET)) = delay;
	
	/*Polling on Update Flag*/
	while( GET_BIT( *(vol_u32ptr)(TIMx_BaseAddr + TIMx_SR_OFFSET) , 0) != 1 );

}

void 		MCAL_TIMER_InterruptDelay(strCONFIG_t* config, void (*CallBackFunc)(void) ,uint32_t delay)
{	
	uint32_t TIMx_BaseAddr = ArrBaseAddr[config->TIMER_NUM];

	timer1_ptr_to_fn = CallBackFunc;
	
	/*Set AutoReload Value*/
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_ARR_OFFSET)) = delay;
	
}

uint16_t MCAL_TIMER_GetCurrentTime(strCONFIG_t* config)
{
	uint32_t TIMx_BaseAddr = ArrBaseAddr[config->TIMER_NUM];
	
	return (*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CNT_OFFSET));
}





void 		MCAL_TIMER_PWMInit(strCONFIG_t* config)
{
	if(config->TIMER_MODE != TIMER_PWM)
		return;

uint32_t TIMx_BaseAddr = ArrBaseAddr[config->TIMER_NUM];
	
	/*Enable Power Clock*/
	MCAL_RCC_ClockEnable(CLK_EN_ARR[config->TIMER_NUM]);
	
	/*Enable Power to GPIO*/
	MCAL_RCC_ClockEnable(GPIOA);
	MCAL_RCC_ClockEnable(GPIOB);	
	
	/*Configure Alternative PINS According to Channel and Timer*/ 
	switch(config->TIMER_NUM)
	{
		case _TIM1:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN8 , AF1_TIM1_2);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN9 , AF1_TIM1_2);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN10, AF1_TIM1_2);
					break;
				case CCR4:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN11, AF1_TIM1_2);
					break;
				default:break;
			}
			break;
			
			case _TIM2:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN15, AF1_TIM1_2);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN3 , AF1_TIM1_2);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN10, AF1_TIM1_2);
					break;
				default:break;
			}
			break;
			
			case _TIM3:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN6, AF2_TIM3_5);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN7, AF2_TIM3_5);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN0, AF2_TIM3_5);
					break;
				case CCR4:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN1, AF2_TIM3_5);
				default:break;
			}
			break;
			
			case _TIM4:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN6, AF2_TIM3_5);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN7, AF2_TIM3_5);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN8, AF2_TIM3_5);
					break;
				case CCR4:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN9, AF2_TIM3_5);
					break;
				default:break;
			}
			break;
			
			case _TIM5:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN0, AF2_TIM3_5);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN1, AF2_TIM3_5);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN2, AF2_TIM3_5);
					break;
				case CCR4:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN3, AF2_TIM3_5);
					break;
				default:break;
			}
			break;
		
				default:break;
	}
	
	/*Enable CCRx + Choose PWM Mode 1*/
	switch(config->TIMER_PWM_CH)
	{
		case CCR1:
			(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCMR1_OFFSET)) |= 6 << 4;
			SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCER_OFFSET)) , 0);
		break;
		
		case CCR2:
			(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCMR1_OFFSET)) |= 6 << 12;
			SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCER_OFFSET)) , 4);
		break;
		
		case CCR3:
			(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCMR2_OFFSET)) |= 6 << 4;
			SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCER_OFFSET)) , 8);
		break;
		
		case CCR4:
			(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCMR2_OFFSET)) |= 6 << 12;
			SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCER_OFFSET)) , 12);
		break;
		
		default:break;
	}
	
	/*Set Prescalar*/
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_PSC_OFFSET)) = 49;

	/*MOE*/
	SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_BDTR_OFFSET)) , 15);
	
	/*Enable Timer*/
	SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CR1_OFFSET)), 0);
}


void 		MCAL_TIMER_SetPWM(strCONFIG_t* config ,uint16_t freq ,float32_t duty_cycle)
{
	uint32_t CCRx_OFFSET	 = ArrCCR_OFFSET[config->TIMER_PWM_CH];
	uint32_t TIMx_BaseAddr = ArrBaseAddr[config->TIMER_NUM];

	/*Set ARR Value*/
	uint32_t ARR_Value = ( (uint32_t)((F_CPU/50) / freq) - 1);
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_ARR_OFFSET)) = ARR_Value ;
	
	float32_t dy = 100 - duty_cycle;
	
	/*Set Duty Cycle*/
	(*(vol_u32ptr)(TIMx_BaseAddr + CCRx_OFFSET)) = ((ARR_Value + 1) * ((float32_t)dy/100)) - 1;
	
}


uint16_t 		MCAL_TIMER_ICU(strCONFIG_t* config)
{
	
	return 0;
}


void 		MCAL_TIMER_OnePulseInit(strCONFIG_t* config)
{
	uint32_t TIMx_BaseAddr = ArrBaseAddr[config->TIMER_NUM];
	
	/*Enable Power Clock to TIMER*/
	MCAL_RCC_ClockEnable(CLK_EN_ARR[config->TIMER_NUM]);
	
	/*Enable Power to GPIO*/
	MCAL_RCC_ClockEnable(GPIOA);
	MCAL_RCC_ClockEnable(GPIOB);	
	
	/*Configure Alternative PINS According to Channel and Timer*/ 
	switch(config->TIMER_NUM)
	{
		case _TIM1:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN8 , AF1_TIM1_2);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN9 , AF1_TIM1_2);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN10, AF1_TIM1_2);
					break;
				case CCR4:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN11, AF1_TIM1_2);
					break;
				default:break;
			}
			break;
			
			case _TIM2:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN15, AF1_TIM1_2);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN3 , AF1_TIM1_2);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN10, AF1_TIM1_2);
					break;
				default:break;
			}
			break;
			
			case _TIM3:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN6, AF2_TIM3_5);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN7, AF2_TIM3_5);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN0, AF2_TIM3_5);
					break;
				case CCR4:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN1, AF2_TIM3_5);
				default:break;
			}
			break;
			
			case _TIM4:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN6, AF2_TIM3_5);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN7, AF2_TIM3_5);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN8, AF2_TIM3_5);
					break;
				case CCR4:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB, _IO_PIN9, AF2_TIM3_5);
					break;
				default:break;
			}
			break;
			
			case _TIM5:
			switch(config->TIMER_PWM_CH)
			{
				case CCR1:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN0, AF2_TIM3_5);
					break;
				case CCR2:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN1, AF2_TIM3_5);
					break;
				case CCR3:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN2, AF2_TIM3_5);
					break;
				case CCR4:
					MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA, _IO_PIN3, AF2_TIM3_5);
					break;
				default:break;
			}
			break;
		
				default:break;
	}
	
	
	
	
	
	
	
	
	

	/*T1 as input*/
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCMR1_OFFSET)) |= 1 << 0 | 7 << 4;
	
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_SMCR_OFFSET))  |= 8 << 4 | 8 << 0;
	
	/*Set OPM bit*/
	SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CR1_OFFSET)) , 3); 
	
	
	
}


void 		MCAL_TIMER_OnePulse(strCONFIG_t* config , uint16_t delay ,uint16_t length)
{
	uint32_t TIMx_BaseAddr = ArrBaseAddr[config->TIMER_NUM];
	
	/*Clear Update Flag*/
	CLR_BIT( (*(vol_u32ptr)(TIMx_BaseAddr + TIMx_SR_OFFSET)) , 0);
	
	/*Set delay of signal*/
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CCR1_OFFSET)) = delay;
	
	/*Set length of signal*/
	(*(vol_u32ptr)(TIMx_BaseAddr + TIMx_ARR_OFFSET)) = length + delay;
	
	/*Enable Timer and start counter*/
	SET_BIT((*(vol_u32ptr)(TIMx_BaseAddr + TIMx_CR1_OFFSET)), 0);
	
	/*Polling on Update Flag*/
	while( GET_BIT( *(vol_u32ptr)(TIMx_BaseAddr + TIMx_SR_OFFSET) , 0) != 1 );
}



/*TIMERS HANDLERS*/
void TIM1_UP_TIM10_IRQHandler(void)
{
	/*Clear Update Flag*/
	CLR_BIT( (*(vol_u32ptr)(TIM1_BASEADDR + TIMx_SR_OFFSET)) , 0);
	
	if(timer1_ptr_to_fn != (void*)0)
	{
		timer1_ptr_to_fn();
	}
}




