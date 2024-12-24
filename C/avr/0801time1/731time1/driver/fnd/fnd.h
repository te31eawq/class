#ifndef FND_H_
#define FND_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../Periph/timer/TIM.h"

#define FND_DIGIT_DDR DDRE
#define FND_DATA_DDR DDRF
#define FND_DIGIT_1 4
#define FND_DIGIT_2 5
#define FND_DIGIT_3 6
#define FND_DIGIT_4 7

void FND_setFndData(uint16_t data);
void fndinit();
void FND_dispNum(uint16_t dir);
void FND_ISR_Process();


#endif /* FND_H_ */