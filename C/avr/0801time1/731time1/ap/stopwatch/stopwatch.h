#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/fnd/fnd.h"
#include "../../driver/button/button.h"
#include "../../Periph/timer/TIM.h" 

void stopwatchincmilisec();
void stopwatchinit();
void stopWatchexecute();
void stopwatcheventcheck();
void stoprun();
#endif /* STOPWATCH_H_ */