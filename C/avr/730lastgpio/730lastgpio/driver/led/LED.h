#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>


#define TRAFFIC_LED_DDR DDRF
#define TRAFFIC_LED_PORT PORTF
#define TRAFFIC_LED_PIN PINF


#define TRAFFIC_LIGHT_VRED 0
#define TRAFFIC_LIGHT_VYELLOW 1
#define TRAFFIC_LIGHT_VGREEN 2
#define TRAFFIC_LIGHT_HRED 3
#define TRAFFIC_LIGHT_HYELLOW 4
#define TRAFFIC_LIGHT_HGREEN 5

enum {AUTO, MANUAL, CONTROL};
enum {RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED};

uint8_t trafficState;

void TrafficSignal_REDGREEN();
void TrafficSignal_REDYELLOW();
void TrafficSignal_GREENRED();
void TrafficSignal_YELLOWRED();
void TrafficSignal_AUTO();
void TrafficSignal_MANUAL();

#endif /* LED_H_ */