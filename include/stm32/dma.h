#ifndef __PLATFORM_DMA_H__
#define __PLATFORM_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef unsigned int HDMA;
#define HDMA_NULL	((HDMA)0)

enum dma_peripheral_address_mapping_e
{
	dma_peripheral_adc1,
};

enum dma_channel_e
{
	dma1_channel1,
	dma1_channel2,
	dma1_channel3,
	dma1_channel4,
	dma1_channel5,
	dma1_channel6,
	dma1_channel7,
	dma2_channel1,
	dma2_channel2,
	dma2_channel3,
	dma2_channel4,
	dma2_channel5,
};

enum dma_data_transfer_dir_e
{
	dma_data_transfer_dir_peripheral,
	dma_data_transfer_dir_memory,
};

enum dma_data_bit_wide_e
{
	dma_data_bit_wide_8bit,
	dma_data_bit_wide_16bit,
	dma_data_bit_wide_32bit,
};

enum dma_priority_e
{
	dma_priority_veryhigh,
	dma_priority_high,
	dma_priority_medium,
	dma_priority_low,
};

enum dma_callback_type_e
{
	dma_callback_transfer_complete,
	dma_callback_transfer_error,
	dma_callback_half_transfer,
};

struct dma_init_t
{
	enum dma_channel_e Channel;
	enum dma_priority_e Priority;
	enum dma_data_transfer_dir_e Dir;
	bool PeripheralIncEn;
	bool MemoryIncEn;
	bool CircularModeEn;
	bool M2MEN;
	enum dma_data_bit_wide_e PeripheralDataBitWide;
	enum dma_data_bit_wide_e MemoryDataBitWide;
	uint32_t PeripheralBaseAddr;
	uint32_t MemoryBaseAddr;
	uint32_t Count;
};

static inline void DMA_StructInit(struct dma_init_t* init, enum dma_channel_e channel)
{
	init->Channel = channel;
	init->Priority = dma_priority_low;
	init->Dir = dma_data_transfer_dir_peripheral;
	init->PeripheralIncEn = false;
	init->MemoryIncEn = false;
	init->CircularModeEn = false;
	init->M2MEN = false;
	init->PeripheralDataBitWide = dma_data_bit_wide_8bit;
	init->MemoryDataBitWide = dma_data_bit_wide_8bit;
	init->PeripheralBaseAddr = 0;
	init->MemoryBaseAddr = 0;
	init->Count = 0;
}

uint32_t DMA_PeripheralAddressMapping(enum dma_peripheral_address_mapping_e);
HDMA DMA_Init(const struct dma_init_t *);
void DMA_DeInit(HDMA);
uint16_t DMA_GetDataCounter(HDMA);
bool DMA_Register_CallBack(HDMA, enum dma_callback_type_e, void (*callbck)(void));
void DMA_UnRegister_CallBack(HDMA, enum dma_callback_type_e);


#ifdef __cplusplus
}
#endif

#endif

