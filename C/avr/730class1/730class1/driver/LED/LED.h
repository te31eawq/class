#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

#define LEDDDR DDRD
#define LEDPORT PORTD

void LEDinit();
void LEDallon();
void LEDwritedata(uint8_t data);



#endif /* LED_H_ */