#ifndef __TASK_MANAGEMENT_H__
#define __TASK_MANAGEMENT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "ucos_ii.h"

enum task_type_e
{
	task_type_starter,
	task_type_usage,
	task_type_hearbeat,
	task_type_appmain,

	task_type_max,
};

struct task_stack_info_t
{
	const char* name;
	unsigned int addr;
	unsigned int size;
};

void TaskInit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
