#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BUZZER_ICR ICR3
#define BUZZER_OCR OCR3A
#define BUZZER2_ICR ICR1
#define BUZZER2_OCR OCR1A

void Buzzer2_soundOn();
void Buzzer2_soundOff();
void Buzzer2_init();
void Buzzer2_makehz(uint16_t hertz);
void Buzzer2_buttonOn();



#endif /* BUZZER_H_ */