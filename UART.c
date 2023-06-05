#include <stdio.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_PROGRAM.h"
#include "UART.h"
#include "RCC_DRIV.h"

void MCAL_UART1_Init()
{
	/*USART1 Clock Enable*/
	MCAL_RCC_ClockEnable(USART1);
	
	/*GPIOB Clock Enable*/
	MCAL_RCC_ClockEnable(GPIOB);
	
	/*Configure PINS as alternative functions*/
	MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB , _IO_PIN6 , AF7_USART1_2);
	MCAL_GPIO_PIN_ALTERNATIVE(_IO_GPIOB , _IO_PIN7 , AF7_USART1_2);
	
	/*Define Word Length*/
	CLR_BIT (USART1_CR1_REG , 12);	/*8 bit data*/
	
	/*Define BAUDRATE for Fclk ,9600 baudrate and using equation from datasheet*/
#if USER_PLL == PLL_Enable
	float32_t BR_Mantissa = (F_CPU/4 / (float32_t)(16 * BAUDRATE)); /*from datasheet*/
#elif USER_PLL == PLL_Disable
	float32_t BR_Mantissa = (F_CPU / (float32_t)(16 * BAUDRATE)); /*from datasheet*/
#endif
	float32_t Mantissa_decimal_part =  BR_Mantissa - (uint32_t)BR_Mantissa;
	
	uint32_t  BR_Fractional = (16 * Mantissa_decimal_part); /*from datasheet*/
	
	USART1_BRR_REG = ( ((uint32_t)BR_Mantissa << 4) | BR_Fractional );				/*Mantissa Part , Fractional Part*/ 	/*16Mhz:104 , 3 | 84Mhz:546 , 14*/

	/*Enable Transmitter and Reciever Bits*/
	SET_BIT(USART1_CR1_REG , 2);	/*TE*/
	SET_BIT(USART1_CR1_REG , 3);	/*RE*/

	/*Enable UART1*/
	SET_BIT (USART1_CR1_REG , 13);
	
	/*Clear Data Register*/
	USART1_DR_REG = 0;
	while( GET_BIT(USART1_SR_REG , 6) != 1 );
}

void MCAL_UART1_EnableIRQ(void)
{
	SET_BIT(USART1_CR1_REG , 5);	/*enable local interrupt of recieve*/
}

void MCAL_UART1_Send_Char(uint8_t u8Data)
{
	/*Put data in data register*/
	USART1_DR_REG = (uint32_t) u8Data;
	
	/*Poll on TC Transmission Complete Flag*/
	while( GET_BIT(USART1_SR_REG , 6) != 1 );
}

void MCAL_UART1_Send_String(char* string)
{
	while( *string )
	{
		MCAL_UART1_Send_Char( *(string++) );
	}
}

void MCAL_UART1_Send_Number(sint32_t s32Number)
{
	/*Convert integer to string*/
	char buffer[10];		
	
	sprintf(buffer, "%d", (int)s32Number);	/*include stdio.h*/
	
	/*Send the string*/
	MCAL_UART1_Send_String(buffer);
	
}

uint8_t MCAL_UART1_Recieve_Char()
{
	/*Poll on Read Data register bit*/
	while( GET_BIT(USART1_SR_REG , 5) != 1 );
	
	/*reading data clears BIT RXNE*/
	uint8_t data = USART1_DR_REG;	
	
	return data;	

}
