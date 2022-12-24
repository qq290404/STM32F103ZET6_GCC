#include <ucos_ii.h>
#include "stm32/systick.h"

static HSYSTICK hsystick = HSYSTICK_NULL;

static void OS_CPU_SysTickHandler(void)
{
	OSIntEnter(); 
    OSTimeTick(); 
    OSIntExit();
}

static void InitSystick(void)
{
	hsystick = GetSysTickInstance();
	SysTick_Register_CallBack(hsystick, OS_CPU_SysTickHandler);
}

void OS_Bsp_Init(void)
{
	InitSystick();
}
