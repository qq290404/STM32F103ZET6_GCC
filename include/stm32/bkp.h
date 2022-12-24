#ifndef __PLATFORM_BKP_H__
#define __PLATFORM_BKP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum bkp_dr_e
{
	bkp_dr_1,
	bkp_dr_2,
	bkp_dr_3,
	bkp_dr_4,
	bkp_dr_5,
	bkp_dr_6,
	bkp_dr_7,
	bkp_dr_8,
	bkp_dr_9,
	bkp_dr_10,
	bkp_dr_11,
	bkp_dr_12,
	bkp_dr_13,
	bkp_dr_14,
	bkp_dr_15,
	bkp_dr_16,
	bkp_dr_17,
	bkp_dr_18,
	bkp_dr_19,
	bkp_dr_20,
	bkp_dr_21,
	bkp_dr_22,
	bkp_dr_23,
	bkp_dr_24,
	bkp_dr_25,
	bkp_dr_26,
	bkp_dr_27,
	bkp_dr_28,
	bkp_dr_29,
	bkp_dr_30,
	bkp_dr_31,
	bkp_dr_32,
	bkp_dr_33,
	bkp_dr_34,
	bkp_dr_35,
	bkp_dr_36,
	bkp_dr_37,
	bkp_dr_38,
	bkp_dr_39,
	bkp_dr_40,
	bkp_dr_41,
	bkp_dr_42,
};

void BKP_Write_DR(enum bkp_dr_e, uint16_t);
uint16_t BKP_Read_DR(enum bkp_dr_e);

#ifdef __cplusplus
}
#endif

#endif

