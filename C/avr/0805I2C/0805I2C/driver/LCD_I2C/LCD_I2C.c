#include "LCD_I2C.h"

uint8_t lcdControlData; // xxxx xxxx

void LCD_blacklighton()
{
	lcdControlData |= (1<<LCD_BLACKLIGHT);
}

void LCD_blacklightoff()
{
	lcdControlData &= ~(1<<LCD_BLACKLIGHT);
}

void LCDinit()
{
	I2C_init();
	lcdControlData = 0;
	
	_delay_ms(15);
	LCDcmdmode();
	LCDwritemode();
	LCD_writeNibble(0x30); // functionset
	_delay_ms(5);
	LCD_writeNibble(0x30); // functionset
	_delay_ms(1);
	LCD_writeNibble(0x30); // functionset
	LCD_writeNibble(0x20); // another functionset
	LCDwritecmddata(LCD_4bit_FUNCTIONSET);
	LCDwritecmddata(displayoff);// display off
	LCDwritecmddata(displayclear);// display clear
	LCDwritecmddata(entrymodeset);// (0b 000001 I/D S )entry mode set
	LCDwritecmddata(displayon);
	
	LCD_blacklighton();
}

void LCD_sendToI2C(uint8_t sla_w, uint8_t data)
{
	I2C_txByte(sla_w, data);
}

//MCU -> LCD로 명령어를 보낼 경우 (write mode)

void LCDcmdmode()
{
	//RS pin : bit 0 set
	lcdControlData &= ~(1<<LCD_RS);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
}

void LCDcharmode()
{
	// RS pin : bit 0 set
	lcdControlData |= (1<<LCD_RS);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
}
void LCDwritemode()
{
	// LCDcontrolport &= ~(1<<6);
	lcdControlData &= ~(1<<LCD_RW);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
}
void LCDenablehigh()
{
	// e pin : 1세팅
	lcdControlData |= (1<<LCD_E);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
	_delay_ms(1);
}
void LCDenablelow()
{
	// e pin : 0세팅
	lcdControlData &= ~(1<<LCD_E);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
	_delay_ms(1);
}

void LCD_writeNibble(uint8_t data)
{
	LCDenablehigh();
	lcdControlData = (lcdControlData & 0x0f) | (data & 0xf0);
	LCD_sendToI2C(LCD_SLA_W, lcdControlData);
	LCDenablelow();
}


void LCDwritebyte(uint8_t data)
{
	// 8 bit를 PORTC로 data 값을 내보내기
	LCD_writeNibble(data);
	data <<= 4;
	LCD_writeNibble(data);
}

void LCDwritecmddata(uint8_t data)
{
	//LCD 명령어 전달
	LCDcmdmode();
	LCDwritemode();
	LCDenablehigh();
	LCDwritebyte(data);
	LCDenablelow();
	
}
void LCDwritechardata(uint8_t data)
{
	//LCD character 쓰기 전달
	LCDcharmode();
	LCDwritemode();
	LCDenablehigh();
	LCDwritebyte(data);
	LCDenablelow();
}
void LCDwritestring(char *str)
{
	for(int i = 0 ; str[i]; i++)
	{
		LCDwritechardata(str[i]);
	}
}
void LCDgotoxy(uint8_t row, uint8_t col)
{
	col%= 16; row %=2;
	uint8_t lcdregisterAddress = (0x40 * row ) + col;
	uint8_t command = 0x80 + lcdregisterAddress;
	LCDwritecmddata(command);
}
void LCDwrtiestringxy(uint8_t row, uint8_t col, char *str)
{
	LCDgotoxy(row,col);
	LCDwritestring(str);
}
void LCDcleardisplay()
{
	LCDwritecmddata(displayclear);
}