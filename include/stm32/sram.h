#ifndef __PLATFORM_SRAM_H__
#define __PLATFORM_SRAM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void FSMC_SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(uint16_t *, uint32_t, uint32_t);
void FSMC_SRAM_ReadBuffer(uint16_t *, uint32_t, uint32_t);

#ifdef __cplusplus
}
#endif

#endif

