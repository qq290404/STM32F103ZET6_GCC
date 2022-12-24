#ifndef __PLATFORM_RCC_H__
#define __PLATFORM_RCC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define MHZ(x) (x * 1000000)
#define KHZ(x) (x * 1000)
#define HZ(x)  (x)

enum rcc_clock_tree_e
{
	rcc_clock_lse,
	rcc_clock_lsi,
	rcc_clock_hsi,
	rcc_clock_hse,

	rcc_clock_pll, 	//max 72MHz
	rcc_clock_system, //max 72MHz
	rcc_clock_rtc,
	rcc_clock_iwdg,
	rcc_clock_fltf,
	
	rcc_clock_usb,	// 48MHz
	rcc_clock_mco,  //max 50MHz
	rcc_clock_hclk,

	rcc_clock_ahb,
	rcc_clock_apb1,
	rcc_clock_apb2,
	rcc_clock_core,
	rcc_clock_memory,
	rcc_clock_dma,

	rcc_clock_cortex_system_timer,
	rcc_clock_fclk,
	rcc_clock_apb1_timer,
	rcc_clock_apb2_timer,
	rcc_clock_adc,
	rcc_clock_sdio,
	rcc_clock_i2s2,
	rcc_clock_i2s3,
	rcc_clock_fsmc,

	rcc_clock_tree_max
};

enum rcc_pll_clock_source_e
{
	rcc_pll_clock_source_hse_1div,
	rcc_pll_clock_source_hse_2div,
	rcc_pll_clock_source_hsi_2div,
};

enum rcc_pll_mul_e
{
	rcc_pll_mul_2,
	rcc_pll_mul_3,
	rcc_pll_mul_4,
	rcc_pll_mul_5,
	rcc_pll_mul_6,
	rcc_pll_mul_7,
	rcc_pll_mul_8,
	rcc_pll_mul_9,
	rcc_pll_mul_10,
	rcc_pll_mul_11,
	rcc_pll_mul_12,
	rcc_pll_mul_13,
	rcc_pll_mul_14,
	rcc_pll_mul_15,
	rcc_pll_mul_16,
};

enum rcc_system_clock_source_e
{
	rcc_system_clock_source_hsi,
	rcc_system_clock_source_hse,
	rcc_system_clock_source_pll,
};

enum rcc_rtc_clock_source_e
{
	rcc_rtc_clock_source_hse_128div,
	rcc_rtc_clock_source_lse,
	rcc_rtc_clock_source_lsi,
};

enum rcc_mco_clock_source_e
{
	rcc_mco_clock_source_none,
	rcc_mco_clock_source_pllclk_2div,
	rcc_mco_clock_source_hsi,
	rcc_mco_clock_source_hse,
	rcc_mco_clock_source_sysclk,
};

enum rcc_clock_prescaler_e
{
	rcc_clock_prescaler_1,
	rcc_clock_prescaler_1_5,
	rcc_clock_prescaler_2,
	rcc_clock_prescaler_4,
	rcc_clock_prescaler_6,
	rcc_clock_prescaler_8,
	rcc_clock_prescaler_16,
	rcc_clock_prescaler_64,
	rcc_clock_prescaler_128,
	rcc_clock_prescaler_256,
	rcc_clock_prescaler_512,
};

enum rcc_flash_wait_state_e
{
	rcc_flash_wait_state_0,
	rcc_flash_wait_state_1,
	rcc_flash_wait_state_2,
};

struct rcc_clock_enable_t
{
	bool USART1EN;
	bool USART2EN;
	bool USART3EN;
	bool UART4EN;
	bool UART5EN;
	
	bool AFIOEN;
	bool IOPAEN;
	bool IOPBEN;
	bool IOPCEN;
	bool IOPDEN;
	bool IOPEEN;
	bool IOPFEN;
	bool IOPGEN;

	bool ADC1EN;
	bool ADC2EN;
	bool ADC3EN;

	bool SPI1EN;
	bool SPI2EN;
	bool SPI3EN;

	bool DMA1EN;
	bool DMA2EN;

	bool I2C1EN;
	bool I2C2EN;

	bool TIM1EN;
	bool TIM2EN;
	bool TIM3EN;
	bool TIM4EN;
	bool TIM5EN;
	bool TIM6EN;
	bool TIM7EN;
	bool TIM8EN;

	bool SDIOEN;
	bool FSMCEN;
	bool CRCEN;
	bool FLITFEN;
	bool SRAMEN;
	bool DACEN;
	bool PWREN;
	bool BKPEN;
	bool CANEN;
	bool USBEN;
	bool WWDGEN;
	bool RTCEN;
};

struct rcc_clock_scale_t
{
	uint32_t lse;
	uint32_t lsi;
	uint32_t hsi;
	uint32_t hse;

	enum rcc_pll_clock_source_e pll_source;
	enum rcc_pll_mul_e pll_mul;
	
	enum rcc_system_clock_source_e sysclk_source;
	enum rcc_rtc_clock_source_e rtc_source;
	enum rcc_mco_clock_source_e mco_source;
	
	enum rcc_clock_prescaler_e ahb_prescaler;
	enum rcc_clock_prescaler_e apb1_prescaler;
	enum rcc_clock_prescaler_e apb2_prescaler;
	enum rcc_clock_prescaler_e usb_prescaler;
	enum rcc_clock_prescaler_e adc_prescaler;
	enum rcc_clock_prescaler_e cortex_system_timer_prescaler;

	enum rcc_flash_wait_state_e flash_waitstates;

	struct rcc_clock_enable_t  clock_enable;
};

void RCC_Clock_Setup_Init(const struct rcc_clock_scale_t *);
void RCC_Update_Clock_Tree(const struct rcc_clock_scale_t*);
uint32_t RCC_Get_Clock_Freq(enum rcc_clock_tree_e);
void RCC_Print_Clock_Freq(enum rcc_clock_tree_e, const char *);

#ifdef __cplusplus
}
#endif

#endif

