/*Custom Header Files*/
#include "BIT_MATH.h"
#include <stdint.h>
#include "CPU_CONFIGURATIONS.h"

/*Compiler Header Files*/
#include "cmsis_armcc.h"

/*STM32 Drivers Header Files*/
#include "RCC_DRIV.h"
#include "DIO_PROGRAM.h"
#include "UART.h"
#include "NVIC_DRIV.h"
#include "EXTI_DRIV.h"
#include "System_Timer.h"
#include "WWDG_DRIV.h"
#include "IWDG_DRIV.h"
#include "TIMER_DRIV.h"
#include "ADC_DRIV.h"
#include "SPI_DRIV.h"
#include "I2C_DRIV.h"

/*STM32 External Modules*/
#include "Keypad_DRIV.h"

/*Global Variables*/
uint32_t PM_Reg_Value 			= 0;
uint32_t FM_Reg_Value				= 0;
uint32_t Control_Reg_value	= 0;


void Disable_All_Interrupts(void)
{
	/*SET PRIMASK*/
	__ASM("CPSID i");
	
	/*SET FAULTMASK*/
	__ASM("CPSID f");
	
}

void Enable_All_Interrupts(void)
{
	/*CLR PRIMASK*/
	__ASM("CPSIE i");
	
	/*CLR FAULTMASK*/
	__ASM("CPSIE f");
	
}

void BASEPRI_Set(uint8_t basepri_num)
{
	__ASM("mov R4, basepri_num");
	
	__ASM("MSR BASEPRI, R4");
	
}

void Switch_to_UNPRIVILEGE(void)
{
	/*SET first bit in CONTROL Reg*/
	__ASM("MOV R0, #1");
	__ASM("MSR CONTROL, R0");
	
}

void Switch_to_PRIVILEGE(void)
{
	/*Fire SVCALL*/
	__ASM("SVC #0");
	
}

void SVC_Handler()
{
	/*CLR first bit in CONTROL Reg*/
	__ASM("MOV R4, #0");
	__ASM("MSR CONTROL, R4");
	
	/*OPTIONAL: Read Core Registers*/

	//__ASM("MRS R5,CONTROL");
	//__ASM("MOV Control_Reg_value,R5");
	///*OPTIONAL: READ PRIMASK REG*/
	//__ASM("MRS R5,PRIMASK");
	//__ASM("MOV PM_Reg_value,R5");
	/*OPTIONAL: READ FAULTMASK REG*/
	//__ASM("MRS R5,FAULTMASK");
	//__ASM("MOV FM_Reg_value,R5");
}


/**************************************/










/****Interrupts/Exceptions HANDLERS*****/
void USART1_IRQHandler(void)
{
	MCAL_UART1_Send_String("USART1 Execution");
	MCAL_UART1_Send_Char(NEWLINE);
}

void EXTI0_IRQHandler(void)
{	
	MCAL_UART1_Send_String("EXTI0 Execution");
	MCAL_UART1_Send_Char(NEWLINE);
}

void EXTI2_IRQHandler(void)
{
	MCAL_UART1_Send_String("EXTI2 Execution");
	MCAL_UART1_Send_Char(NEWLINE);
}

void EXTI3_IRQHandler(void)
{
	MCAL_UART1_Send_String("EXTI3 Execution");
	MCAL_UART1_Send_Char(NEWLINE);
}

void EXTI4_IRQHandler(void)
{
	MCAL_UART1_Send_String("EXTI4 Execution");
	MCAL_UART1_Send_Char(NEWLINE);
}

void EXTI15_10_IRQHandler(void)
{
	MCAL_UART1_Send_String("EXTI15_10 Execution");
	MCAL_UART1_Send_Char(NEWLINE);
}
void HardFault_Handler(void)
{
	MCAL_UART1_Send_Char(NEWLINE);
	MCAL_UART1_Send_String("HardFault!");
}
/*****************************************/

void onepulse (strCONFIG_t* config,uint8_t delay,uint8_t length,GPIO_PORT_t port,GPIO_Pin_t pin,uint8_t state1,uint8_t state2 )
{
	MCAL_GPIO_WRITE_PIN(port , pin, state1); /*Low*/
	
	MCAL_TIMER_PollingDelay(config , delay);
	
	MCAL_GPIO_WRITE_PIN(port , pin, state2); /*High*/
	
	MCAL_TIMER_PollingDelay(config , length);
	
	MCAL_GPIO_WRITE_PIN(port , pin, state1); /*Low*/
}
/*****/


int main()
{
/************INITIALIZATIONS************/
	MCAL_RCC_Clock_Config();

	/*ENABLE GLOBAL GATES*/
	Enable_All_Interrupts(); 
	
	/*BASEPRI GATE*/
	BASEPRI_Set(0x00); /*no effect*/
	
	/*UART Configurations*/
	MCAL_UART1_Init();
	
	/*GPIO Configurations*/
	/*MCAL_GPIO_PIN_INPUT(_IO_GPIOA  , _IO_PIN1 , _IO_PULL_DOWN);
	MCAL_GPIO_PIN_OUTPUT(_IO_GPIOC , _IO_PIN13, _IO_OPEN_DRAIN , _IO_PULL_DOWN, _IO_HIGH_SPEED);
	MCAL_GPIO_WRITE_PIN(_IO_GPIOC , _IO_PIN13, _IO_PIN_HIGH);*/			/*Led onboard*/
	
	/*ADC Configurations*/
	/*uint8_t adc_channels[] = {ADC_CH2, ADC_CH3, ADC_CH4, ADC_CH5};
	strADCUser_Config adc = {adc_channels , sizeof(adc_channels) , ADC_RESOLUTION_12 , ADC_MODE_SINGLE , ADC_POLLING};
	MCAL_ADC_Init(&adc);*/

	/*TIMERS Configurations*/
	/*strCONFIG_t tim1_ccr1 = {_TIM1 , CCR1, UP_COUNT , TIMER_PWM};
	MCAL_TIMER_PWMInit(&tim1_ccr1);
	MCAL_TIMER_SetPWM(&tim1_ccr1 , 50 , 50);
	
	strCONFIG_t tim1_ccr2 = {_TIM1 , CCR2, UP_COUNT , TIMER_PWM};
	MCAL_TIMER_PWMInit(&tim1_ccr2);
	MCAL_TIMER_SetPWM(&tim1_ccr2 , 50 , 50);*/
	
	strCONFIG_t tim4_ccr3 = {_TIM4 , CCR3, UP_COUNT , TIMER_POLLING};
	MCAL_TIMER_Init(&tim4_ccr3);

	/*Enable External Interrupts*/
	/*MCAL_EXTI_Config(_IO_GPIOA , _IO_PIN13 , EXTI_RISING);
	MCAL_EXTI_Config(_IO_GPIOB , _IO_PIN14 , EXTI_RISING);
	MCAL_EXTI_Config(_IO_GPIOB , _IO_PIN4  , EXTI_RISING);*/
	
	
	HAL_Keypad_Init();
	uint8_t pr_key = 0;
	
	while(1)
	{
		HAL_Keypad_GetPressedKey(&pr_key);
		
		if(pr_key != 0)
		{
			MCAL_UART1_Send_Number(pr_key);
		}

		MCAL_TIMER_PollingDelay(&tim4_ccr3 , 30);
		
		pr_key = 0;

	}
}	






	










//void System_Clk_Config()
//{
//	/*1.Enable HSE Clock*/
//	SET_BIT (RCC_CR_REGG , 16);	/*HSEON*/
//	
//	/*2.Wait untill clock is ready*/
//	while( GET_BIT(RCC_CR_REGG , 17) != 1 );	/*HSERDY*/
//	
//	/*3.Define P,N,M parameters of PLL*/
//	RCC_PLLCFGR_REGG =  (PLL_M) | (PLL_N << 6) | ( ((PLL_P >> 1) - 1) << 16 );
//	
//	/*4.Choose source of PLL as HSE*/
//	SET_BIT(RCC_PLLCFGR_REGG , 22);
//	
//	/*5.Enable power clock*/
//	SET_BIT( RCC_APB1_REGG , 28 );
//	
//	/*6.Choose voltage regulator scale 3 , 01*/
//	CLR_BIT(PWR_CR_REGG , 15); SET_BIT(PWR_CR_REGG , 14); 
//	
//	/*7.Choose Prescaler of APB and AHB buses*/
//	RCC_CFGR_REGG = ((RCC_CFGR_REGG & 0xFFFFE3FF) | (4<<10));	/*Div APB1 by 4*/
//	/*APB2 and AHB no div*/
//		
//	/*8.Enable PLL*/
//	SET_BIT(RCC_CR_REGG, 24);
//	
//	/*9.Wait on PLL Ready*/
//	while( GET_BIT(RCC_CR_REGG , 25) != 1 );
//	
//	/*10.Choose PLL as System Clock , 10*/
//	SET_BIT(RCC_CFGR_REGG , 1); CLR_BIT(RCC_CFGR_REGG , 0);
//}




