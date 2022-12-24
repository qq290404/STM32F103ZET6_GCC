#ifndef __SERVICE_TOUCH_H__
#define __SERVICE_TOUCH_H__

struct touch_srv_packet_t
{
	uint8_t  bEventId;
	uint16_t wXStart;
	uint16_t wYStart;
	uint16_t wXNow;
	uint16_t wYNow;
};

enum touch_command_id_e
{
	SRV_GET_TOUCH_COORDINATE,
};

enum touch_panel_event_e
{
	EVENT_IDLE = 0,		//up --> untouch
	EVENT_DOWN,   		//untouch --> touch
	EVENT_MOVE,   		//x1 - x2 > x_range
	EVENT_KEEP,   		//current counter > keep_counter
	EVENT_KEEPMOVE,
	EVENT_UP,			//touch --> untouch
	EVENT_UP_PLT,		//touch --> untouch(Press LongTime)
	EVENT_MAX
};

int service_read_touch_info(int *, int *, int *);
int service_touch_init(void);

#endif
