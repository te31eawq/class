#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "../../Periph/I2C/I2C.h"

#define LCDcontrolport PORTB
#define LCDcontrolddr DDRB
#define LCDdataddr DDRC

#define LCD_RS	0
#define LCD_RW		1
#define LCD_E		2
#define LCD_SLA		0x27
#define LCD_SLA_W	LCD_SLA<<1
#define LCD_BLACKLIGHT 3

#define functionset 0x38
#define LCD_4bit_FUNCTIONSET 0x28
#define displayoff 0x08
#define displayclear 0x01
#define entrymodeset 0x06
#define displayon 0x0c

void LCD_sendToI2C(uint8_t sla_w, uint8_t data);

void LCD_writeNibble(uint8_t data);
void LCD_blacklighton();
void LCD_blacklightoff();
void LCDwritecmddata(uint8_t data);
void LCDinit();
void Gpioinit();
void LCDcmdmode();
void LCDcharmode();
void LCDwritemode();
void LCDenablehigh();
void LCDenablelow();
void LCDwritebyte(uint8_t data);
void LCDwritecmddata(uint8_t data);
void LCDwritechardata(uint8_t data);
void LCDwritestring(char *str);
void LCDgotoxy(uint8_t row, uint8_t col);
void LCDwrtiestringxy(uint8_t row, uint8_t col, char *str);
void LCDcleardisplay();




#endif