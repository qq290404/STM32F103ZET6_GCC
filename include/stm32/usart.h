#ifndef __PLATFORM_USART_H__
#define __PLATFORM_USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef unsigned int HUSART;
#define HUSART_NULL	((HUSART)0)

#define BAUD(baud)	(baud)

enum usart_type_e
{
	usart_type_1,
	usart_type_2,
	usart_type_3,
};

enum usart_baud_e
{
	usart_baud_110 		= BAUD(110),
	usart_baud_300		= BAUD(300),
	usart_baud_600 		= BAUD(600),
	usart_baud_1200		= BAUD(1200),
	usart_baud_2400		= BAUD(2400),
	usart_baud_4800		= BAUD(4800),
	usart_baud_9600		= BAUD(9600),
	usart_baud_14400	= BAUD(14400),
	usart_baud_19200	= BAUD(19200),
	usart_baud_38400	= BAUD(38400),
	usart_baud_56000	= BAUD(56000),
	usart_baud_57600	= BAUD(57600),
	usart_baud_115200	= BAUD(115200),
	usart_baud_230400	= BAUD(230400),
	usart_baud_460800	= BAUD(460800),
	usart_baud_921600	= BAUD(921600),
	usart_baud_1000000	= BAUD(1000000),
	usart_baud_2000000	= BAUD(2000000),
	usart_baud_3000000	= BAUD(3000000),
	usart_baud_4000000	= BAUD(4000000),
};

enum usart_stop_bits_e
{
	usart_stop_bits_0_5,
	usart_stop_bits_1,
	usart_stop_bits_1_5,
	usart_stop_bits_2,
};

enum usart_word_length_e
{
	usart_word_length_8bit,
	usart_word_length_9bit,
};

enum usart_parity_e
{
	usart_parity_null,
	usart_parity_even,
	usart_parity_odd,
};

enum usart_mode_e
{
	usart_mode_tx,
	usart_mode_rx,
	usart_mode_rx_tx,
};

enum usart_flow_control_e
{
	usart_flow_control_none,
	usart_flow_control_rts,
	usart_flow_control_cts,
	usart_flow_control_rts_cts,
};

struct usart_init_t
{
	enum usart_type_e type;
	enum usart_baud_e baud;
	enum usart_word_length_e word_length;
	enum usart_stop_bits_e stop_bits;
	enum usart_parity_e parity;
	enum usart_mode_e mode;
	enum usart_flow_control_e flow_control;
};

static inline void USART_StructInit(struct usart_init_t* init, enum usart_type_e type)
{
	init->type 			= type;
	init->baud 			= usart_baud_115200;
	init->word_length	= usart_word_length_8bit;
	init->stop_bits		= usart_stop_bits_1;
	init->parity 		= usart_parity_null;
	init->mode 			= usart_mode_rx_tx;
	init->flow_control 	= usart_flow_control_none;
}

HUSART USART_Init(const struct usart_init_t *);
void USART_DeInit(HUSART);

void USART_SendData(HUSART , uint8_t);
void USART_SendBuff(HUSART, const uint8_t *, uint32_t);

#ifdef __cplusplus
}
#endif

#endif

