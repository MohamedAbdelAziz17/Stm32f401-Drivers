#ifndef SPI_DRIV_H_
#define SPI_DRIV_H_

#include "STD_TYPES.h"
#include "DIO_PROGRAM.h"



/*SPI BASE ADDRESSES*/
#define SPI1_BASEADDR		0x40013000
#define SPI2_BASEADDR		0x40003800
#define SPI3_BASEADDR		0x40003C00 



/*SPI REGISTERS OFFSET*/
#define SPI_CR1			0x00
#define SPI_CR2			0x04
#define SPI_SR			0x08
#define SPI_DR			0x0C
#define SPI_CRCPR		0x10
#define SPI_RXCRPR	0x14
#define SPI_TXCRPR	0x18
#define SPI_I2SCFGR	0x1C
#define SPI_I2SPR		0x20

/*SPI Control Register 1*/
typedef struct
{
	uint16_t CPHA	: 1;
	uint16_t CPOL	: 1;
	uint16_t MSTR	: 1;
	uint16_t BR	 	: 3;
	uint16_t SPE 	: 1;
	uint16_t LSBFIRST: 1;
	uint16_t SSI	: 1;
	uint16_t SSM	: 1;
	uint16_t RXONLY: 1;
	uint16_t DFF	: 1;
	uint16_t CRCNEXT: 1;
	uint16_t CRCEN: 1;
	uint16_t BIDIOE: 1;
	uint16_t BIDIMODE: 1;
}strSPI_CR1;

typedef union
{
	uint16_t REG;
	strSPI_CR1 BITS;
}unionSPI_CR1;

/*SPI Control Register 2*/
typedef struct
{
	uint16_t RXDMAEN	: 1;
	uint16_t TXDMAEN	: 1;
	uint16_t SSOE			: 1;
	uint16_t 					: 1;
	uint16_t FRF			: 1;
	uint16_t ERRIE		: 1;
	uint16_t RXNEIE		: 1;
	uint16_t TXEIE		: 1;
	uint16_t 					: 8;
}strSPI_CR2;

typedef union
{
	uint16_t REG;
	strSPI_CR2 BITS;
}unionSPI_CR2;

/*SPI Status Register*/
typedef struct
{
	uint16_t RXNE			: 1;
	uint16_t TXE			: 1;
	uint16_t CHSIDE		: 1;
	uint16_t UDR			: 1;
	uint16_t CRCERR		: 1;
	uint16_t MODF			: 1;
	uint16_t OVR			: 1;
	uint16_t BSY			: 1;
	uint16_t FRE			: 1;
	uint16_t 					: 7;
	
}strSPI_SR;

typedef union
{
	uint16_t REG;
	strSPI_SR BITS;
}unionSPI_SR;

#define SPI_CR1_REG(n)  ((volatile unionSPI_CR1*)(ArrBaseAddr[n] + SPI_CR1))
#define SPI_CR2_REG(n)  ((volatile unionSPI_CR2*)(ArrBaseAddr[n] + SPI_CR2))
#define SPI_SR_REG(n)	  ((volatile unionSPI_SR* )(ArrBaseAddr[n] + SPI_SR ))
#define SPI_DR_REG(n) 	(*(volatile uint16_t*	  )(ArrBaseAddr[n] + SPI_DR	))

/*Alternate Function*/
#define SPI_1_EN	28	
#define SPI_2_EN	12	
#define SPI_3_EN	13	

/*Configurations*/
#define SPI_Master	1
#define SPI_Slave		0

#define _SPI1	0
#define _SPI2	1
#define _SPI3	2


#define SPI_16Data	1
#define SPI_8Data		0

#define SPI_FullDuplex	0
#define SPI_HalfDuplex	1

typedef struct
{
	uint8_t SPI_Num;
	uint8_t SPI_Mode;
	GPIO_PORT_t SPI_NSS_GPIO;
	GPIO_Pin_t SPI_NSS_PIN;
	uint8_t SPI_Data;
	uint8_t SPI_Transmission_Mode;
	
}strSPIConfig_t;


/*Function Implementation*/
void MCAL_SPI_Init(strSPIConfig_t* config);

void MCAL_SPI_Send(strSPIConfig_t* config, uint16_t data);

uint16_t MCAL_SPI_Read(strSPIConfig_t* config);

void MCAL_SPI_EnableSS(strSPIConfig_t* config);

void MCAL_SPI_DisableSS(strSPIConfig_t* config);




#endif

