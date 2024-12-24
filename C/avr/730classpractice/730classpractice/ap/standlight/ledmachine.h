
#ifndef LEDMACHINE_H_
#define LEDMACHINE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/button/Button.h"
#include "../../driver/led/LED.h"

#define LED_PORT PORTD
#define LED_DDR DDRD
#define BUTTON_PIN PINA
#define BUTTON_DDR DDRA
#define BUTTON_PORT PORTA
#define BUTTON_MODE 0
#define BUTTON_OFF 1

void StandLightinit();
void StandLightrun();
void StandLight_eventCheck();
void StandLight_execute();

#endif /* LEDMACHINE_H_ */