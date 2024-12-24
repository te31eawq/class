#ifndef UPCOUNTER_H_
#define UPCOUNTER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/button/Button.h"
#include "../../driver/fnd/fnd.h"
#include "../../Periph/timer/TIM.h"

void upcounterinit();
void upcounterexecute();

#endif 