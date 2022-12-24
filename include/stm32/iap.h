#ifndef __PLATFORM_IAP_H__
#define __PLATFORM_IAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

struct iap_image_head_t
{
	uint32_t magic;
	uint32_t crc;
	char time[20];
	uint32_t arch;
	uint32_t type;
	uint32_t entry_point;
	char name[24];
};

struct iap_partition_info_t
{
	uint32_t address;
	uint32_t size;
	uint32_t max_size;
};

enum iap_partition_type_e
{
	iap_partition_type_iboot,
	iap_partition_type_xboot,
	iap_partition_type_uboot,
	iap_partition_type_app,
	iap_partition_type_fs_image,

	iap_partition_type_max
};

enum iap_image_boot_e
{
	iap_image_xboot,
	iap_image_uboot,
	iap_image_app,
};

void UpdatePartitionInfo(void);
const struct iap_partition_info_t* GetPartitionInfo(enum iap_partition_type_e);
bool JumpApplication(enum iap_image_boot_e);

#ifdef __cplusplus
}
#endif

#endif
