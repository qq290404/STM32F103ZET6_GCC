#ifndef __DATA_CACHE_H__
#define __DATA_CACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

enum mcu_packet_cache_type_e
{
	mcu_send_cache,
	mcu_rev_cache,
	mcu_max_cache,
};

struct data_cache_t
{
    unsigned int dRdIndex;
    unsigned int dWrIndex;
    unsigned int dMaxBufLen;
    unsigned char* pBufAddr;
};

void DataCacheInit(struct data_cache_t *, unsigned char *, unsigned int);
bool DataCachePop(struct data_cache_t *, unsigned char *);
bool DataCachePush(struct data_cache_t *, unsigned char);
bool DataCacheCopy(struct data_cache_t *, unsigned char *, unsigned int);
unsigned int DataCacheSize(struct data_cache_t *);
unsigned char* DataCacheWrAddr(struct data_cache_t *);
unsigned char* DataCacheRdAddr(struct data_cache_t *);
unsigned int DataCacheWrIdx(struct data_cache_t *);
unsigned int DataCacheRdIdx(struct data_cache_t *);
void DataCacheSetWrIdx(struct data_cache_t *, unsigned int);
void DataCacheSetRdIdx(struct data_cache_t *, unsigned int);
unsigned char* DataCacheStartAddr(struct data_cache_t *);
unsigned char* DataCacheEndAddr(struct data_cache_t *);

#ifdef __cplusplus
}
#endif

#endif
