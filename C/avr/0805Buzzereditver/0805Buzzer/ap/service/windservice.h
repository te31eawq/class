#ifndef WINDSERVICE_H_
#define WINDSERVICE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../driver/model/windbutton.h"
#include "../../driver/model/windauto.h"
#include "../../driver/model/modelwindnext.h"
#include "../../driver/model/windtimer.h"
#include "../../driver/model/timerstart.h"
#include "../presenter/presenter.h"

void stopwatchinit();
void stopwatchincmilisec();
void timerincmilisec();
void fndshow();
void stopreset();
void clear();
void timerdecmilisec();
void setInitialTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds);


#endif /* WINDSERVICE_H_ */