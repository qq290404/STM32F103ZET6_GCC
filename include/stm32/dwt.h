#ifndef __PLATFORM_DWT_H__
#define __PLATFORM_DWT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void DWT_Init(void);
uint32_t DWT_Get_CNT(void);
void DWT_Delay_us(uint32_t);
void DWT_Delay_ms(uint32_t);

#ifdef __cplusplus
}
#endif

#endif

