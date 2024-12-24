#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "../../Periph/GPIO/gpio.h"

//#define LEDDDR DDRD
//#define LEDPORT PORTD

void LEDinit(volatile uint8_t *DDR);
void LEDallon(volatile uint8_t *PORT);
void LEDalloff(volatile uint8_t *PORT);
void LEDwritedata(volatile uint8_t *PORT, uint8_t data);



#endif /* LED_H_ */