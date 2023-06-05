#ifndef KEYPAD_DRIV_H_
#define KEYPAD_DRIV_H_


#include "Keypad_Cfg.h"

void HAL_Keypad_Init(void);

void HAL_Keypad_GetPressedKey(uint8_t *ptr_PressedValue);











#endif