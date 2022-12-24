#ifndef __PLATFORM_WWDG_H__
#define __PLATFORM_WWDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef unsigned int HWWDG;
#define HWWDG_NULL	((HWWDG)0)

HWWDG WWDG_Init(void);
void WWDG_DeInit(HWWDG);

#ifdef __cplusplus
}
#endif

#endif

