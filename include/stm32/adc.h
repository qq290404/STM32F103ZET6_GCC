#ifndef __PLATFORM_ADC_H__
#define __PLATFORM_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef unsigned int HADC;
#define HADC_NULL	((HADC)0)

enum adc_mode_e
{
	adc_mode_independent,
	adc_mode_reginjecsimult,
	adc_mode_regsimult_altertrig,
	adc_mode_injecsimult_fastinterl,
	adc_mode_injecsimult_slowinterl,
	adc_mode_injecsimult,
	adc_mode_regsimult,
	adc_mode_fastinterl,
	adc_mode_slowinterl,
	adc_mode_altertrig,
};

enum adc_data_align_e
{
	adc_data_align_left,
	adc_data_align_right,
};

enum adc_index_e
{
	adc_index_1,
	adc_index_2,
	adc_index_3,

	adc_index_max
};

enum adc_channel_e
{
	adc_channel_0,
	adc_channel_1,
	adc_channel_2,
	adc_channel_3,
	adc_channel_4,
	adc_channel_5,
	adc_channel_6,
	adc_channel_7,
	adc_channel_8,
	adc_channel_9,
	adc_channel_10,
	adc_channel_11,
	adc_channel_12,
	adc_channel_13,
	adc_channel_14,
	adc_channel_15,
	adc_channel_16,
	adc_channel_17,
	
	adc_channel_max
};

enum adc_conversion_mode_e
{
	adc_conversion_mode_single,
	adc_conversion_mode_continuous,
	adc_conversion_mode_scan,
	adc_conversion_mode_discontinuous,
};

enum adc_external_trigger_regular_event_e
{
	adc_external_trigger_regular_event_invalid,
	/*!< For ADC1 and ADC2 */
	adc_external_trigger_regular_event_t1_cc1,
	adc_external_trigger_regular_event_t1_cc2,
	adc_external_trigger_regular_event_t2_cc2,
	adc_external_trigger_regular_event_t3_trgo,
	adc_external_trigger_regular_event_t4_cc4,
	adc_external_trigger_regular_event_ext_it11_tim8_trgo,

	/*!< For ADC1, ADC2 and ADC3 */
	adc_external_trigger_regular_event_t1_cc3,
	adc_external_trigger_regular_event_none,

	/*!< For ADC3 only */
	adc_external_trigger_regular_event_t3_cc1,
	adc_external_trigger_regular_event_t2_cc3,
	adc_external_trigger_regular_event_t8_cc1,
	adc_external_trigger_regular_event_t8_trgo,
	adc_external_trigger_regular_event_t5_cc1,
	adc_external_trigger_regular_event_t5_cc3,
};

enum adc_external_trigger_injected_event_e
{
	adc_external_trigger_injected_event_invalid,
	/*!< For ADC1 and ADC2 */
	adc_external_trigger_injected_event_t2_trgo,
	adc_external_trigger_injected_event_t2_cc1,
	adc_external_trigger_injected_event_t3_cc4,
	adc_external_trigger_injected_event_t4_trgo,
	adc_external_trigger_injected_event_ext_it15_tim8_cc4,

	/*!< For ADC1, ADC2 and ADC3 */
	adc_external_trigger_injected_event_t1_trgo,
	adc_external_trigger_injected_event_t1_cc4,
	adc_external_trigger_injected_event_t1_none,

	/*!< For ADC3 only */
	adc_external_trigger_injected_event_t4_cc3,
	adc_external_trigger_injected_event_t8_cc2,
	adc_external_trigger_injected_event_t8_cc4,
	adc_external_trigger_injected_event_t5_trgo,
	adc_external_trigger_injected_event_t5_cc4,
};

enum adc_sampletime_e
{
	adc_sampletime_1cycles5,
	adc_sampletime_7cycles5,
	adc_sampletime_13cycles5,
	adc_sampletime_28cycles5,
	adc_sampletime_41cycles5,
	adc_sampletime_55cycles5,
	adc_sampletime_71cycles5,
	adc_sampletime_239cycles5,
};

struct adc_channel_setting_t
{
	bool En;
	uint8_t ChannelCount;
	const enum adc_channel_e* ChannelList;
	int Event;
};

struct adc_init_t
{
	enum adc_index_e Index;
	enum adc_mode_e Mode;
	enum adc_conversion_mode_e ConversionMode;
	enum adc_data_align_e DataAlign;
	enum adc_sampletime_e Sampletime;

	struct adc_channel_setting_t RegularChannels;
	struct adc_channel_setting_t InjectedChannels;
};

static inline void ADC_StructRegisterChannels(struct adc_channel_setting_t* channel_setting_t, uint8_t count, const enum adc_channel_e* list, int event)
{
	channel_setting_t->En = true;
	channel_setting_t->ChannelCount = count;
	channel_setting_t->ChannelList = list;
	channel_setting_t->Event = event;
}

static inline void ADC_StructUnRegisterChannels(struct adc_channel_setting_t* channel_setting_t)
{
	channel_setting_t->En = false;
	channel_setting_t->ChannelCount = 0;
	channel_setting_t->ChannelList = NULL;
	channel_setting_t->Event = 0;
}

static inline void ADC_StructInit(struct adc_init_t* init, enum adc_index_e index)
{
	init->Index = index;
	init->Mode = adc_mode_independent;
	init->ConversionMode = adc_conversion_mode_continuous;
	init->DataAlign = adc_data_align_right;
	init->Sampletime = adc_sampletime_1cycles5;
	ADC_StructUnRegisterChannels(&init->RegularChannels);
	ADC_StructUnRegisterChannels(&init->InjectedChannels);
}

#define ADC_INIT_GET_INDEX(init)					((init)->Index)
#define ADC_INIT_SET_INDEX(init, index)				(ADC_INIT_GET_INDEX(init) = index)

#define ADC_INIT_GET_MODE(init)						((init)->Mode)
#define ADC_INIT_SET_MODE(init, mode)				(ADC_INIT_GET_MODE(init) = mode)

#define ADC_INIT_GET_CONVERSIONMODE(init)			((init)->ConversionMode)
#define ADC_INIT_SET_CONVERSIONMODE(init, mode)		(ADC_INIT_GET_CONVERSIONMODE(init) = mode)

#define ADC_INIT_GET_DATAALIGN(init)				((init)->DataAlign)
#define ADC_INIT_SET_DATAALIGN(init, align)			(ADC_INIT_GET_DATAALIGN(init) = align)

#define ADC_INIT_GET_SAMPLETIME(init)				((init)->Sampletime)
#define ADC_INIT_SET_SAMPLETIME(init, time)			(ADC_INIT_GET_SAMPLETIME(init) = time)

void ADC_Enable_Temperature_Sensor(void);
void ADC_Disable_Temperature_Sensor(void);

HADC ADC_Init(const struct adc_init_t *);
void ADC_DeInit(HADC);
uint32_t ADC_Read_Value(HADC);
void ADC_Enable_DMA(HADC, uint32_t *, uint32_t);

#ifdef __cplusplus
}
#endif

#endif

