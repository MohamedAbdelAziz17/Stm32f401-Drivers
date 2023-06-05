#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_DRIV.h"
#include "UART.h"
#include "DIO_PROGRAM.h"


void MCAL_RCC_SystemReset(void)
{														/*MASK*/			 		 /*VECTKEY*/	/*SYSRESETREQ*/
	SCB_AIRCR_REG = (SCB_AIRCR_REG & 0xFFFB) | ((0x5FA << 16) | (1 << 2));
}
/**/
void MCAL_RCC_PerphReset(enumPeripherals_t Peripheral)
{
	if(Peripheral <= 7)
	{
		switch(Peripheral)
		{
			case GPIOA:
				RCC_AHB1RSTR->REG_BITS.GPIOARST = 1;
			break;
			case GPIOB:
				RCC_AHB1RSTR->REG_BITS.GPIOBRST = 1;
			break;
			case GPIOC:
				RCC_AHB1RSTR->REG_BITS.GPIOCRST = 1;
			break;
			case GPIOD:
				RCC_AHB1RSTR->REG_BITS.GPIODRST = 1;
			break;
			case GPIOE:
				RCC_AHB1RSTR->REG_BITS.GPIOERST = 1;
			break;
			case GPIOH:
				RCC_AHB1RSTR->REG_BITS.GPIOHRST = 1;
			break;
			case DMA1:
				RCC_AHB1RSTR->REG_BITS.DMA1RST = 1;
			break;
			case DMA2:
				RCC_AHB1RSTR->REG_BITS.DMA2RST = 1;
			break;
			default:break;
		}			
	}
	else if(Peripheral <= 19)
	{
		switch(Peripheral)
		{
			case TIM2:
				RCC_APB1RSTR->REG_BITS.TIM2RST = 1;
			break;
			case TIM3:
				RCC_APB1RSTR->REG_BITS.TIM3RST = 1;
			break;
			case TIM4:
				RCC_APB1RSTR->REG_BITS.TIM4RST = 1;
			break;
			case TIM5:
				RCC_APB1RSTR->REG_BITS.TIM5RST = 1;
			break;
			case SPI2:
				RCC_APB1RSTR->REG_BITS.SPI2RST = 1;
			break;
			case SPI3:
				RCC_APB1RSTR->REG_BITS.SPI3RST = 1;
			break;
			case WWDG:
				RCC_APB1RSTR->REG_BITS.WWDGRST = 1;
			break;
			case USART2:
				RCC_APB1RSTR->REG_BITS.USART2RST = 1;
			break;
			case I2C1:
				RCC_APB1RSTR->REG_BITS.I2C1RST = 1;
			break;
			case I2C2:
				RCC_APB1RSTR->REG_BITS.I2C2RST = 1;
			break;
			case I2C3:
				RCC_APB1RSTR->REG_BITS.I2C3RST = 1;
			break;
			case PWR:
				RCC_APB1RSTR->REG_BITS.PWRRST = 1;
			break;
			default:break;
		}			
	}
	else if(Peripheral <= 29)
	{
		switch(Peripheral)
		{
			case ADC1:
				RCC_APB2RSTR->REG_BITS.ADC1RST = 1;
			break;
			case SDIO:
				RCC_APB2RSTR->REG_BITS.SDIORST = 1;
			break;
			case TIM1:
				RCC_APB2RSTR->REG_BITS.TIM1RST = 1;
			break;
			case TIM9:
				RCC_APB2RSTR->REG_BITS.TIM9RST = 1;
			break;
			case TIM10:
				RCC_APB2RSTR->REG_BITS.TIM10RST = 1;
			break;
			case TIM11:
				RCC_APB2RSTR->REG_BITS.TIM11RST = 1;
			break;
			case USART1:
				RCC_APB2RSTR->REG_BITS.USART1RST = 1;
			break;
			case USART6:
				RCC_APB2RSTR->REG_BITS.USART6RST = 1;
			break;
			case SPI1:
				RCC_APB2RSTR->REG_BITS.SPI1RST = 1;
			break;
			case SPI4:
				RCC_APB2RSTR->REG_BITS.SPI4RST = 1;
			break;
			
			default:break;
		}
	}
	else{/*ERROR*/}
	
}

/**/
uint8_t MCAL_RCC_GetResetFlag(void)
{
	/*Store temporary value before clearing the flags*/
	uint8_t* tmp = (uint8_t*) RCC_CSR;
	
	/*Clear Flags*/
	RCC_CSR->REG_BITS.RMVF = 1;
	
	return (*(tmp + 3));	/*return last 8 bits*/
}
/**/
void MCAL_RCC_ClockEnable(uint8_t Peripheral)
{
	if(Peripheral <= 7)
	{
		switch(Peripheral)
		{
			case GPIOA:
				RCC_AHB1ENR->REG_BITS.GPIOAEN = 1;
			break;
			case GPIOB:
				RCC_AHB1ENR->REG_BITS.GPIOBEN = 1;
			break;
			case GPIOC:
				RCC_AHB1ENR->REG_BITS.GPIOCEN = 1;
			break;
			case GPIOD:
				RCC_AHB1ENR->REG_BITS.GPIODEN = 1;
			break;
			case GPIOE:
				RCC_AHB1ENR->REG_BITS.GPIOEEN = 1;
			break;
			case GPIOH:
				RCC_AHB1ENR->REG_BITS.GPIOHEN = 1;
			break;
			case DMA1:
				RCC_AHB1ENR->REG_BITS.DMA1EN = 1;
			break;
			case DMA2:
				RCC_AHB1ENR->REG_BITS.DMA2EN = 1;
			break;
			default:break;
		}			
	}
	else if(Peripheral <= 19)
	{
		switch(Peripheral)
		{
			case TIM2:
				RCC_APB1ENR->REG_BITS.TIM2EN = 1;
			break;
			case TIM3:
				RCC_APB1ENR->REG_BITS.TIM3EN = 1;
			break;
			case TIM4:
				RCC_APB1ENR->REG_BITS.TIM4EN = 1;
			break;
			case TIM5:
				RCC_APB1ENR->REG_BITS.TIM5EN = 1;
			break;
			case SPI2:
				RCC_APB1ENR->REG_BITS.SPI2EN = 1;
			break;
			case SPI3:
				RCC_APB1ENR->REG_BITS.SPI3EN= 1;
			break;
			case WWDG:
				RCC_APB1ENR->REG_BITS.WWDGEN = 1;
			break;
			case USART2:
				RCC_APB1ENR->REG_BITS.USART2EN = 1;
			break;
			case I2C1:
				RCC_APB1ENR->REG_BITS.I2C1EN= 1;
			break;
			case I2C2:
				RCC_APB1ENR->REG_BITS.I2C2EN = 1;
			break;
			case I2C3:
				RCC_APB1ENR->REG_BITS.I2C3EN = 1;
			break;
			case PWR:
				RCC_APB1ENR->REG_BITS.PWREN = 1;
			break;
			default:break;
		}			
	}
	else if(Peripheral <= 30)
	{
		switch(Peripheral)
		{
			case SYSCFG:
				RCC_APB2ENR->REG_BITS.SYSCFGEN = 1;
			break;
			case ADC1:
				RCC_APB2ENR->REG_BITS.ADC1EN = 1;
			break;
			case SDIO:
				RCC_APB2ENR->REG_BITS.SDIOEN = 1;
			break;
			case TIM1:
				RCC_APB2ENR->REG_BITS.TIM1EN = 1;
			break;
			case TIM9:
				RCC_APB2ENR->REG_BITS.TIM9EN = 1;
			break;
			case TIM10:
				RCC_APB2ENR->REG_BITS.TIM10EN = 1;
			break;
			case TIM11:
				RCC_APB2ENR->REG_BITS.TIM11EN = 1;
			break;
			case USART1:
				RCC_APB2ENR->REG_BITS.USART1EN = 1;
			break;
			case USART6:
				RCC_APB2ENR->REG_BITS.USART6EN = 1;
			break;
			case SPI1:
				RCC_APB2ENR->REG_BITS.SPI1EN = 1;
			break;
			case SPI4:
				RCC_APB2ENR->REG_BITS.SPI4EN = 1;
			break;
			
			default:break;
		}
	}
	else{/*ERROR*/}
	
}


void MCAL_RCC_Clock_Config()
{
	MCAL_RCC_ClockEnable(PWR);
	
#if 	USER_CLOCK == Clock_HSE
		/*Enable HSE Clock and wait to be ready*/
		RCC_CR->REG_BITS.HSEON = 1;
		while( RCC_CR->REG_BITS.HSERDY != 1 );
	
		/*HSE bypass*/
		RCC_CR->REG_BITS.HSEBYP = 1;
	
	uint32_t PLLClockSource = 0; 
		#if USER_PLL == PLL_Disable
				/*Choose HSE as clock source and wait to be ready*/
				RCC_CFGR->REG_BITS.SW = 1;
				while ( RCC_CFGR->REG_BITS.SWS != 1 );
		#elif USER_PLL == PLL_Enable
				/*Choose Source of PLL*/
				PLLClockSource = 1;
		#endif
	
#elif USER_CLOCK == Clock_HSI
			/*Enable HSI Clock*/
			RCC_CR->REG_BITS.HSION = 1;
		
			/*Wait untill HSIclock is ready*/
			while( RCC_CR->REG_BITS.HSIRDY != 1 );
	
		#if USER_PLL == PLL_Disable
			/*Choose HSI as clock source and wait to be ready*/
			RCC_CFGR->REG_BITS.SW = 0;
			while ( RCC_CFGR->REG_BITS.SWS != 0 );
		#elif USER_PLL == PLL_Enable
			/*Choose Source of PLL*/
			PLLClockSource = 0;
		#endif
#endif
	
#if 	USER_PLL == PLL_Enable
		/*Calculate Parameters of PLL*/
		uint32_t  PLL_P = 2;
		uint32_t  PLL_M = 0;
		uint32_t  PLL_N = 0;
		uint32_t 	INPUT_CLK;
		
#if USER_CLOCK == Clock_HSE
		  PLL_M = ((uint32_t)F_HSE / 1000000UL);
			INPUT_CLK = F_HSE;
#elif USER_CLOCK == Clock_HSI
		  PLL_M = ((uint32_t)F_HSI / 1000000UL);
			INPUT_CLK = F_HSI;
#endif

		PLL_N = (PLL_P * ((uint32_t)F_CPU/1000000) * PLL_M) / ((uint32_t)INPUT_CLK/1000000);
		
		/*Check if PLL_N is out of range*/
		while((PLL_N > 432) || (PLL_N < 192))
		{
			PLL_P += 2;
			PLL_N = (PLL_P * ((uint32_t)F_CPU/1000000) * PLL_M) / ((uint32_t)INPUT_CLK/1000000);
			if(PLL_P > 8)
				return;
		}
		
		/*Configure P , M , N and Clock Source of PLL HSE/HSI*/
		RCC_PLLCFGR->REG = (PLL_M) | (PLL_N << 6UL) | ( ((PLL_P >> 1UL) - 1UL) << 16UL ) | (PLLClockSource << 22UL) ;
		
		/*Enable PLL and Wait to be ready*/
		RCC_CR->REG_BITS.PLLON = 1;
		while( RCC_CR->REG_BITS.PLLRDY != 1 );
		
		/*Choose PLL as clock source and wait to be ready*/
		RCC_CFGR->REG_BITS.SW = 2;
		while ( RCC_CFGR->REG_BITS.SWS != 2 );
	
#endif
	
}
