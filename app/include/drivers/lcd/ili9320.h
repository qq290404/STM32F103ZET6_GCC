#ifndef __LCD_ILI9320_H__
#define __LCD_ILI9320_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void ili9320_Initializtion(void);
void ili9320_SetCursor(uint16_t, uint16_t);
void ili9320_SetWindows(uint16_t, uint16_t, uint16_t, uint16_t);
void ili9320_Clear(uint16_t);
uint16_t ili9320_GetPoint(uint16_t, uint16_t);
void ili9320_SetPoint(uint16_t, uint16_t, uint16_t);
void ili9320_DrawPicture(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t *);
void ili9320_PutChar(uint16_t, uint16_t, uint8_t, uint16_t, uint16_t);
void ili9320_PutChar_16x24(uint16_t, uint16_t, uint8_t, uint16_t, uint16_t);
uint16_t ili9320_BGR2RGB(uint16_t);
void ili9320_BackLight(uint8_t);
void ili9320_Delay(uint32_t);

#ifdef __cplusplus
}
#endif

#endif

