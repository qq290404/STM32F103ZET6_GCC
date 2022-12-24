#include "config.h"
#include "clog.h"
#include "service.h"

static struct requset_service_t req_srv_touch =
{
	TouchSrvName,
	NULL,
	service_touch_init,
};

static int submit_touch_service(uint8_t* pBuf, int len)
{
	struct requset_service_t* pSrvTouch = &req_srv_touch;
	struct service_packet_header_t Header;
	
	Header.bTypeID    = SRV_TYPE_TOUCH;
	Header.bCommandID = SRV_GET_TOUCH_COORDINATE;
	Header.pBuf       = pBuf;
	Header.wBufLen    = len;

	return submit_service(pSrvTouch, (uint8_t *)&Header, sizeof(struct service_packet_header_t));
}

int service_read_touch_info(int* event_type, int* x, int* y)
{
	struct touch_srv_packet_t stTouchPacket;

	stTouchPacket.bEventId = EVENT_IDLE;
	stTouchPacket.wXNow = 0;
	stTouchPacket.wYNow = 0;

	if(submit_touch_service((uint8_t *)&stTouchPacket, sizeof(struct touch_srv_packet_t)) < 0) {
		return -1;
	}

	*event_type = stTouchPacket.bEventId;
	*x = stTouchPacket.wXNow;
	*y = stTouchPacket.wYNow;
	return 0;
}

int service_touch_init(void)
{
	struct requset_service_t* pSrvTouch  = &req_srv_touch;

	SrvMng_Service_Request(pSrvTouch);

	if(pSrvTouch->pService == NULL) {
		QPLOG_WAR("%s fail\n",__FUNCTION__);
		return -1;
	}
	return 0;
}

