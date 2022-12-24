#ifndef __PLATFORM_VECTOR_H__
#define __PLATFORM_VECTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef void (*irq_vector_handler)(void);

enum irq_vector_type_e
{
	irq_vector_type_systick,
	irq_vector_type_wwdg,
	irq_vector_type_pvd,
	irq_vector_type_tamper,
	irq_vector_type_rcc,
	irq_vector_type_flash,
	irq_vector_type_rtc,
	irq_vector_type_rtc_alarm,
	irq_vector_type_fsmc,
	irq_vector_type_sdio,
	irq_vector_type_exti0,
	irq_vector_type_exti1,
	irq_vector_type_exti2,
	irq_vector_type_exti3,
	irq_vector_type_exti4,
	irq_vector_type_exti5,
	irq_vector_type_exti6,
	irq_vector_type_exti7,
	irq_vector_type_exti8,
	irq_vector_type_exti9,
	irq_vector_type_exti10,
	irq_vector_type_exti11,
	irq_vector_type_exti12,
	irq_vector_type_exti13,
	irq_vector_type_exti14,
	irq_vector_type_exti15,
	irq_vector_type_dma1_channel1,
	irq_vector_type_dma1_channel2,
	irq_vector_type_dma1_channel3,
	irq_vector_type_dma1_channel4,
	irq_vector_type_dma1_channel5,
	irq_vector_type_dma1_channel6,
	irq_vector_type_dma1_channel7,
	irq_vector_type_dma2_channel1,
	irq_vector_type_dma2_channel2,
	irq_vector_type_dma2_channel3,
	irq_vector_type_dma2_channel4,
	irq_vector_type_dma2_channel5,
	irq_vector_type_adc1,
	irq_vector_type_adc2,
	irq_vector_type_adc3,
	irq_vector_type_usb_hp,
	irq_vector_type_usb_lp,
	irq_vector_type_usb_wakeup,
	irq_vector_type_can1_tx,
	irq_vector_type_can1_rx0,
	irq_vector_type_can1_rx1,
	irq_vector_type_can1_sce,
	irq_vector_type_i2c1_ev,
	irq_vector_type_i2c1_er,
	irq_vector_type_i2c2_ev,
	irq_vector_type_i2c2_er,
	irq_vector_type_spi1,
	irq_vector_type_spi2,
	irq_vector_type_spi3,
	irq_vector_type_usart1,
	irq_vector_type_usart2,
	irq_vector_type_usart3,
	irq_vector_type_uart4,
	irq_vector_type_uart5,
	irq_vector_type_tim1_brk,
	irq_vector_type_tim1_up,
	irq_vector_type_tim1_trg_com,
	irq_vector_type_tim1_cc,
	irq_vector_type_tim2,
	irq_vector_type_tim3,
	irq_vector_type_tim4,
	irq_vector_type_tim5,
	irq_vector_type_tim6,
	irq_vector_type_tim7,
	irq_vector_type_tim8_brk,
	irq_vector_type_tim8_up,
	irq_vector_type_tim8_trg_com,
	irq_vector_type_tim8_cc,
	
	irq_vector_type_max,
};

bool IsIrqHandlerEmpty(enum irq_vector_type_e);
bool RegisterIrqHandler(enum irq_vector_type_e, irq_vector_handler);
void UnRegisterIrqHandler(enum irq_vector_type_e);

#ifdef __cplusplus
}
#endif

#endif

