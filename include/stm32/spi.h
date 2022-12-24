#ifndef __PLATFORM_SPI_H__
#define __PLATFORM_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef unsigned int HSPI;
#define HSPI_NULL	((HSPI)0)

enum spi_index_e
{
	spi_index_1,
	spi_index_2,
	spi_index_3,
};

enum spi_direction_e
{
	spi_direction_2lines_fullduplex,
	spi_direction_2lines_rxOnly,
	spi_direction_1line_rx,
	spi_direction_1line_tx,
};

enum spi_mode_e
{
	spi_mode_master,
	spi_mode_slave,
};

enum spi_data_format_e
{
	spi_data_format_8bit,
	spi_data_format_16bit,
};

enum spi_cpol_e
{
	spi_cpol_low,
	spi_cpol_high,
};

enum spi_cpha_e
{
	spi_cpha_1edge,
	spi_cpha_2edge,
};

enum spi_first_bit_format_e
{
	spi_first_bit_format_msb,
	spi_first_bit_format_lsb,
};

enum spi_nss_control_source_e
{
	spi_nss_control_source_soft,
	spi_nss_control_source_hard,
};

struct spi_init_t
{
	enum spi_index_e Index;
	enum spi_direction_e Direction;
	enum spi_mode_e Mode;
	enum spi_data_format_e Format;
	enum spi_cpol_e Cpol;
	enum spi_cpha_e Cpha;
	enum spi_first_bit_format_e FirstBitFormat;
	enum spi_nss_control_source_e Nss;
	uint16_t CRCPolynomial;
};

HSPI SPI_Init(const struct spi_init_t *);
void SPI_DeInit(HSPI);

uint8_t SPI_Read_Data(HSPI);
bool SPI_Write_Data(HSPI, uint8_t);

void SPI_Enable_Device(HSPI, bool);

#ifdef __cplusplus
}
#endif

#endif

