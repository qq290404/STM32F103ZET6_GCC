#include "config.h"
#include "clog.h"
#include "service.h"

#define _SERVICE_INIT_DEBUG
#ifdef _SERVICE_INIT_DEBUG
#define service_init_debug_e	QPLOG_ERR
#define service_init_debug_w	QPLOG_WAR
#define service_init_debug_d	QPLOG_DEB
#else
#define service_init_debug_e(fmt, ...)
#define service_init_debug_w(fmt, ...)
#define service_init_debug_d(fmt, ...)
#endif

int service_option_init(void)
{
	return 0;
}

int service_init(void)
{
	service_init_debug_d("service_manager_init");
	if(service_manager_init() < 0) {
		service_init_debug_e("no service manager!");
		return -1;
	}

	service_init_debug_d("service_system_init");
	if(service_system_init() < 0) {
		service_init_debug_e("no system service!");
		return -1;
	}
}
