#ifndef __PLATFORM_FLASH_H__
#define __PLATFORM_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void FLASH_Write_Data(uint32_t, const uint8_t *, uint32_t);
void FLASH_Read_Data(uint32_t, uint8_t * , uint32_t);

#ifdef __cplusplus
}
#endif

#endif

