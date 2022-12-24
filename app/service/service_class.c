#include "config.h"
#include "service.h"

int Service_Register(struct register_service_t* pRegService)
{
	const char* name = NULL;
	Service pService = NULL;
	if(pRegService) {
		name = pRegService->name;
		pService = pRegService->pService;
	}
	if(!name || !pService) {
		return -1;
	}
	return 0;
}

int Service_UnRegister(struct register_service_t* pRegService)
{
	return 0;
}

Service Service_Request(const char* name)
{
	return NULL;
}

int Service_Core_Request(struct requset_service_t* pRequest)
{
	return 0;
}
