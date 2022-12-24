#ifndef __PLATFORM_SYSTICK_H__
#define __PLATFORM_SYSTICK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdbool.h>

typedef unsigned int HSYSTICK;
#define HSYSTICK_NULL ((HSYSTICK)0)

HSYSTICK GetSysTickInstance(void);
bool SysTick_Register_CallBack(HSYSTICK, void (*callback)(void));
void SysTick_UnRegister_CallBack(HSYSTICK);
uint32_t Systick_Get_Count(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
