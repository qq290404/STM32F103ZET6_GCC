#ifndef __PLATFORM_VECTOR_TYPE_H__
#define __PLATFORM_VECTOR_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

void reset_handler(void);
void nmi_handler(void);
void hard_fault_handler(void);
void sv_call_handler(void);
void pend_sv_handler(void);
void sys_tick_handler(void);
void mem_manage_handler(void);
void bus_fault_handler(void);
void usage_fault_handler(void);
void debug_monitor_handler(void);
void wwdg_irq_handler(void);
void pvd_irq_handler(void);
void tamper_irq_handler(void);
void rtc_irq_handler(void);
void flash_irq_handler(void);
void rcc_irq_handler(void);
void exti0_irq_handler(void);
void exti1_irq_handler(void);
void exti2_irq_handler(void);
void exti3_irq_handler(void);
void exti4_irq_handler(void);
void dma1_channel1_irq_handler(void);
void dma1_channel2_irq_handler(void);
void dma1_channel3_irq_handler(void);
void dma1_channel4_irq_handler(void);
void dma1_channel5_irq_handler(void);
void dma1_channel6_irq_handler(void);
void dma1_channel7_irq_handler(void);
void adc1_2_irq_handler(void);
void usb_hp_can1_tx_irq_handler(void);
void usb_lp_can1_rx0_irq_handler(void);
void can1_rx1_irq_handler(void);
void can1_sce_irq_handler(void);
void exti9_5_irq_handler(void);
void tim1_brk_irq_handler(void);
void tim1_up_irq_handler(void);
void tim1_trg_com_irq_handler(void);
void tim1_cc_irq_handler(void);
void tim2_irq_handler(void);
void tim3_irq_handler(void);
void tim4_irq_handler(void);
void i2c1_ev_irq_handler(void);
void i2c1_er_irq_handler(void);
void i2c2_ev_irq_handler(void);
void i2c2_er_irq_handler(void);
void spi1_irq_handler(void);
void spi2_irq_handler(void);
void usart1_irq_handler(void);
void usart2_irq_handler(void);
void usart3_irq_handler(void);
void exti15_10_irq_handler(void);
void rtc_alarm_irq_handler(void);
void usb_wakeup_irq_handler(void);
void tim8_brk_irq_handler(void);
void tim8_up_irq_handler(void);
void tim8_trg_com_irq_handler(void);
void tim8_cc_irq_handler(void);
void adc3_irq_handler(void);
void fsmc_irq_handler(void);
void sdio_irq_handler(void);
void tim5_irq_handler(void);
void spi3_irq_handler(void);
void uart4_irq_handler(void);
void uart5_irq_handler(void);
void tim6_irq_handler(void);
void tim7_irq_handler(void);
void dma2_channel1_irq_handler(void);
void dma2_channel2_irq_handler(void);
void dma2_channel3_irq_handler(void);
void dma2_channel4_5_irq_handler(void);


typedef void (*vector_table_entry_t)(void);
struct vector_table_t {
    unsigned int* initial_sp_value; /**< Initial stack pointer value. */
    vector_table_entry_t reset;
    vector_table_entry_t nmi;
    vector_table_entry_t hard_fault;
    vector_table_entry_t memory_manage_fault; /* not in CM0 */
    vector_table_entry_t bus_fault;           /* not in CM0 */
    vector_table_entry_t usage_fault;         /* not in CM0 */
    vector_table_entry_t reserved1[4];
    vector_table_entry_t sv_call;
    vector_table_entry_t debug_monitor;       /* not in CM0 */
    vector_table_entry_t reserved2;
    vector_table_entry_t pend_sv;
    vector_table_entry_t systick;
    vector_table_entry_t irq[240];
};

#pragma weak nmi_handler = null_handler
//#pragma weak hard_fault_handler = blocking_handler
#pragma weak sv_call_handler = null_handler
#pragma weak pend_sv_handler = null_handler
#pragma weak sys_tick_handler = null_handler
#pragma weak mem_manage_handler = blocking_handler
#pragma weak bus_fault_handler = blocking_handler
#pragma weak usage_fault_handler = blocking_handler
#pragma weak debug_monitor_handler = null_handler
#pragma weak wwdg_irq_handler = null_handler
#pragma weak pvd_irq_handler = null_handler
#pragma weak tamper_irq_handler = null_handler
#pragma weak rtc_irq_handler = null_handler
#pragma weak flash_irq_handler = null_handler
#pragma weak rcc_irq_handler = null_handler
#pragma weak exti0_irq_handler = null_handler
#pragma weak exti1_irq_handler = null_handler
#pragma weak exti2_irq_handler = null_handler
#pragma weak exti3_irq_handler = null_handler
#pragma weak exti4_irq_handler = null_handler
#pragma weak dma1_channel1_irq_handler = null_handler
#pragma weak dma1_channel2_irq_handler = null_handler
#pragma weak dma1_channel3_irq_handler = null_handler
#pragma weak dma1_channel4_irq_handler = null_handler
#pragma weak dma1_channel5_irq_handler = null_handler
#pragma weak dma1_channel6_irq_handler = null_handler
#pragma weak dma1_channel7_irq_handler = null_handler
#pragma weak adc1_2_irq_handler = null_handler
#pragma weak usb_hp_can1_tx_irq_handler = null_handler
#pragma weak usb_lp_can1_rx0_irq_handler = null_handler
#pragma weak can1_rx1_irq_handler = null_handler
#pragma weak can1_sce_irq_handler = null_handler
#pragma weak exti9_5_irq_handler = null_handler
#pragma weak tim1_brk_irq_handler = null_handler
#pragma weak tim1_up_irq_handler = null_handler
#pragma weak tim1_trg_com_irq_handler = null_handler
#pragma weak tim1_cc_irq_handler = null_handler
#pragma weak tim2_irq_handler = null_handler
#pragma weak tim3_irq_handler = null_handler
#pragma weak tim4_irq_handler = null_handler
#pragma weak i2c1_ev_irq_handler = null_handler
#pragma weak i2c1_er_irq_handler = null_handler
#pragma weak i2c2_ev_irq_handler = null_handler
#pragma weak i2c2_er_irq_handler = null_handler
#pragma weak spi1_irq_handler = null_handler
#pragma weak spi2_irq_handler = null_handler
#pragma weak usart1_irq_handler = null_handler
#pragma weak usart2_irq_handler = null_handler
#pragma weak usart3_irq_handler = null_handler
#pragma weak exti15_10_irq_handler = null_handler
#pragma weak rtc_alarm_irq_handler = null_handler
#pragma weak usb_wakeup_irq_handler = null_handler
#pragma weak tim8_brk_irq_handler = null_handler
#pragma weak tim8_up_irq_handler = null_handler
#pragma weak tim8_trg_com_irq_handler = null_handler
#pragma weak tim8_cc_irq_handler = null_handler
#pragma weak adc3_irq_handler = null_handler
#pragma weak fsmc_irq_handler = null_handler
#pragma weak sdio_irq_handler = null_handler
#pragma weak tim5_irq_handler = null_handler
#pragma weak spi3_irq_handler = null_handler
#pragma weak uart4_irq_handler = null_handler
#pragma weak uart5_irq_handler = null_handler
#pragma weak tim6_irq_handler = null_handler
#pragma weak tim7_irq_handler = null_handler
#pragma weak dma2_channel1_irq_handler = null_handler
#pragma weak dma2_channel2_irq_handler = null_handler
#pragma weak dma2_channel3_irq_handler = null_handler
#pragma weak dma2_channel4_5_irq_handler = null_handler

#ifdef __cplusplus
}
#endif

#endif

