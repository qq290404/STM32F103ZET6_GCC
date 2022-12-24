#ifndef __USERINIT_H__
#define __USERINIT_H__

#define __VERSION_NUM   "0.0.1"
#define __CONSUMER_NAME "Unkonw"

#define UCOSII_STACK_MEM_SIZE	(10 << 10)

#define SUPPORT_STATRER_TASK
#define STATRER_TASK_STACK_SIZE (2 << 10)
#define STATRER_TASK_PRIO		(4)

#define SUPPORT_CPU_USAGE_TASK
#define CPU_USAGE_TASK_STACK_SIZE (2 << 10)
#define CPU_USAGE_TASK_PRIO		  (30)

#define SUPPORT_HEARBEAT_TASK
#define HEARBEAT_TASK_STACK_SIZE (2 << 10)
#define HEARBEAT_USAGE_TASK_PRIO (5)

#define SUPPORT_APPMAIN_TASK
#define APPMAIN_TASK_STACK_SIZE (2 << 10)
#define APPMAIN_USAGE_TASK_PRIO (6)


#endif
