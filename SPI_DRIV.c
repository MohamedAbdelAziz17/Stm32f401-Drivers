#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_PROGRAM.h"
#include "RCC_DRIV.h"
#include "SPI_DRIV.h"
#include "UART.h"

const static uint32_t ArrBaseAddr[] = {SPI1_BASEADDR, SPI2_BASEADDR, SPI3_BASEADDR};

const static uint32_t ArrSPI_EN[]		= {SPI_1_EN , SPI_2_EN , SPI_3_EN};

static void SPI_SetPinsAF(uint8_t SPI_Num , strSPIConfig_t* config)
{
	switch(SPI_Num)
	{
		/*SPI1*/
		case 0:
			if(config->SPI_Mode == SPI_Master)
			{
				MCAL_GPIO_PIN_OUTPUT(config->SPI_NSS_GPIO , config->SPI_NSS_PIN, _IO_PUSH_PULL,_IO_NO_PULL_UP_DOWN , _IO_VHIGH_SPEED);
			}
			else
			{
				MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA , _IO_PIN4 , AF5_SPI1_4);
			}
			MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA , _IO_PIN5 , AF5_SPI1_4);
			MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA , _IO_PIN6 , AF5_SPI1_4);
			MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA , _IO_PIN7 , AF5_SPI1_4);
		break;
		
		/*SPI2*/
		case 1:
			if(config->SPI_Mode == SPI_Master)
			{
				MCAL_GPIO_PIN_OUTPUT(config->SPI_NSS_GPIO , config->SPI_NSS_PIN, _IO_PUSH_PULL,_IO_NO_PULL_UP_DOWN , _IO_VHIGH_SPEED);
			}
			else
			{
				MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA , _IO_PIN4 , AF5_SPI1_4);
			}
			MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB , _IO_PIN13 , AF5_SPI1_4);
			MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB , _IO_PIN14 , AF5_SPI1_4);
			MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB , _IO_PIN15 , AF5_SPI1_4);
		break;
		
		/*SPI3*/
		case 2:
			if(config->SPI_Mode == SPI_Master)
			{
				MCAL_GPIO_PIN_OUTPUT(config->SPI_NSS_GPIO , config->SPI_NSS_PIN, _IO_PUSH_PULL ,_IO_NO_PULL_UP_DOWN , _IO_VHIGH_SPEED);
			}
			else
			{
				MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA , _IO_PIN4 , AF5_SPI1_4);
			}
			MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB , _IO_PIN4 , AF6_SPI3);
			MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB , _IO_PIN5 , AF6_SPI3);
			MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOA , _IO_PIN15, AF6_SPI3);
		break;
		default: break;
	}
}





void MCAL_SPI_Init(strSPIConfig_t* config)
{
	/*Enable Clock Power*/
	MCAL_RCC_ClockEnable(ArrSPI_EN[config->SPI_Num]);
	
	/*Enable Clock to GPIO*/
	if(config->SPI_Num == _SPI1)
	MCAL_RCC_ClockEnable(GPIOA);
	else
	MCAL_RCC_ClockEnable(GPIOB);
	
	/*Alternative Pins of SPI*/
	SPI_SetPinsAF(config->SPI_Num , config);
	
	/*Choose Mode Master or Slave*/
	SPI_CR1_REG(config->SPI_Num)->BITS.MSTR = config->SPI_Mode;

	/*Choose Data Format 8 or 16 bits*/
	SPI_CR1_REG(config->SPI_Num)->BITS.DFF = config->SPI_Data;
	
	/*Choose Transmission Mode*/
	if(config->SPI_Transmission_Mode == SPI_FullDuplex)
	{
		SPI_CR1_REG(config->SPI_Num)->BITS.RXONLY 	= 0;
		SPI_CR1_REG(config->SPI_Num)->BITS.BIDIMODE = 0;
	}
	
	/*Enable SPI*/
	SPI_CR1_REG(config->SPI_Num)->BITS.SPE = 1;
	
}


void MCAL_SPI_Send(strSPIConfig_t* config, uint16_t data)
{
	if(config->SPI_Transmission_Mode == SPI_HalfDuplex)
	{
		SPI_CR1_REG(config->SPI_Num)->BITS.BIDIMODE = 1;
		SPI_CR1_REG(config->SPI_Num)->BITS.BIDIOE	  = 1;
	}
	
	/*Wait for Transmit buffer to be empty*/
	while( (SPI_SR_REG(config->SPI_Num)->BITS.TXE) != 1);

	/*Load data to TX buffer + Clear TXE flag*/
	SPI_DR_REG(config->SPI_Num) = data;
	
	/*Wait for Transmit buffer to be empty*/
	while( (SPI_SR_REG(config->SPI_Num)->BITS.RXNE) != 1);
}


uint16_t MCAL_SPI_Read(strSPIConfig_t* config)
{
	uint16_t data = 0;
	
	if(config->SPI_Transmission_Mode == SPI_HalfDuplex)
	{
		SPI_CR1_REG(config->SPI_Num)->BITS.BIDIMODE = 1;
		SPI_CR1_REG(config->SPI_Num)->BITS.BIDIOE	  = 0;
	}
	
	/*Wait for RX buffer to load data*/
	while( (SPI_SR_REG(config->SPI_Num)->BITS.RXNE) != 1 );
	
	/*Read data + Clear RXNE flag*/
	data = SPI_DR_REG(config->SPI_Num);
	
	return data;
}


void MCAL_SPI_EnableSS(strSPIConfig_t* config)
{
	MCAL_GPIO_WRITE_PIN(config->SPI_NSS_GPIO , config->SPI_NSS_PIN , _IO_PIN_LOW);
}

void MCAL_SPI_DisableSS(strSPIConfig_t* config)
{
	MCAL_GPIO_WRITE_PIN(config->SPI_NSS_GPIO , config->SPI_NSS_PIN , _IO_PIN_HIGH);
}

