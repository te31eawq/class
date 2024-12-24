#ifndef WIND_H_
#define WIND_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../driver/buzzer/buzzer.h"
#include "../../driver/button/Button.h"
#include "../../driver/model/windbutton.h"
#include "../../driver/model/windauto.h"
#include "../service/windservice.h"
#include "../listener/listener.h"
#include "../../driver/FND/fnd.h"
#include "../../driver/LCD/LCD.h"
#include "../presenter/presenter.h"

void wind_init();
void wind_execute();

#endif /* WIND_H_ */