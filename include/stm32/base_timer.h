#ifndef __PLATFORM_BASE_TIMER_H__
#define __PLATFORM_BASE_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef unsigned int HBASETIMER;
#define HBASETIMER_NULL	((HBASETIMER)0)

enum base_timer_index_e
{
	base_timer_index_1,
	base_timer_index_2,
};

struct base_timer_init_t
{
	enum base_timer_index_e Index;
	uint16_t Prescaler;
	uint16_t Autoreload;
};

static inline void BaseTimer_StructInit(struct base_timer_init_t* init, enum base_timer_index_e index)
{
	init->Index = index;
	init->Prescaler = 0x0000;
	init->Autoreload = 0x0000;
}

HBASETIMER BaseTimer_Init(struct base_timer_init_t *);
void BaseTimer_DeInit(HBASETIMER);

bool BaseTimer_Register_CallBack(HBASETIMER, void (*callback)(void));
bool BaseTimer_UnRegister_CallBack(HBASETIMER);

#ifdef __cplusplus
}
#endif

#endif

