#ifndef __PLATFORM_NOR_FLASH_H__
#define __PLATFORM_NOR_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct NOR_IDTypeDef
{
	uint16_t Manufacturer_Code;
	uint16_t Device_Code1;
};

enum NOR_Status
{
	NOR_SUCCESS = 0,
	NOR_ONGOING,
	NOR_ERROR,
	NOR_TIMEOUT
};

void FSMC_NOR_Init(void);
void FSMC_NOR_ReadID(struct NOR_IDTypeDef *);
enum NOR_Status FSMC_NOR_EraseBlock(uint32_t);
enum  NOR_Status FSMC_NOR_EraseChip(void);
enum NOR_Status FSMC_NOR_WriteHalfWord(uint32_t, uint16_t);
enum NOR_Status FSMC_NOR_WriteBuffer(uint16_t *, uint32_t, uint32_t);
enum NOR_Status FSMC_NOR_ProgramBuffer(uint16_t *, uint32_t, uint32_t);
uint16_t FSMC_NOR_ReadHalfWord(uint32_t);
void FSMC_NOR_ReadBuffer(uint16_t *, uint32_t, uint32_t);
enum NOR_Status FSMC_NOR_ReturnToReadMode(void);
enum NOR_Status FSMC_NOR_Reset(void);
enum NOR_Status FSMC_NOR_GetStatus(uint32_t);

#ifdef __cplusplus
}
#endif

#endif

