#ifndef FND_H_
#define FND_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void fndinit();
void fndsystem(uint16_t dir);
void fndtime();
void FND_setFndData(uint16_t data);
#endif 