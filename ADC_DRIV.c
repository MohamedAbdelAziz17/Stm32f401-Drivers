#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_DRIV.h"
#include "DIO_PROGRAM.h"
#include "NVIC_DRIV.h"
#include "ADC_DRIV.h"


static void (*global_ptr)(uint32_t) = (void*)0;


void MCAL_ADC_Init(strADCUser_Config* config)
{
	MCAL_RCC_ClockEnable(ADC1);
	MCAL_RCC_ClockEnable(GPIOA);
	MCAL_RCC_ClockEnable(GPIOB);
	
	/*Select Analog Mode for ADC Channels*/
	for(int i = 0 ; i < config->ArraySize ; i++)
	{
		if(i > 7)
		{
			MCAL_GPIO_PIN_AnalogMode(_IO_GPIOB , (GPIO_Pin_t)config->ArrayChannel[i - 8]);
			continue;
		}
		
		MCAL_GPIO_PIN_AnalogMode(_IO_GPIOA , (GPIO_Pin_t)config->ArrayChannel[i]);
	}
	
	/*Enable ADC*/
	ADC_CR2_REG->BITS.ADON = 1;
	
	/*Choose Mode*/
	ADC_CR2_REG->BITS.CONT = config->Mode;

	/*Choose Resolution*/
	ADC_CR1_REG->BITS.RES = config->Resolution;
	
	/*Choose Interrupt or Polling*/
	ADC_CR1_REG->BITS.EOCIE = config->ADC_ConversionMode;
	
	if(config->ADC_ConversionMode == ADC_INTERRUPT)
		CORTEXM4_NVIC_EnableIRQ(ADC_IRQn);
	
	/*End of Conversion Selection*/
	ADC_CR2_REG->BITS.EOCS = 0;
	
	/*Select Scan Mode*/
	ADC_CR1_REG->BITS.SCAN = 1;
	
	/*Data Right Alignment*/
	ADC_CR2_REG->BITS.ALIGN = 0;
	
	/*ADC Prescalar divided by 8*/
	ADC_CCR_REG |= 3UL << 16;
	
	/*Channels Total Number in Regular*/
	ADC_SQR1_REG |= (uint32_t)((config->ArraySize) - 1) << 20;
	
	/*Choose Channels and their sequence in Regular*/
	for(uint32_t i = 0 ; i < config->ArraySize ; i++)
	{
		if(i < 5)
			ADC_SQR3_REG |= (uint32_t)config->ArrayChannel[i] << (i*5);
		else if (i < 11)
			ADC_SQR2_REG |= (uint32_t)config->ArrayChannel[i] << (i*5);
		else if (i < 15)
			ADC_SQR1_REG |= (uint32_t)config->ArrayChannel[i] << (i*5);
	}

}

void MCAL_ADC_StartConversion(void)
{
	/*Start Conversion*/
	ADC_CR2_REG->BITS.SWSTART = 1;
}

uint32_t MCAL_ADC_PollingRead(void)
{
	uint32_t data = 0;
	
	/*Clear SWSTART Flag*/
	ADC_SR_REG->BITS.STRT = 0;
	
	/*Poll on End of Conversion Flag*/
	while(ADC_SR_REG->BITS.EOC != 1);
	
	/*Read Data+ Clear EOC Flag*/
	data = ADC_DR_REG;

	return data;
}

void	MCAL_ADC_InterruptRead( void (*ptr)(uint32_t) )
{
	/*Poll on Start Flag*/
	while(ADC_SR_REG->BITS.STRT != 1);
	
	/*Clear Start Flag*/
	ADC_SR_REG->BITS.STRT = 0;
	
	global_ptr = ptr;
}





void ADC_IRQHandler(void)
{
	uint32_t data = 0;
	
	if( global_ptr != (void*)0 )
	{
		data = ADC_DR_REG;
		
		global_ptr(data);
	}
}
