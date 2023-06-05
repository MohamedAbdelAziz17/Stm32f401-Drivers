


#ifndef UART_H
#define	UART_H


#include "STD_TYPES.h"



#define RCC_APB2ENR_REG 	( * ( volatile uint32_t * ) ( 0x40023800 + 0x44 ) )		
	
#define USART1_SR_REG 		( * ( volatile uint32_t * ) ( 0x40011000 + 0x00 ) )	
#define USART1_DR_REG 		( * ( volatile uint32_t * ) ( 0x40011000 + 0x04 ) )	
#define USART1_BRR_REG 		( * ( volatile uint32_t * ) ( 0x40011000 + 0x08 ) )	
#define USART1_CR1_REG 		( * ( volatile uint32_t * ) ( 0x40011000 + 0x0C ) )	
#define USART1_CR2_REG 		( * ( volatile uint32_t * ) ( 0x40011000 + 0x10 ) )	
#define USART1_CR3_REG 		( * ( volatile uint32_t * ) ( 0x40011000 + 0x14 ) )	
#define USART1_GTPR_REG 	( * ( volatile uint32_t * ) ( 0x40011000 + 0x18 ) )	
	

#define BAUDRATE	9600

#define NEWLINE		0x0D
#define SPACE			0x20

void MCAL_UART1_Init(void);

void MCAL_UART1_Send_Char(uint8_t u8Data);

void MCAL_UART1_Send_String(char* string);

void MCAL_UART1_Send_Number(sint32_t s32Number);

uint8_t MCAL_UART1_Recieve_Char(void);

void MCAL_UART1_EnableIRQ(void);

#endif

