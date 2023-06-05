
#ifndef WWDG_DRIV_H_
#define WWDG_DRIV_H_

#include "STD_TYPES.h"


/*REGISTERS used in Reset Clock Control RCC*/
#define WWDG_BASE_ADDR					0x40002C00 

/*WWDG CR REGISTER*/
typedef struct
{
	uint32_t T		:7;
	uint32_t WDGA	:1;
	uint32_t 			:24;
	
}WWDG_CR_StrType;

typedef union
{
	uint32_t REG;
	WWDG_CR_StrType REG_BITS;
	
}WWDG_CR_TAG;

#define WWDG_CR 	(( volatile WWDG_CR_TAG * ) (WWDG_BASE_ADDR + 0x00))


/*WWDG CFR REGISTER*/
typedef struct
{
	uint32_t W			:7;
	uint32_t WDGTB	:2;
	uint32_t EWI		:23;
		
}WWDG_CFR_StrType;

typedef union
{
	uint32_t REG;
	WWDG_CFR_StrType REG_BITS;
	
}WWDG_CFR_TAG;

#define WWDG_CFR 	(( volatile WWDG_CFR_TAG * ) (WWDG_BASE_ADDR + 0x04))


/*WWDG SR REGISTER*/
typedef struct
{
	uint32_t EWIF			:1;
	uint32_t 					:31;

		
}WWDG_SR_StrType;

typedef union
{
	uint32_t REG;
	WWDG_SR_StrType REG_BITS;
	
}WWDG_SR_TAG;

#define WWDG_SR 	(( volatile WWDG_SR_TAG * ) (WWDG_BASE_ADDR + 0x08))


typedef struct
{
	uint8_t InterruptConfig;
	void (*NotificationEN)(void);
	uint8_t Wdg_InitialTimeOut;
	uint8_t Wdg_MaxTimeOut;
	
}Wdg_ConfigType;

/*Functions Prototypes*/
void MCAL_WWDG_Init(Wdg_ConfigType user_config);

void MCAL_WWDG_Start(void);

void MCAL_WWDG_Stop(void);

void MCAL_WWDG_Refresh(uint8_t timeout);





#endif
