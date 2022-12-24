#include "config.h"
#include "clog.h"
#include "service.h"

#define _SERVICE_MANAGER_DEBUG
#ifdef _SERVICE_MANAGER_DEBUG
#define service_manager_debug_e	QPLOG_ERR
#define service_manager_debug_w	QPLOG_WAR
#define service_manager_debug_d	QPLOG_DEB
#else
#define service_manager_debug_e(fmt, ...)
#define service_manager_debug_w(fmt, ...)
#define service_manager_debug_d(fmt, ...)
#endif

int SrvMng_Service_Request(struct requset_service_t* pRequestSrv)
{
	return 0;
}

int SrvMng_Service_Register(struct register_service_t* pRegisterSrv)
{
    return 0;
}

int SrvMng_Service_UnRegister(struct register_service_t* pRegisterSrv)
{
    return 0;
}

int service_manager_init(void)
{
    return 0;
}

int submit_service(struct requset_service_t* pReqSrv, uint8_t* pBuf, uint32_t dLen)
{
	struct service_payload_t stPayload;

    stPayload.pBuf = pBuf;
    stPayload.dLen = dLen;

    if(pReqSrv->pService) {
		return pReqSrv->pService(&stPayload);
    }

    if(pReqSrv->name) {
        service_manager_debug_w("service function [%s]", pReqSrv->name);
    } else {
        service_manager_debug_e("unkown name service function is not exist!");
    }
    return -1;
}

int callback_service(struct service_packet_header_t* pHeader, uint8_t bComID, const uint8_t* pBuf, uint16_t wLen)
{
    pHeader->bCommandID = bComID;
    if((pHeader->pBuf) && (pHeader->wBufLen >= wLen)) {
        memcpy(pHeader->pBuf, pBuf, wLen);
    }
    return 0;
}

void main_service_entry(void)
{
	int ret = service_init();
	if(ret) {
		service_manager_debug_e("service init is failed(ret = %d)", ret);
		return;
	}
	if(service_option_init() == 0) {

	}
}
