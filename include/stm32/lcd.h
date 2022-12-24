#ifndef __PLATFORM_LCD_H__
#define __PLATFORM_LCD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void STM32_LCD_Init(void);
void LCD_Light_On(void);
void LCD_Light_Off(void);
void LCD_WriteReg(uint16_t, uint16_t);
uint16_t LCD_ReadReg(uint8_t);
uint16_t LCD_ReadSta(void);
void LCD_WriteCommand(uint16_t);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t);
uint16_t LCD_ReadRAM(void);
void LCD_SetCursor(uint16_t, uint16_t);

#ifdef __cplusplus
}
#endif


#endif
