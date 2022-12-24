#ifndef __PLATFORM_CRC_H__
#define __PLATFORM_CRC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "gcc_attribute.h"

void CRC_Reset(void);
uint32_t CRC_CalcUInt32(uint32_t);
uint32_t CRC_Calcuint8_t(const uint8_t *, uint32_t);
uint32_t CRC_Calcuint16_t(const uint16_t *, uint32_t);
uint32_t CRC_Calcuint32_t(const uint32_t *, uint32_t);
uint32_t CRC_GetCRC(void);
void CRC_SetIDRegister(uint8_t);
uint8_t CRC_GetIDRegister(void);

#ifdef __cplusplus
}
#endif

#endif

