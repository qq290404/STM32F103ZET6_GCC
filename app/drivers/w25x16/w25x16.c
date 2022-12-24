#include "config.h"
#include "clog.h"
#include "w25x16.h"

//÷∏¡Ó±Ì
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

static HSPI hw25x16 = HSPI_NULL;
static uint8_t w25x16_buffer[4096];

static inline uint8_t SPIx_ReadWriteByte(uint8_t TxData)
{
	uint8_t ret = 0;
	if(SPI_Write_Data(hw25x16, TxData)) {
		ret = SPI_Read_Data(hw25x16);
	}
	return ret;
}

void w25x16_Init(void)
{
	struct spi_init_t init;
	init.Index = spi_index_1;
	init.Direction = spi_direction_2lines_fullduplex;
	init.Mode = spi_mode_master;
	init.Format = spi_data_format_8bit;
	init.Cpol = spi_cpol_high;
	init.Cpha = spi_cpha_2edge;
	init.FirstBitFormat = spi_first_bit_format_msb;
	init.Nss = spi_nss_control_source_soft;
	init.CRCPolynomial = 7;
	hw25x16 = SPI_Init(&init);
}

uint8_t w25x16_Read_SR(void)   
{  
	uint8_t byte = 0;
	SPI_Enable_Device(hw25x16, true);
	SPIx_ReadWriteByte(W25X_ReadStatusReg);
	byte = SPIx_ReadWriteByte(0Xff);
	SPI_Enable_Device(hw25x16, false);
	return byte;   
} 

void w25x16_Write_SR(uint16_t sr)   
{   
	SPI_Enable_Device(hw25x16, true);
	SPIx_ReadWriteByte(W25X_WriteStatusReg);
	SPIx_ReadWriteByte(sr);
	SPI_Enable_Device(hw25x16, false);
}   

void w25x16_Write_Enable(void)   
{
	SPI_Enable_Device(hw25x16, true);
    SPIx_ReadWriteByte(W25X_WriteEnable);
	SPI_Enable_Device(hw25x16, false);
} 

void w25x16_Write_Disable(void)   
{  
	SPI_Enable_Device(hw25x16, true);
    SPIx_ReadWriteByte(W25X_WriteDisable);
	SPI_Enable_Device(hw25x16, false);
} 			    

uint16_t w25x16_Read_ID(void)
{
	uint16_t Temp = 0;	  
	SPI_Enable_Device(hw25x16, true);
	SPIx_ReadWriteByte(0x90);
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	 			   
	Temp |= SPIx_ReadWriteByte(0xFF) << 8;  
	Temp |= SPIx_ReadWriteByte(0xFF) << 0;	 
	SPI_Enable_Device(hw25x16, false);
	return Temp;
}   		    

void w25x16_Read_Buffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{   												    
	SPI_Enable_Device(hw25x16, true);
    SPIx_ReadWriteByte(W25X_ReadData);
    SPIx_ReadWriteByte((uint8_t)((ReadAddr) >> 16));
    SPIx_ReadWriteByte((uint8_t)((ReadAddr) >>   8));   
    SPIx_ReadWriteByte((uint8_t)((ReadAddr) >>  0));   
    for(uint16_t i = 0; i < NumByteToRead; i++) { 
        pBuffer[i]=SPIx_ReadWriteByte(0xFF);
    }
	SPI_Enable_Device(hw25x16, false);
}  

void w25x16_Write_Page(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    w25x16_Write_Enable();
	SPI_Enable_Device(hw25x16, true);
    SPIx_ReadWriteByte(W25X_PageProgram);
    SPIx_ReadWriteByte((uint8_t)((WriteAddr) >>16));
    SPIx_ReadWriteByte((uint8_t)((WriteAddr) >> 8));   
    SPIx_ReadWriteByte((uint8_t)((WriteAddr) >> 0));   
    for(uint16_t i = 0; i < NumByteToWrite; i++) {
		SPIx_ReadWriteByte(pBuffer[i]);
    }
	SPI_Enable_Device(hw25x16, false);
	w25x16_Wait_Busy();
} 

void w25x16_Write_NoCheck(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)   
{ 			 		 
	uint16_t pageremain;	   
	pageremain = 256 - WriteAddr % 256;
	if(NumByteToWrite <= pageremain) {
		pageremain = NumByteToWrite;
	}
	while(1) {	   
		w25x16_Write_Page(pBuffer, WriteAddr, pageremain);
		if(NumByteToWrite==pageremain) {
			break;
		} else {
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite -= pageremain;
			if(NumByteToWrite > 256) pageremain = 256;
			else pageremain=NumByteToWrite;
		}
	};	    
} 
void w25x16_Write_Buffer(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;  
	secpos= WriteAddr / 4096;
	secoff=WriteAddr % 4096;
	secremain= 4096 - secoff;
	if(NumByteToWrite <= secremain) secremain = NumByteToWrite;
	while(1) {	
		w25x16_Read_Buffer(w25x16_buffer, secpos * 4096, 4096);
		for(i = 0; i < secremain; i++) {
			if(w25x16_buffer[secoff+i]!=0XFF)break;
		}
		if(i<secremain) {
			w25x16_Erase_Sector(secpos);
			for(i=0;i<secremain;i++) {
				w25x16_buffer[i+secoff] = pBuffer[i];	  
			}
			w25x16_Write_NoCheck(w25x16_buffer,secpos*4096,4096);
		} else { 
			w25x16_Write_NoCheck(pBuffer,WriteAddr,secremain);
		}
		if(NumByteToWrite==secremain)break;
		else
		{
			secpos++;
			secoff=0;

		   	pBuffer+=secremain;
			WriteAddr+=secremain;
		   	NumByteToWrite-=secremain;
			if(NumByteToWrite>4096)secremain=4096;
			else secremain=NumByteToWrite;
		}	 
	};	 	 
}

void w25x16_Erase_Chip(void)   
{                                             
    w25x16_Write_Enable();
    w25x16_Wait_Busy();   
	SPI_Enable_Device(hw25x16, true);
    SPIx_ReadWriteByte(W25X_ChipErase);
	SPI_Enable_Device(hw25x16, false);
	w25x16_Wait_Busy();
}   

void w25x16_Erase_Sector(uint32_t Dst_Addr)   
{   
	Dst_Addr*=4096;
    w25x16_Write_Enable();
    w25x16_Wait_Busy();   
	SPI_Enable_Device(hw25x16, true);
    SPIx_ReadWriteByte(W25X_SectorErase);
    SPIx_ReadWriteByte((uint8_t)((Dst_Addr)>>16)); 
    SPIx_ReadWriteByte((uint8_t)((Dst_Addr)>>8));   
    SPIx_ReadWriteByte((uint8_t)Dst_Addr);  
	SPI_Enable_Device(hw25x16, false);
    w25x16_Wait_Busy();
}  

void w25x16_Wait_Busy(void)   
{   
	while((w25x16_Read_SR()&0x01)==0x01);
}  

void w25x16_PowerDown(void)   
{ 
	SPI_Enable_Device(hw25x16, true);
    SPIx_ReadWriteByte(W25X_PowerDown);
	SPI_Enable_Device(hw25x16, false);
    DWT_Delay_us(3);
}   

void w25x16_WAKEUP(void)   
{  
	SPI_Enable_Device(hw25x16, true);
    SPIx_ReadWriteByte(W25X_ReleasePowerDown);
	SPI_Enable_Device(hw25x16, false);
    DWT_Delay_us(3);
}   

