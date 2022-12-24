#include "config.h"
#include "task.h"
#include "clog.h"

#include "ucos_ii.h"

#define _TASK_DEBUG
#ifdef _TASK_DEBUG
#define task_debug_e	QPLOG_ERR
#define task_debug_w	QPLOG_WAR
#define task_debug_d	QPLOG_DEB
#else
#define task_debug_e(fmt, ...)
#define task_debug_w(fmt, ...)
#define task_debug_d(fmt, ...)
#endif

void main_service_entry(void);


#define START_TASK_STK_SIZE   1024

static OS_STK task_stack[UCOSII_STACK_MEM_SIZE];
static struct task_stack_info_t task_stack_info[task_type_max];

static void TaskStackInfoInit(struct task_stack_info_t* info, const char* name, unsigned int size, unsigned int stack_addr)
{
	info->name = name;
	info->size = sizeof(OS_STK) * size;
	info->addr = stack_addr + sizeof(OS_STK) * (size - 1);
}

static void Task_Usage(void* arg)
{
	while(1) {
		task_debug_d("CPU Usage %d%%", OSCPUUsage);
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

static void Task_LED(void* arg)
{
	HGPIO hled = GPIO_Init(eHW_GPIOF, eHW_GPIO_Pin_6);
	GPIO_Set_Mode(hled, eHW_GPIO_MODE_OUTPUT_PUSH_PULL);
	GPIO_Set_Status(hled, eHW_GPIO_STS_HIGHT);

	while(1) {
		GPIO_Toggle_Status(hled);
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

static void Task_AppMain(void* arg)
{
	main_service_entry();
	while(1) {
		task_debug_d("appmain!");
		OSTimeDlyHMSM(0, 0, 2, 0);
	}
}

static void Task_Starter(void* arg)
{
	struct task_stack_info_t* info_t = NULL;

	OSStatInit();

#ifdef SUPPORT_CPU_USAGE_TASK
		info_t = &task_stack_info[task_type_usage];
		OSTaskCreate(Task_Usage, (void *)0, (OS_STK *)info_t->addr, CPU_USAGE_TASK_PRIO);
#endif
#ifdef SUPPORT_HEARBEAT_TASK
		info_t = &task_stack_info[task_type_hearbeat];
		OSTaskCreate(Task_LED, (void *)0, (OS_STK *)info_t->addr, HEARBEAT_USAGE_TASK_PRIO);
#endif
#ifdef SUPPORT_APPMAIN_TASK
		info_t = &task_stack_info[task_type_appmain];
		OSTaskCreate(Task_AppMain, (void *)0, (OS_STK *)info_t->addr, APPMAIN_USAGE_TASK_PRIO);
#endif

	while(1) {
		OSTaskDel(STATRER_TASK_PRIO);
	}
}

void TaskInit(void)
{
	struct task_stack_info_t* info_t = NULL;
	unsigned int stack_st_addr = (unsigned int)task_stack;

	memset(task_stack, 0, UCOSII_STACK_MEM_SIZE * sizeof(OS_STK));
	memset(task_stack_info, 0, task_type_max * sizeof(struct task_stack_info_t));
	
#ifdef SUPPORT_STATRER_TASK
	info_t = &task_stack_info[task_type_starter];
	TaskStackInfoInit(info_t, "starter", STATRER_TASK_STACK_SIZE, stack_st_addr);
	stack_st_addr += info_t->size;
#endif
#ifdef SUPPORT_CPU_USAGE_TASK
	info_t = &task_stack_info[task_type_usage];
	TaskStackInfoInit(info_t, "usage", CPU_USAGE_TASK_STACK_SIZE, stack_st_addr);
	stack_st_addr += info_t->size;
#endif
#ifdef SUPPORT_HEARBEAT_TASK
	info_t = &task_stack_info[task_type_hearbeat];
	TaskStackInfoInit(info_t, "hearbeat",  HEARBEAT_TASK_STACK_SIZE, stack_st_addr);
	stack_st_addr += info_t->size;
#endif
#ifdef SUPPORT_APPMAIN_TASK
	info_t = &task_stack_info[task_type_appmain];
	TaskStackInfoInit(info_t, "appmain",  APPMAIN_TASK_STACK_SIZE, stack_st_addr);
	stack_st_addr += info_t->size;
#endif
	
	if(stack_st_addr >= ((unsigned int)task_stack + sizeof(task_stack))) {
		task_debug_e("ucosii stack overflow!!!");
		return;
	}

#ifdef SUPPORT_STATRER_TASK
	info_t = &task_stack_info[task_type_starter];
	OSTaskCreate(Task_Starter, (void *)0, (OS_STK *)info_t->addr, STATRER_TASK_PRIO);
#endif
}

