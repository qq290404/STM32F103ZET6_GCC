#ifndef __SERVICE_AP_H__
#define __SERVICE_AP_H__

struct service_manager_t
{
    int service_fd;
};

int SrvMng_Service_Request(struct requset_service_t *);
int SrvMng_Service_Register(struct register_service_t *);
int SrvMng_Service_UnRegister(struct register_service_t *);
int service_manager_init(void);
int submit_service(struct requset_service_t *, uint8_t *, uint32_t);
int callback_service(struct service_packet_header_t *, uint8_t, const uint8_t *, uint16_t);
#endif
