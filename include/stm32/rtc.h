#ifndef __PLATFORM_RTC_H__
#define __PLATFORM_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void RTC_Init(void);
uint32_t RTC_Get_Count(void);
void RTC_Set_Count(uint32_t);
bool RTC_Register_CallBack(void (*callback)(void));
void RTC_UnRegister_CallBack(void);
void RTC_Interrupt_Enable(void);

#ifdef __cplusplus
}
#endif

#endif

