#ifndef __PLATFORM_IWDG_H__
#define __PLATFORM_IWDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void IWDG_Init(uint32_t);
bool IWDG_Reset_Status(void);
void IWDG_Clear_Reset_Status(void);
void IWDG_Reload_Counter(void);

#ifdef __cplusplus
}
#endif

#endif

