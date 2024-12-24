#ifndef LEDMACHINE_H_
#define LEDMACHINE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/Button/Button.h"
#include "../../driver/LED/LED.h"


#define TRAFFIC_BUTTON_PIN PINA
#define TRAFFIC_BUTTON_PORT PORTA
#define TRAFFIC_BUTTON_DDR DDRA
#define TRAFFIC_LED_DDR DDRF
#define TRAFFIC_LED_PORT PORTF
#define TRAFFIC_LED_PIN PINF
#define TRAFFIC_BUTTON_AUTO 0
#define TRAFFIC_BUTTON_MANUAL 1
#define TRAFFIC_BUTTON_CONTROL 2

#define TRAFFIC_LIGHT_VRED 0
#define TRAFFIC_LIGHT_VYELLOW 1
#define TRAFFIC_LIGHT_VGREEN 2

#define TRAFFIC_LIGHT_HRED 3
#define TRAFFIC_LIGHT_HYELLOW 4
#define TRAFFIC_LIGHT_HGREEN 5

enum {AUTO, MANUAL, CONTROL};
enum {RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED};

void ledmachineinit();
void ledmachineexecute();
void LED1();
void LED2();
void LED3();
void LED4();

#endif 