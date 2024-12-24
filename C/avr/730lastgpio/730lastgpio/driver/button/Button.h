#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#define TRAFFIC_BUTTON_PIN PINA
#define TRAFFIC_BUTTON_PORT PORTA
#define TRAFFIC_BUTTON_DDR DDRA
#define TRAFFIC_BUTTON_AUTO 0
#define TRAFFIC_BUTTON_MANUAL 1
#define TRAFFIC_BUTTON_CONTROL 2

enum {AUTO, MANUAL, CONTROL};
uint8_t ledData;

typedef struct _button
{
	volatile uint8_t *DDR;  // port 정보
	volatile uint8_t *PIN; // pin number 정보
	uint8_t pinNum;
	uint8_t prevState; // static prevState
}button_t;

void button_init(button_t *btn, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum);
uint8_t Button_GetState(button_t *btn);

#endif /* BUTTON_H_ */