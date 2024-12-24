#ifndef LEDMACHINE_H_
#define LEDMACHINE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/Button/Button.h"
#include "../../driver/LED/LED.h"

void ledmachineinit();
void ledmachineexecute();
void LED1();
void LED2();
void LED3();
void LED4();

#endif 