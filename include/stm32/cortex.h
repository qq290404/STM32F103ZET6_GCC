#ifndef __PLATFORM_CORTEX_H__
#define __PLATFORM_CORTEX_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include <stdint.h>

void cortex_enable_irq(void);
void cortex_disable_irq(void);
void cortex_enable_fault_irq(void);
void cortex_disable_fault_irq(void);
void cortex_nop(void);
void cortex_wfi(void);
void cortex_wfe(void);
void cortex_sev(void);
void cortex_isb(void);
void cortex_dsb(void);
void cortex_dmb(void);
void cortex_clrex(void);
uint32_t cortex_get_psp(void);
void cortex_set_psp(uint32_t topOfProcStack);
uint32_t cortex_get_msp(void);
void cortex_set_msp(uint32_t topOfMainStack);
uint32_t cortex_get_basepri(void);
void cortex_set_basepri(uint32_t basePri);
uint32_t  cortex_get_primask(void);
void cortex_set_primask(uint32_t priMask);
uint32_t cortex_get_faultmask(void);
void cortex_set_faultmask(uint32_t faultMask);
uint32_t cortex_get_control(void);
void cortex_set_control(uint32_t control);
uint32_t cortex_rev(uint32_t value);
uint32_t cortex_rev16(uint16_t value);
int32_t cortex_revsh(int16_t value);
uint32_t cortex_rbit(uint32_t value);
uint8_t cortex_ldrexb(uint8_t *addr);
uint16_t cortex_ldrexh(uint16_t *addr);
uint32_t cortex_ldrexw(uint32_t *addr);
uint32_t cortex_strexb(uint8_t value, uint8_t *addr);
uint32_t cortex_strexh(uint16_t value, uint16_t *addr);
uint32_t cortex_strexw(uint32_t value, uint32_t *addr);

#ifdef __cplusplus
}
#endif

#endif
