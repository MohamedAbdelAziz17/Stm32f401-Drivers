#ifndef KEYPAD_PROGRAM_C_
#define KEYPAD_PROGRAM_C_

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_PROGRAM.h"
#include "Keypad_Cfg.h"
#include "Keypad_DRIV.h"

uint8_t Key_Matrix[KEYPAD_ROW_END - KEYPAD_ROW_START + 1 ][KEYPAD_COL_END - KEYPAD_COL_START + 1 ] = {{'*',0,'#'},{7,8,9},{4,5,6},{1,2,3}};


void HAL_Keypad_Init(void)
{
  uint8_t Local_RowLoop , Local_ColLoop ;

  for(Local_RowLoop = KEYPAD_ROW_START  ; Local_RowLoop <= KEYPAD_ROW_END ; Local_RowLoop ++)
  {
	  MCAL_GPIO_PIN_INPUT(KEYPAD_ROW_PORT , Local_RowLoop , _IO_PULL_UP);
  }

  for(Local_ColLoop = KEYPAD_COL_START  ; Local_ColLoop <= KEYPAD_COL_END ; Local_ColLoop ++)
   {
		 MCAL_GPIO_PIN_OUTPUT(KEYPAD_COL_PORT , Local_ColLoop , _IO_PUSH_PULL , _IO_NO_PULL_UP_DOWN, _IO_VHIGH_SPEED);
		 MCAL_GPIO_WRITE_PIN(KEYPAD_COL_PORT , Local_ColLoop , _IO_PIN_HIGH);
   }

}

void HAL_Keypad_GetPressedKey(uint8_t *ptr_PressedValue)
{
	 uint8_t Local_RowLoop , Local_ColLoop  , Local_Value = 1;
	 uint8_t pin_state = 0;

	 for(Local_RowLoop = KEYPAD_ROW_START  ; Local_RowLoop <= KEYPAD_ROW_END ; Local_RowLoop ++)
	 {
		 for(Local_ColLoop = KEYPAD_COL_START  ; Local_ColLoop <= KEYPAD_COL_END ; Local_ColLoop ++)
		 {
			 MCAL_GPIO_WRITE_PIN(KEYPAD_COL_PORT , Local_ColLoop , _IO_PIN_LOW);
			 pin_state = MCAL_GPIO_READ_PIN(KEYPAD_ROW_PORT , Local_RowLoop);

			 if(pin_state == 0)
			 {
				 *ptr_PressedValue = Key_Matrix [Local_RowLoop - KEYPAD_ROW_START][Local_ColLoop - KEYPAD_COL_START];
					
				 while(Local_Value == 0)
				 {
					 pin_state = MCAL_GPIO_READ_PIN(KEYPAD_ROW_PORT , Local_RowLoop);
				 }
			 }
			 
			 MCAL_GPIO_WRITE_PIN(KEYPAD_COL_PORT , Local_ColLoop , _IO_PIN_HIGH);
		 }

	 }

}

#endif /* KEYPAD_PROGRAM_C_ */