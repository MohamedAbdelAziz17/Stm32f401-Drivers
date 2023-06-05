
#ifndef I2C_DRIV_H_
#define I2C_DRIV_H_

#include "STD_TYPES.h"
#include "DIO_PROGRAM.h"

/*SPI BASE ADDRESSES*/
#define I2C1_BASEADDR		0x40005400
#define I2C2_BASEADDR		0x40005800
#define I2C3_BASEADDR		0x40005C00 


/*SPI REGISTERS OFFSET*/
#define I2C_CR1			0x00
#define I2C_CR2			0x04
#define I2C_OAR1		0x08
#define I2C_OAR2		0x0C
#define I2C_DR			0x10
#define I2C_SR1			0x14
#define	I2C_SR2			0x18
#define I2C_CCR			0x1C
#define I2C_TRISE		0x20
#define I2C_FLTR		0x24


/*I2C Control Register 1*/
typedef struct
{
	uint16_t PE						: 1;
	uint16_t SMBUS				: 1;
	uint16_t 							: 1;
	uint16_t SMBTYPE	 		: 1;
	uint16_t ENARP 				: 1;
	uint16_t ENPEC				: 1;
	uint16_t ENGC					: 1;
	uint16_t NOSTRETCH		: 1;
	uint16_t START				: 1;
	uint16_t STOP					: 1;
	uint16_t ACK					: 1;
	uint16_t POS					: 1;
	uint16_t PEC					: 1;
	uint16_t ALERT				: 1;
	uint16_t 							: 1;
	uint16_t SWRST				: 1;
	
}strI2C_CR1;

typedef union
{
	uint16_t REG;
	strI2C_CR1 BITS;
}unionI2C_CR1;



/*I2C Control Register 2*/
typedef struct
{
	uint16_t FREQ			: 6;
	uint16_t 					: 2;
	uint16_t ITERREN	: 1;
	uint16_t ITEVTEN 	: 1;
	uint16_t ITBUFEN	: 1;
	uint16_t DMAEN		: 1;
	uint16_t LAST			: 1;
	uint16_t 					: 3;
	
	
}strI2C_CR2;

typedef union
{
	uint16_t REG;
	strI2C_CR2 BITS;
}unionI2C_CR2;


/*I2C OWN ADDRESS REGISTER 1*/
typedef struct
{
	uint16_t ADD0			: 1;
	uint16_t ADD1_7		: 7;
	uint16_t ADD9_8		: 2;
	uint16_t 				 	: 5;
	uint16_t ADDMODE	: 1;

}strI2C_OAR1;

typedef union
{
	uint16_t REG;
	strI2C_OAR1 BITS;
}unionI2C_OAR1;



/*I2C STATUS REGISTER 1*/
typedef struct
{
	uint16_t SB			: 1;
	uint16_t ADDR		: 1;
	uint16_t BTF		: 1;
	uint16_t ADDR10	: 1;
	uint16_t STOPF	: 1;
	uint16_t 				: 1;
	uint16_t RXNE		: 1;
	uint16_t TXE		: 1;
	uint16_t BERR		: 1;
	uint16_t ARLO		: 1;
	uint16_t AF			: 1;
	uint16_t OVR		: 1;
	uint16_t PECERR	: 1;
	uint16_t 				: 1;
	uint16_t TIMEOUT	: 1;
	uint16_t SMBALERT	: 1;
	
}strI2C_SR1;

typedef union
{
	uint16_t REG;
	strI2C_SR1 BITS;
}unionI2C_SR1;


/*I2C STATUS REGISTER 2*/
typedef struct
{
	uint16_t MSL				: 1;
	uint16_t BUSY				: 1;
	uint16_t TRA				: 1;
	uint16_t 						: 1;
	uint16_t GENCALL		: 1;
	uint16_t SMBDEFAULT	: 1;
	uint16_t SMBHOST		: 1;
	uint16_t DUALF			: 1;
	uint16_t PEC				: 8;

	
}strI2C_SR2;

typedef union
{
	uint16_t REG;
	strI2C_SR2 BITS;
}unionI2C_SR2;


/*I2C CLOCL CONTROL REGISTER*/
typedef struct
{
	uint16_t CCR				: 12;
	uint16_t 						: 2;
	uint16_t DUTY				: 1;
	uint16_t FS					: 1;
	
}strI2C_CCR;

typedef union
{
	uint16_t REG;
	strI2C_CCR BITS;
}unionI2C_CCR;


#define I2C1_RCC_EN_BIT	16
#define I2C2_RCC_EN_BIT	17
#define I2C3_RCC_EN_BIT	18


#define I2C1_SCL_PORT			_IO_GPIOB
#define I2C1_SCL_PIN  		_IO_PIN8	
#define I2C1_SDA_PORT			_IO_GPIOB
#define I2C1_SDA_PIN 			_IO_PIN9	

#define I2C2_SCL_PORT 		_IO_GPIOA  
#define I2C2_SCL_PIN 			_IO_PIN10	
#define I2C2_SDA_PORT			_IO_GPIOB
#define I2C2_SDA_PIN 			_IO_PIN3	

#define I2C3_SCL_PORT 		_IO_GPIOA  
#define I2C3_SCL_PIN 			_IO_PIN8
#define I2C3_SDA_PORT			_IO_GPIOB
#define I2C3_SDA_PIN 			_IO_PIN4	


/*REGISTERS*/
#define I2C_CR1_REG(n)  	((volatile unionI2C_CR1*)	(ArrBaseAddr[n] + I2C_CR1))
#define I2C_CR2_REG(n)  	((volatile unionI2C_CR2*)	(ArrBaseAddr[n] + I2C_CR2))
#define I2C_OAR1_REG(n)  	((volatile unionI2C_OAR1*)(ArrBaseAddr[n] + I2C_OAR1))
#define I2C_OAR2_REG(n)  	((volatile unionI2C_OAR2*)(ArrBaseAddr[n] + I2C_OAR2))
#define I2C_DR_REG(n)  		(*(volatile uint16_t*)		(ArrBaseAddr[n] + I2C_DR))
#define I2C_SR1_REG(n) 		((volatile unionI2C_SR1*)	(ArrBaseAddr[n] + I2C_SR1))
#define I2C_SR2_REG(n) 		((volatile unionI2C_SR2*)	(ArrBaseAddr[n] + I2C_SR2))
#define I2C_CCR_REG(n)  	((volatile unionI2C_CCR*)	(ArrBaseAddr[n] + I2C_CCR))
#define I2C_TRISE_REG(n)  (*(volatile uint16_t*)		(ArrBaseAddr[n] + I2C_TRISE))
#define I2C_FLTR_REG(n)  	(*(volatile uint16_t*)		(ArrBaseAddr[n] + I2C_FLTR))


/*CONFIGURATIONS*/
#define I2C_1	0
#define I2C_2	1
#define I2C_3	2

#define I2C_Master 1
#define I2C_Slave 0

#define I2C_Write	0
#define I2C_Read	1



typedef struct
{
	uint8_t I2C_Num;
	uint8_t I2C_Mode;
	
	
}strI2C_Config_t;



/*Functions Prototypes*/
void MCAL_I2C_Init(strI2C_Config_t* config);

/*Master Mode API's*/
void MCAL_I2C_MasterStartCondition(strI2C_Config_t* config);

void MCAL_I2C_MasterSendAddrAck	(strI2C_Config_t* config , uint16_t address , uint8_t ReadOrWrite);
void MCAL_I2C_MasterSendAddrNack(strI2C_Config_t* config , uint16_t address , uint8_t ReadOrWrite);

void MCAL_I2C_MasterSendDataAck (strI2C_Config_t* config , uint8_t data);
void MCAL_I2C_MasterSendDataNack(strI2C_Config_t* config , uint8_t data);

void MCAL_I2C_MasterStopCondition(strI2C_Config_t* config);

void MCAL_I2C_MasterRepStartCondition(strI2C_Config_t* config);

uint8_t MCAL_I2C_MasterRead(strI2C_Config_t* config);

/*Slave Mode API's*/
void MCAL_I2C_SlaveSetAddr(strI2C_Config_t* config, uint16_t address);

uint8_t MCAL_I2C_SlaveRead(strI2C_Config_t* config);



#endif
