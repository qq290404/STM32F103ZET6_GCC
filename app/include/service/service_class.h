#ifndef __SERVICE_CLASS_H__
#define __SERVICE_CLASS_H__

struct service_payload_t
{
	uint8_t* pBuf;
	uint32_t dLen;
};

typedef int (*Service)(struct service_payload_t *);
typedef int (*TimeoutRequest)(void);

struct register_service_t
{
	const char* name;
	Service pService;
};

struct requset_service_t
{
	const char* name;
	Service pService;
	TimeoutRequest pRequest;
};

int Service_Register(struct register_service_t *);
int Service_UnRegister(struct register_service_t *);
Service Service_Request(const char *);
int Service_Core_Request(struct requset_service_t *);

#endif
