#ifndef LISTENER_H_
#define LISTENER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../driver/button/Button.h"
#include "../../driver/model/windbutton.h"
#include "../../driver/model/windauto.h"
#include "../../driver/model/windtimer.h"
#include "../../driver/model/timerstart.h"
void listen_init();
void listen_execute();


#endif /* LISTENER_H_ */