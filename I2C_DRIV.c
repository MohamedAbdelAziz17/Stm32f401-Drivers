#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_DRIV.h"
#include "DIO_PROGRAM.h"
#include "I2C_DRIV.h"
#include "UART.h"


volatile const static uint16_t ArrBaseAddr[] = {I2C1_BASEADDR, I2C2_BASEADDR, I2C3_BASEADDR};

volatile const static uint32_t ArrI2C_EN[]		= {I2C1_RCC_EN_BIT , I2C2_RCC_EN_BIT , I2C3_RCC_EN_BIT};

volatile const static uint32_t ArrI2C_PORT_PIN[]		= {I2C1_SCL_PORT , I2C1_SCL_PIN , I2C1_SDA_PORT , I2C1_SDA_PIN ,
																						 I2C2_SCL_PORT , I2C1_SCL_PIN , I2C1_SDA_PORT , I2C1_SDA_PIN ,
																					   I2C2_SCL_PORT , I2C1_SCL_PIN , I2C1_SDA_PORT , I2C1_SDA_PIN  };


/*Functions Implementations*/
void MCAL_I2C_Init(strI2C_Config_t* config)
{
	/*Enable Clock to I2C*/
	MCAL_RCC_ClockEnable(ArrI2C_EN[config->I2C_Num]);
	
	/*Enable Clock to GPIO*/
	MCAL_RCC_ClockEnable(GPIOA);
	MCAL_RCC_ClockEnable(GPIOB);
	
	/*Configure I2C Pins as AF*/
	MCAL_GPIO_PIN_ALTERNATIVE((GPIO_PORT_t) ArrI2C_PORT_PIN[((config->I2C_Num)*4) + 0] , (GPIO_Pin_t) ArrI2C_PORT_PIN[((config->I2C_Num)*4) + 1] , (GPIO_ALT_FUNC_t)(config->I2C_Num == I2C_2) ? AF9_I2C2_2:AF4_I2C1_3);
	MCAL_GPIO_PIN_ALTERNATIVE((GPIO_PORT_t) ArrI2C_PORT_PIN[((config->I2C_Num)*4) + 2] , (GPIO_Pin_t) ArrI2C_PORT_PIN[((config->I2C_Num)*4) + 3] , (GPIO_ALT_FUNC_t)(config->I2C_Num == I2C_2) ? AF9_I2C2_2:AF4_I2C1_3);
	
	switch(config->I2C_Num)
	{
		case I2C_1:
			SET_BIT(GPIOB_OTYPER_REG , 8); 	/*SCL open drain*/
			SET_BIT(GPIOB_OTYPER_REG , 9); 	/*SDA open drain*/

			SET_BIT(GPIOB_PUPDR_REG  , 16); /*SCL PULL UP*/
			SET_BIT(GPIOB_PUPDR_REG  , 18); /*SDA PULL UP*/
	
			SET_BIT(GPIOB_OSPEED_REG , 16); /*SCL Very High Speed*/
			SET_BIT(GPIOB_OSPEED_REG , 17);
			SET_BIT(GPIOB_OSPEED_REG , 18);	/*SDA Very High Speed*/
			SET_BIT(GPIOB_OSPEED_REG , 19);
		break;
		
		case I2C_2:
			SET_BIT(GPIOA_OTYPER_REG , 10); 	/*SCL open drain*/
			SET_BIT(GPIOB_OTYPER_REG , 3); 		/*SDA open drain*/

			SET_BIT(GPIOA_PUPDR_REG  , 20); 	/*SCL PULL UP*/
			SET_BIT(GPIOB_PUPDR_REG  , 6); 		/*SDA PULL UP*/
	
			SET_BIT(GPIOA_OSPEED_REG , 20); 	/*SCL Very High Speed*/
			SET_BIT(GPIOA_OSPEED_REG , 21);
			SET_BIT(GPIOB_OSPEED_REG , 6);		/*SDA Very High Speed*/
			SET_BIT(GPIOB_OSPEED_REG , 7);
		break;
		
		case I2C_3:
			SET_BIT(GPIOA_OTYPER_REG , 8); 	/*SCL open drain*/
			SET_BIT(GPIOB_OTYPER_REG , 4); 	/*SDA open drain*/

			SET_BIT(GPIOA_PUPDR_REG  , 16); /*SCL PULL UP*/
			SET_BIT(GPIOB_PUPDR_REG  , 8); 	/*SDA PULL UP*/
	
			SET_BIT(GPIOA_OSPEED_REG , 16); /*SCL Very High Speed*/
			SET_BIT(GPIOA_OSPEED_REG , 17);
			SET_BIT(GPIOB_OSPEED_REG , 8);	/*SDA Very High Speed*/
			SET_BIT(GPIOB_OSPEED_REG , 9);
		break;
		
		default : break;
	}
	
	
	/*Choose I2C SM Mode*/
	I2C_CCR_REG(config->I2C_Num)->BITS.FS = 0;
	
	/*Enable Acknowledge*/
	I2C_CR1_REG(config->I2C_Num)->BITS.ACK = 1;
	
	I2C_CR1_REG(config->I2C_Num)->BITS.SMBUS = 0;
	
	/*Configure Frequency*/
	I2C_CR2_REG(config->I2C_Num)->BITS.FREQ = 25; /*Must be APB1 Clock 25Mhz*/
	
	/*Configure Clock to 100KHz*/
	I2C_CCR_REG(config->I2C_Num)->BITS.CCR = 125;
	
	/*Configure Rise Time*/
	I2C_TRISE_REG(config->I2C_Num) = 25;
	
	/*Enable I2C*/
	I2C_CR1_REG(config->I2C_Num)->BITS.PE = 1;

}

/*Master Mode API's*/
void MCAL_I2C_MasterStartCondition(strI2C_Config_t* config)
{
	I2C_CR1_REG(config->I2C_Num)->BITS.START = 1;
	
	MCAL_UART1_Send_Char(NEWLINE);
	MCAL_UART1_Send_Number(I2C_SR1_REG(config->I2C_Num)->REG);
	MCAL_UART1_Send_Char(NEWLINE);
	MCAL_UART1_Send_Number(I2C_SR2_REG(config->I2C_Num)->REG);
	
	/*Wait to be sent*/
	while( I2C_SR1_REG(config->I2C_Num)->BITS.SB != 1 );
	
	/*Read SR1 to Clear flags */
	(void)(I2C_SR1_REG(config->I2C_Num)->REG);
}

void MCAL_I2C_MasterSendAddrAck	(strI2C_Config_t* config , uint16_t address , uint8_t ReadOrWrite)
{
	I2C_DR_REG(config->I2C_Num) = address | ReadOrWrite;
	
	/*Wait to be sent*/
	while( I2C_SR1_REG(config->I2C_Num)->BITS.ADDR != 1 );
	
	/*Ack Recieved*/
	while( I2C_SR1_REG(config->I2C_Num)->BITS.TXE != 1 );
	
	/*Clear Flag*/
	(void)(I2C_SR1_REG(config->I2C_Num)->REG);
	(void)(I2C_SR2_REG(config->I2C_Num)->REG);
}


void MCAL_I2C_MasterSendAddrNack(strI2C_Config_t* config , uint16_t address , uint8_t ReadOrWrite)
{
	I2C_DR_REG(config->I2C_Num) = address | ReadOrWrite;
	
	/*Wait to be sent*/
	while( I2C_SR1_REG(config->I2C_Num)->BITS.ADDR != 1 );
	
	/*Nack Recieved*/
	//while( I2C_SR1_REG(config->I2C_Num)->BITS.TXE != 1 );
	
	/*Clear Flag*/
	(void)(I2C_SR1_REG(config->I2C_Num)->REG);
	(void)(I2C_SR2_REG(config->I2C_Num)->REG);
	
}


void MCAL_I2C_MasterSendDataAck (strI2C_Config_t* config , uint8_t data)
{
	/*Wait on Data register to be empty*/
	while( I2C_SR1_REG(config->I2C_Num)->BITS.TXE != 1 );
	
	/*Load data + Clear Flag*/
	I2C_DR_REG(config->I2C_Num) = data;
	
	/*Wait on Data register to be empty to indicate data sent succesfully + Ack Recieved*/
	while( I2C_SR1_REG(config->I2C_Num)->BITS.TXE != 1 );
	
	/*Cleared by writing to data register or by hardware at stop condition*/
	
}

void MCAL_I2C_MasterSendDataNack(strI2C_Config_t* config , uint8_t data)
{
	/*Wait on Data register to be empty*/
	while( I2C_SR1_REG(config->I2C_Num)->BITS.TXE != 1 );
	
	/*Load data + Clear Flag*/
	I2C_DR_REG(config->I2C_Num) = data;
	
	/*Nack Recieved*/
	//while( I2C_SR1_REG(config->I2C_Num)->BITS.TXE != 1 );
	
	/*Cleared by writing to data register or by hardware at stop condition*/
}


void MCAL_I2C_MasterStopCondition(strI2C_Config_t* config)
{
	I2C_CR1_REG(config->I2C_Num)->BITS.STOP = 1;
	
	/*System Goes back to Slave*/ /*Wait to be slave*/
	while( I2C_SR2_REG(config->I2C_Num)->BITS.MSL != 0 );
}


void MCAL_I2C_MasterRepStartCondition(strI2C_Config_t* config)
{
	MCAL_I2C_MasterStopCondition(config);
}


uint8_t MCAL_I2C_MasterRead(strI2C_Config_t* config)
{
	uint8_t data = 0;
	
	while( I2C_SR1_REG(config->I2C_Num)->BITS.RXNE != 1 );
	
	data = I2C_DR_REG(config->I2C_Num);
	
	return data;
}




/*Slave Mode API's*/
void MCAL_I2C_SlaveSetAddr(strI2C_Config_t* config, uint16_t address)
{
	/*Choose 7-bits Address*/
	I2C_OAR1_REG(config->I2C_Num)->BITS.ADD0 = 0 ;
	
	I2C_OAR1_REG(config->I2C_Num)->BITS.ADD1_7 = (uint8_t)address;
}


uint8_t MCAL_I2C_SlaveRead(strI2C_Config_t* config)
{
	uint8_t data = 0;
	
	/*Wait on Address to be matched*/
	while(I2C_SR1_REG(config->I2C_Num)->BITS.ADDR != 1);
	
	/*Clear Flag*/
	(void)(I2C_SR1_REG(config->I2C_Num)->REG);
	(void)(I2C_SR2_REG(config->I2C_Num)->REG);
	
	while( I2C_SR1_REG(config->I2C_Num)->BITS.RXNE != 1 );
	
	/*Recieve data + Clear Flag*/
	data = I2C_DR_REG(config->I2C_Num);
	
	return data;
}

