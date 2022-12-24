#ifndef __PLATFORM_I2C_H__
#define __PLATFORM_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef unsigned int HI2C;
#define HI2C_NULL	((HI2C)0)

#define I2C_SPEED_KHZ(speed) (speed * 1000)
#define I2C_SPEED_MHZ(speed) (speed * I2C_SPEED_KHZ(1000))

enum i2c_index_e
{
	i2c_index_1,
	i2c_index_2,
};

enum i2c_mode_e
{
	i2c_mode_i2c_master,
	i2c_mode_i2c_slave,

	i2c_mode_smbus_master,
	i2c_mode_smbus_slave,
};

enum i2c_address_format_e
{
	i2c_address_format_7bit,
	i2c_address_format_10bit,
};

enum i2c_duty_cycle_e
{
	i2c_duty_cycle_16_9,
	i2c_duty_cycle_2,
};


enum i2c_speed_e
{
	i2c_speed_100k = I2C_SPEED_KHZ(100),
	i2c_speed_400k = I2C_SPEED_KHZ(400),
};

struct i2c_init_t
{
	enum i2c_index_e Index;
	enum i2c_mode_e Mode;
	uint16_t Addr;
	enum i2c_address_format_e AddressFormat;
	uint32_t Speed;
	enum i2c_duty_cycle_e DutyCycle; 
};

static inline void I2C_StructInit(struct i2c_init_t* init, enum i2c_index_e index)
{
	init->Index = index;
	init->Mode = i2c_mode_i2c_master;
	init->Addr = 0x0000;
	init->AddressFormat = i2c_address_format_7bit;
	init->Speed = i2c_speed_400k;
	init->DutyCycle = i2c_duty_cycle_2;
}

HI2C I2C_Init(struct i2c_init_t *);
void I2C_DeInit(HI2C);

void I2C_Write_Data(HI2C, int, const uint8_t *, uint32_t);
void I2C_Read_Data(HI2C, int , uint8_t *, uint32_t);

#ifdef __cplusplus
}
#endif

#endif

