#ifndef __BASE_SERVICE_H__
#define __BASE_SERVICE_H__

#define TouchSrvName    "touch"

enum service_type_e
{
    SRV_TYPE_TOUCH,
};

struct service_packet_header_t
{
    uint8_t bCommandID;
    uint8_t bTypeID;
    uint16_t wPayloadLen;
    uint8_t* pPayload;
    uint16_t wBufLen;
    uint8_t* pBuf;
};

#include "service_class.h"

#include "service_manager.h"
#include "service_init.h"
#include "service_system.h"

#include "service_touch.h"

#endif
