#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "../../driver/fnd/fnd.h"
#include "../../driver/button/button.h"
#include "../../Periph/timer/TIM.h" 
#include "../../driver/LCD/LCD.h"


void stopwatchincmilisec();
void stopwatchinit();
void stopWatchexecute();
void stopwatcheventcheck();
void stoprun();
void hourminchange();
void clockmodify();
#endif /* STOPWATCH_H_ */