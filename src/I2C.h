#ifndef 
#define _I2C_H_

void I2C_init(void)
{
	TWSR = 0x00;
	TWBR = 0x0C; // 200kHz on 8MHz
	TWCR |= (1 << TWEN);
}

void I2C_start(void)
{
	TWCR |= (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);
	while ((TWCR & (1 << TWINT)) == 0);
}

void I2C_stop(void)
{
	TWCR |= (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
}

void I2C_write(uint8_t data)
{
	TWDR = data;
	TWCR |= (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0);
}

uint8_t I2C_readACK(void)
{
	TWCR |= (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while ((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}

uint8_t I2C_readNACK(void)
{
	TWCR |= (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}

uint8_t I2C_getStatus(void)
{
	uint8_t status;
	status = TWSR & 0xF8;
	return status;
}

#endif
