#include "gcc_attribute.h"
#include "stm32_mem.h"

#include "stm32/init.h"
#include "stm32/cortex.h"

void SystemPrintInit(void);

void boot_main(void)
{
	SystemInfoRead();
	SystemPrintInit();
}

