#ifndef __SPI_FLASH_W25X16_H__
#define __SPI_FLASH_W25X16_H__

#include "stdint.h"

//W25X16¶ÁÐ´
#define FLASH_ID 0xEF14

void w25x16_Init(void);
uint8_t w25x16_Read_SR(void);
void w25x16_Write_SR(uint16_t);
void w25x16_Write_Enable(void);
void w25x16_Write_Disable(void);
uint16_t w25x16_Read_ID(void);
void w25x16_Read_Buffer(uint8_t *, uint32_t, uint16_t);
void w25x16_Write_Page(uint8_t *, uint32_t, uint16_t);
void w25x16_Write_NoCheck(uint8_t *, uint32_t, uint16_t);
void w25x16_Write_Buffer(uint8_t *, uint32_t, uint16_t);
void w25x16_Erase_Chip(void);
void w25x16_Erase_Sector(uint32_t);
void w25x16_Wait_Busy(void);
void w25x16_PowerDown(void);  
void w25x16_WAKEUP(void);

#endif
