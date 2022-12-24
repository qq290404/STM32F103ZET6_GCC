#ifndef __PLATFORM_INIT_H__
#define __PLATFORM_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

void SystemInit(void);
void SystemReset(void);
void PrintSystemInfo(void);
void SystemInfoSave(void);
void SystemInfoRead(void);

#ifdef __cplusplus
}
#endif

#endif
