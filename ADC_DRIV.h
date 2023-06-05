#ifndef ADC_DRIV_H_
#define ADC_DRIV_H_

#include "STD_TYPES.h"


/*ADC status register*/
typedef struct
{
	uint32_t AWD	:1;
	uint32_t EOC	:1;
	uint32_t JEOC	:1;
	uint32_t JSTRT:1;
	uint32_t STRT	:1;
	uint32_t OVR	:1;
	uint32_t 			:26;
	
}strADC_SR;

typedef union
{
	uint32_t REG;
	strADC_SR BITS;
}enumADC_SR;


/*ADC control register 1*/
typedef struct
{
	uint32_t AWDCH	:5;
	uint32_t EOCIE	:1;
	uint32_t AWDIE	:1;
	uint32_t JEOCIE	:1;
	uint32_t SCAN		:1;
	uint32_t AWDSGL	:1;
	uint32_t JAUTO	:1;
	uint32_t DISCEN	:1;
	uint32_t JDISCEN	:1;
	uint32_t DISCNUM	:3;
	uint32_t 					:6;
	uint32_t JAWDEN		:1;
	uint32_t AWDEN		:1;
	uint32_t RES			:2;
	uint32_t OVRIE		:1;
	uint32_t 					:5;
	
}strADC_CR1;

typedef union
{
	uint32_t REG;
	strADC_CR1 BITS;
}enumADC_CR1;


/*ADC control register 2*/
typedef struct
{
	uint32_t ADON		:1;
	uint32_t CONT		:1;
	uint32_t 				:6;
	uint32_t DMA		:1;
	uint32_t DDS		:1;
	uint32_t EOCS		:1;
	uint32_t ALIGN	:1;
	uint32_t 				:4;
	uint32_t JEXTSEL:4;
	uint32_t JEXTEN	:2;
	uint32_t JSWSTART	:1;
	uint32_t 				:1;
	uint32_t EXTSEL	:4;
	uint32_t EXTEN	:2;
	uint32_t SWSTART:1;
	uint32_t 				:1;
	
}strADC_CR2;

typedef union
{
	uint32_t REG;
	strADC_CR2 BITS;
}enumADC_CR2;

#define ADC_BASEADRR	0x40012000

#define ADC_SR_REG  			((volatile enumADC_SR*)  	(ADC_BASEADRR + 0x00))
#define ADC_CR1_REG 			((volatile enumADC_CR1*) 	(ADC_BASEADRR + 0x04))
#define ADC_CR2_REG  			((volatile enumADC_CR2*) 	(ADC_BASEADRR + 0x08))

#define ADC_SMPR1_REG			(*(volatile uint32_t*)		(ADC_BASEADRR + 0x0C))
#define ADC_SMPR2_REG			(*(volatile uint32_t*)		(ADC_BASEADRR + 0x10))
#define ADC_JOFRx_REG			(*(volatile uint32_t*)		(ADC_BASEADRR + 0x14))
#define ADC_HTR_REG				(*(volatile uint32_t*)		(ADC_BASEADRR + 0x24))
#define ADC_LTR_REG				(*(volatile uint32_t*)		(ADC_BASEADRR + 0x28))
#define ADC_SQR1_REG			(*(volatile uint32_t*)		(ADC_BASEADRR + 0x2C))
#define ADC_SQR2_REG			(*(volatile uint32_t*)		(ADC_BASEADRR + 0x30))
#define ADC_SQR3_REG			(*(volatile uint32_t*)		(ADC_BASEADRR + 0x34))
#define ADC_JSQR_REG			(*(volatile uint32_t*)		(ADC_BASEADRR + 0x38))
#define ADC_JDRx_REG			(*(volatile uint32_t*)		(ADC_BASEADRR + 0x3C))
#define ADC_DR_REG				(*(volatile uint32_t*)		(ADC_BASEADRR + 0x4C))
#define ADC_CCR_REG				(*(volatile uint32_t*)		(ADC_BASEADRR + 0x300 + 0x04))

/*User Configurations*/
#define ADC_CH0	0
#define ADC_CH1	1
#define ADC_CH2	2
#define ADC_CH3	3
#define ADC_CH4	4
#define ADC_CH5	5
#define ADC_CH6	6
#define ADC_CH7	7
#define ADC_CH8	8
#define ADC_CH9	9

#define ADC_RESOLUTION_6	3
#define ADC_RESOLUTION_8	2
#define ADC_RESOLUTION_10	1
#define ADC_RESOLUTION_12	0

#define ADC_MODE_SINGLE				0
#define ADC_MODE_CONTINUOUS		1

#define ADC_POLLING			0
#define ADC_INTERRUPT		1


typedef struct
{
	uint8_t* 	ArrayChannel;
	uint8_t		ArraySize;
	uint8_t 	Resolution;
	uint8_t 	Mode;
	uint8_t 	ADC_ConversionMode;
}strADCUser_Config;

/*Functions Prototypes*/
void 		 MCAL_ADC_Init(strADCUser_Config* config);

void 		 MCAL_ADC_StartConversion(void);

uint32_t MCAL_ADC_PollingRead(void);

void		 MCAL_ADC_InterruptRead(void (*ptr)(uint32_t));













#endif
