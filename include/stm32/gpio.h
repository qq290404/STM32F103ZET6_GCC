#ifndef __PLATFORM_GPIO_H__
#define __PLATFORM_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef unsigned int HGPIO;
#define HGPIO_NULL	((HGPIO)0)

enum eHW_IO_Type_e
{
	eHW_GPIOA,
	eHW_GPIOB,
	eHW_GPIOC,
	eHW_GPIOD,
	eHW_GPIOE,
	eHW_GPIOF,
	eHW_GPIOG,
	eHW_GPIOH,
	
	eHW_GPIO_MAX
};

enum eHW_IO_Pin_e
{
	eHW_GPIO_Pin_0,
	eHW_GPIO_Pin_1,
	eHW_GPIO_Pin_2,
	eHW_GPIO_Pin_3,
	eHW_GPIO_Pin_4,
	eHW_GPIO_Pin_5,
	eHW_GPIO_Pin_6,
	eHW_GPIO_Pin_7,
	eHW_GPIO_Pin_8,
	eHW_GPIO_Pin_9,
	eHW_GPIO_Pin_10,
	eHW_GPIO_Pin_11,
	eHW_GPIO_Pin_12,
	eHW_GPIO_Pin_13,
	eHW_GPIO_Pin_14,
	eHW_GPIO_Pin_15,

	eHW_GPIO_Pin_MAX
};

enum eHW_IO_Status_e
{
	eHW_GPIO_STS_LOW,
	eHW_GPIO_STS_HIGHT,

	eHW_GPIO_STS_NULL
};

enum eHW_IO_Mode_e
{
	eHW_GPIO_MODE_INPUT_ANALOG, 
	eHW_GPIO_MODE_INPUT_FLOATING, 
	eHW_GPIO_MODE_INPUT_UP_PULL, 
	eHW_GPIO_MODE_INPUT_DOWN_PULL, 
	eHW_GPIO_MODE_OUTPUT_PUSH_PULL,
	eHW_GPIO_MODE_OUTPUT_OPEN_DRAIN, 
	eHW_GPIO_MODE_OUTPUT_MULTIPLEXED_PUSH_PULL,
	eHW_GPIO_MODE_OUTPUT_MULTIPLEXED_OPEN_DRAIN,
	eHW_GPIO_MODE_MAX
};

enum eHW_IO_Exti_Mode_e
{
	eHW_GPIO_EXTI_MODE_INTERRUPT = 0x00,
	eHW_GPIO_EXTI_MODE_EVENTT	 = 0x04,
};

enum eHW_IO_Trigger_Mode_e
{
	eHW_GPIO_TRIGGER_RISING			 = 0x08,
	eHW_GPIO_TRIGGER_FALLING		 = 0x0C,
	eHW_GPIO_TRIGGER_RISING_FALLING	 = 0x10,
};

HGPIO GPIO_Init(enum eHW_IO_Type_e, enum eHW_IO_Pin_e);
void GPIO_DeInit(HGPIO);
void GPIO_Set_Mode(HGPIO, enum eHW_IO_Mode_e);
void GPIO_Set_Status(HGPIO, enum eHW_IO_Status_e);
void GPIO_Toggle_Status(HGPIO);
const char* GPIO_Get_Name(HGPIO);
enum eHW_IO_Mode_e GPIO_Get_Mode(HGPIO);
enum eHW_IO_Status_e GPIO_Get_Status(HGPIO);
bool GPIO_Register_CallBack(HGPIO, enum eHW_IO_Exti_Mode_e, enum eHW_IO_Trigger_Mode_e, void (*callback)(void));
bool GPIO_UnRegister_CallBack(HGPIO);
void GPIO_Set_IRQ_Priority(HGPIO, uint8_t, uint8_t);

#ifdef __cplusplus
}
#endif

#endif
