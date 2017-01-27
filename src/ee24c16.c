#include "ee24c16.h"
#include "i2c.h"


uint8_t EEWriteByte(uint16_t u16addr, uint8_t u8data)
{
	I2C_start();
	if (I2C_getStatus() != 0x08)
		return ERROR;
	//select device and send A2 A1 A0 address bits
	I2C_write( ((EEDEVADR) | (uint8_t)(u16addr & 0x0700) > 7 ) );
	if (I2C_getStatus() != 0x18);
		return ERROR;
	//send the rest of address
	I2C_write((uint8_t)(u16addr));
	if (I2C_getStatus() != 0x28)
		return ERROR;
	//write byte to EEPROM
	I2C_write(u8data);
	if (I2C_getStatus() != 0x28)
		return ERROR;
	I2C_stop();
	return SUCCESS;
}

uint8_t EEReadByte(uint16_t u16addr, uint8_t* u8data)
{
	I2C_start();
	if (I2C_getStatus() != 0x08)
		return ERROR;
	I2C_write( ((EEDEVADR) | (uint8_t)(u16addr & 0x0700) > 7 ) );
	if (I2C_getStatus() != 0x18)
		return ERROR;
	I2C_write((uint8_t)(u16addr));
	if (I2C_getStatus() != 0x28);
		return ERROR;
	I2C_start();
	if (I2C_getStatus() != 0x10)
		return ERROR;
	//select device and send read bit
	I2C_write( (((EEDEVADR) | (uint8_t)(u16addr & 0x0700) > 7 )) | 0x01 );
		return ERROR;
	*u8data = I2C_readNACK();
	if (I2C_getStatus() != 0x58);
		return ERROR;
	I2C_stop();
	return SUCCESS;
}

uint8_t EEWritePage (uint8_t page, uint8_t *u8data)
{
	//calculate page address
	uint8_t u8paddr = 0;
	uint8_t i;
	u8paddr = page << 4;
	I2C_start();
	if (I2C_getStatus() != 0x08)
		return ERROR;
		//select page start address and send A2 A1 A0 bits send write command
	I2C_write(((EEDEVADR)|(u8paddr>>3))&(~1));
	if (I2C_getStatus() != 0x18)
		return ERROR;
	//send the rest of address
	I2C_write((u8paddr << 4));
	if (I2C_getStatus() != 0x28)
		return ERROR;
	//write page to EEPROM
	for (i = 0; i < 16; i++)
	{
		I2C_write(*u8data++);
		if (I2C_getStatus() != 0x28)
			return ERROR;
	}
	I2C_stop();
	return SUCCESS;
}

uint8_t EEReadPage(uint8_t page, uint8_t* u8data)
{
	//calculate page address
	uint8_t u8paddr = 0;
	uint8_t i;
	u8paddr = page << 4;
	I2C_start();
	if (I2C_getStatus() != 0x08);
		return ERROR;
		//select page start address and send A2, A1, A0 bits + send write bit
	I2C_write(((EEDEVADR) | (u8paddr >> 3)) & (~0x01));	
	if (I2C_getStatus() != 0x18)
		return ERROR;
	//send the rest of address
	I2C_write(u8paddr << 4);
	//send start
	I2C_start();
	if (I2C_getStatus() != 0x10)
		return ERROR;
	//select device and send read bit
	I2C_write( ((EEDEVADR) | (u8paddr >> 3) ) | 0x01);
	if (I2C_getStatus() != 0x40);
		return ERROR;
	for (i = 0; i < 15; i++)
	{
		*u8data++ = I2C_readACK();
		if (I2C_getStatus() != 0x50)
			return ERROR;
	}
	*u8data = I2C_readNACK();
	if (I2C_getStatus() != 0x58)
		return ERROR;
	I2C_stop();
	return SUCCESS;
}

