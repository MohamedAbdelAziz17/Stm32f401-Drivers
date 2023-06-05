#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_PROGRAM.h"
#include "RCC_DRIV.h"



void MCAL_GPIO_PIN_OUTPUT(GPIO_PORT_t PORT  ,GPIO_Pin_t u8Pin , uint8_t u8Output_Type ,uint8_t u8_Input_Type,uint8_t	u8Output_Speed)
{
	/*Enable Clock of PORT*/
	MCAL_RCC_ClockEnable(PORT);
	
		switch(PORT)
		{
			case _IO_GPIOA:
				/*MODER REGISTER*/
				SET_BIT(GPIOA_MODER_REG , (u8Pin*2));	
				CLR_BIT(GPIOA_MODER_REG , ((u8Pin*2)+1));
				
				/*OTYPER REGISTER*/
				if(u8Output_Type == _IO_PUSH_PULL)
				{
					CLR_BIT(GPIOA_OTYPER_REG , u8Pin);
				}
				else
				{
					SET_BIT(GPIOA_OTYPER_REG , u8Pin);
				}
				
				switch(u8Output_Speed)
				{
					/*OSPEED REGISTER*/
					case _IO_LOW_SPEED:
						CLR_BIT(GPIOA_OSPEED_REG , (u8Pin*2));
						CLR_BIT(GPIOA_OSPEED_REG , ((u8Pin*2)+1));
					break;
			
					case _IO_MED_SPEED:
						SET_BIT(GPIOA_OSPEED_REG , (u8Pin*2));
						CLR_BIT(GPIOA_OSPEED_REG , ((u8Pin*2)+1));
					break;
			
					case _IO_HIGH_SPEED:
						CLR_BIT(GPIOA_OSPEED_REG , (u8Pin*2));
						SET_BIT(GPIOA_OSPEED_REG , ((u8Pin*2)+1));
					break;
			
					case _IO_VHIGH_SPEED:
						SET_BIT(GPIOA_OSPEED_REG , (u8Pin*2));
						SET_BIT(GPIOA_OSPEED_REG , ((u8Pin*2)+1));
			
					default: break;
				}
				/*PUDR Register*/
				switch(u8_Input_Type)
				{
			case _IO_NO_PULL_UP_DOWN:
				CLR_BIT(GPIOA_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOA_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_UP:
				SET_BIT(GPIOA_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOA_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_DOWN:
				CLR_BIT(GPIOA_PUPDR_REG , (u8Pin*2));
			  SET_BIT(GPIOA_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			default: break;
				}	
				
				break;
			
				case _IO_GPIOB:
					/*MODER REGISTER*/
				SET_BIT(GPIOB_MODER_REG , (u8Pin*2));	
				CLR_BIT(GPIOB_MODER_REG , ((u8Pin*2)+1));
				
				/*OTYPER REGISTER*/
				if(u8Output_Type == _IO_PUSH_PULL)
				{
					CLR_BIT(GPIOB_OTYPER_REG , u8Pin);
				}
				else
				{
					SET_BIT(GPIOB_OTYPER_REG , u8Pin);
				}
				
				switch(u8Output_Speed)
				{
					/*OSPEED REGISTER*/
					case _IO_LOW_SPEED:
						CLR_BIT(GPIOB_OSPEED_REG , (u8Pin*2));
						CLR_BIT(GPIOB_OSPEED_REG , ((u8Pin*2)+1));
					break;
			
					case _IO_MED_SPEED:
						SET_BIT(GPIOB_OSPEED_REG , (u8Pin*2));
						CLR_BIT(GPIOB_OSPEED_REG , ((u8Pin*2)+1));
					break;
			
					case _IO_HIGH_SPEED:
						CLR_BIT(GPIOB_OSPEED_REG , (u8Pin*2));
						SET_BIT(GPIOB_OSPEED_REG , ((u8Pin*2)+1));
					break;
			
					case _IO_VHIGH_SPEED:
						SET_BIT(GPIOB_OSPEED_REG , (u8Pin*2));
						SET_BIT(GPIOB_OSPEED_REG , ((u8Pin*2)+1));
			
					default: break;
				}
				/*PUDR Register*/
				switch(u8_Input_Type)
				{
			case _IO_NO_PULL_UP_DOWN:
				CLR_BIT(GPIOB_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOB_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_UP:
				SET_BIT(GPIOB_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOB_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_DOWN:
				CLR_BIT(GPIOB_PUPDR_REG , (u8Pin*2));
			  SET_BIT(GPIOB_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			default: break;
				}	
				break;
					
					case _IO_GPIOC:
						/*MODER REGISTER*/
				SET_BIT(GPIOC_MODER_REG , (u8Pin*2));	
				CLR_BIT(GPIOC_MODER_REG , ((u8Pin*2)+1));
				
				/*OTYPER REGISTER*/
				if(u8Output_Type == _IO_PUSH_PULL)
				{	/*Push Pull*/
					CLR_BIT(GPIOC_OTYPER_REG , u8Pin);
				}
				else 
				{	/*Open Drain*/
					SET_BIT(GPIOC_OTYPER_REG , u8Pin);
				}
				
				switch(u8Output_Speed)
				{
					/*OSPEED REGISTER*/
					case _IO_LOW_SPEED:
						CLR_BIT(GPIOC_OSPEED_REG , (u8Pin*2));
						CLR_BIT(GPIOC_OSPEED_REG , ((u8Pin*2)+1));
					break;
			
					case _IO_MED_SPEED:
						SET_BIT(GPIOC_OSPEED_REG , (u8Pin*2));
						CLR_BIT(GPIOC_OSPEED_REG , ((u8Pin*2)+1));
					break;
			
					case _IO_HIGH_SPEED:
						CLR_BIT(GPIOC_OSPEED_REG , (u8Pin*2));
						SET_BIT(GPIOC_OSPEED_REG , ((u8Pin*2)+1));
					break;
			
					case _IO_VHIGH_SPEED:
						SET_BIT(GPIOC_OSPEED_REG , (u8Pin*2));
						SET_BIT(GPIOC_OSPEED_REG , ((u8Pin*2)+1));
			
					default: break;
				}
				/*PUDR Register*/
				switch(u8_Input_Type)
				{
			case _IO_NO_PULL_UP_DOWN:
				CLR_BIT(GPIOC_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOC_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_UP:
				SET_BIT(GPIOC_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOC_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_DOWN:
				CLR_BIT(GPIOC_PUPDR_REG , (u8Pin*2));
			  SET_BIT(GPIOC_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			default: break;
				}	
				break;
					
			default: break;
		}
		
}

void MCAL_GPIO_PIN_INPUT(GPIO_PORT_t PORT  ,GPIO_Pin_t u8Pin , uint8_t u8_Input_Type)
{
	/*Enable Clock of PORT*/
	MCAL_RCC_ClockEnable(PORT);
	
	switch(PORT)
	{
		case _IO_GPIOA:
			CLR_BIT(GPIOA_MODER_REG , (u8Pin*2));	
			CLR_BIT(GPIOA_MODER_REG , ((u8Pin*2)+1));	
			
			switch(u8_Input_Type)
			{
			case _IO_NO_PULL_UP_DOWN:
				CLR_BIT(GPIOA_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOA_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_UP:
				SET_BIT(GPIOA_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOA_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_DOWN:
				CLR_BIT(GPIOA_PUPDR_REG , (u8Pin*2));
			  SET_BIT(GPIOA_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			default: break;
		}
		break;
		
		case _IO_GPIOB:
			CLR_BIT(GPIOB_MODER_REG , (u8Pin*2));	
			CLR_BIT(GPIOB_MODER_REG , ((u8Pin*2)+1));	
			switch(u8_Input_Type)
			{
			case _IO_NO_PULL_UP_DOWN:
				CLR_BIT(GPIOB_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOB_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_UP:
				SET_BIT(GPIOB_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOB_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_DOWN:
				CLR_BIT(GPIOB_PUPDR_REG , (u8Pin*2));
			  SET_BIT(GPIOB_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			default: break;
		}
		break;
		
		case _IO_GPIOC:
			CLR_BIT(GPIOC_MODER_REG , (u8Pin*2));	
			CLR_BIT(GPIOC_MODER_REG , ((u8Pin*2)+1));	
			switch(u8_Input_Type)
			{
			case _IO_NO_PULL_UP_DOWN:
				CLR_BIT(GPIOC_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOC_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_UP:
				SET_BIT(GPIOC_PUPDR_REG , (u8Pin*2));
			  CLR_BIT(GPIOC_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			case _IO_PULL_DOWN:
				CLR_BIT(GPIOC_PUPDR_REG , (u8Pin*2));
			  SET_BIT(GPIOC_PUPDR_REG , ((u8Pin*2)+1));
			break;
			
			default: break;
		}
		break;
		
		default: break;
		
	}
}

void MCAL_GPIO_WRITE_PIN(GPIO_PORT_t Port , GPIO_Pin_t u8Pin , uint8_t u8Pin_State)
{
	switch(Port)
	{
		case _IO_GPIOA:
			if(u8Pin_State)
			SET_BIT(GPIOA_BSRR_REG , u8Pin);		/*Read Modify Write*/	/*Write using BitBandAlias Register*/
			else
			SET_BIT(GPIOA_BSRR_REG , (u8Pin + 16));
		break;

		case _IO_GPIOB:
			if(u8Pin_State)
			SET_BIT(GPIOB_BSRR_REG , u8Pin);
			else
			SET_BIT(GPIOB_BSRR_REG , (u8Pin + 16));
		break;
			
		case _IO_GPIOC:
			if(u8Pin_State)
			SET_BIT(GPIOC_BSRR_REG , u8Pin);
			else
			SET_BIT(GPIOC_BSRR_REG , (u8Pin + 16));
		break;
		
		default: break;
	}
}




uint8_t MCAL_GPIO_READ_PIN(GPIO_PORT_t Port , GPIO_Pin_t u8Pin)
{
	switch(Port)
	{
		case _IO_GPIOA:
			return GET_BIT(GPIOA_IDR_REG , u8Pin);

		case _IO_GPIOB:
			return GET_BIT(GPIOB_IDR_REG , u8Pin);
			
		case _IO_GPIOC:
			return GET_BIT(GPIOC_IDR_REG , u8Pin);
		
		default: break;
	}
	
	return 0;
}


void MCAL_GPIO_PIN_ALTERNATIVE (GPIO_PORT_t Port , GPIO_Pin_t u8Pin ,GPIO_ALT_FUNC_t u8Alt_Func)
{
	switch(Port)
	{
		case _IO_GPIOA:
			GPIOA_MODER_REG |= 2 << (u8Pin * 2);
			if(u8Pin < 8)
			{
				GPIOA_AFRL_REG |= u8Alt_Func << (u8Pin*4);
			}
			else
			{
				GPIOA_AFRH_REG |= u8Alt_Func << ((u8Pin%8)*4);
			}
			break;
	
		case _IO_GPIOB:
			GPIOB_MODER_REG |= 2 << (u8Pin * 2);
			if(u8Pin < 8)
			{
				GPIOB_AFRL_REG |= u8Alt_Func << (u8Pin*4);
			}
			else
			{
				GPIOB_AFRH_REG |= u8Alt_Func << ((u8Pin%8)*4);
			}
			break;
			
		case _IO_GPIOC:
			GPIOC_MODER_REG |= 2 << (u8Pin * 2);
			if(u8Pin < 8)
			{
				GPIOC_AFRL_REG |= u8Alt_Func << (u8Pin*4);
			}
			else
			{
				GPIOC_AFRH_REG |= u8Alt_Func << ((u8Pin%8)*4);
			}
			break;
		
		default: break;
	}
}


void MCAL_GPIO_PIN_AnalogMode(GPIO_PORT_t Port , GPIO_Pin_t u8Pin)
{
		switch(Port)
	{
		case _IO_GPIOA:
			GPIOA_MODER_REG |= 3 << (u8Pin * 2);
			break;
	
		case _IO_GPIOB:
			GPIOB_MODER_REG |= 3 << (u8Pin * 2);
			break;
			
		case _IO_GPIOC:
			GPIOC_MODER_REG |= 3 << (u8Pin * 2);
			break;
		
		default: break;
	}
}
