#ifndef 
#define _EE24C16_H_

#define ERROR -1
#define SUCCESS 1
#define EEDEVADR 0b10100000

uint8_t EEWriteByte(uint16_t u16addr, uint8_t u8data);
uint8_t EEReadByte(uint16_t u16addr, uint8_t* u8data);
uint8_t EEWritePage (uint8_t page, uint8_t *u8data);
uint8_t EEReadPage(uint8_t page, uint8_t* u8data);
#endif
