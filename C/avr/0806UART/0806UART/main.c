#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include "Periph/UART0/UART0.h"
#include <stdio.h>

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL,_FDEV_SETUP_WRITE);



ISR(USART0_RX_vect)
{
	UART0_ISR_Process();
}



int main(void)
{
	//UART0 쓸거임, TxD와 RxD 터널해줘야함, 속도 2배 모드, Baud Rate 9600
	//8bit data bit, 1bit stop bit, Parity bit = none <- 이거 맞춰야함 -> Default 값
	DDRD = 0xff;
	UART0_init();
	
	stdout = &OUTPUT;
	
	sei();
	
	UART0_sendString("Seoul Tech LED Machine\n");
	
	while (1)
	{ 
		//UART0_sendString("TEST\n");
		if(UART0_GetRxFlag())
		{
			UART0_clearRxFlag();
			uint8_t *rxString = UART0_readRxBuff();
			
			if(!strcmp((char *)rxString, "LED1_TOGGLE\n"))
			{
				PORTD ^= (1<<5);
				if(PORTD & (1<<5))
				{
					printf("LED_1_ON\n");
				}
				else
				{
					printf("LED_1_OFF\n");
				}
			}
			else if(!strcmp((char *)rxString, "LED2_TOGGLE\n"))
			{
				PORTD ^= (1<<6);
				if(PORTD & (1<<6))
				{
					printf("LED_2_ON\n");
				}
				else
				{
					printf("LED_2_OFF\n");
				}
			}
			else if(!strcmp((char *)rxString, "LED3_TOGGLE\n"))
			{
				PORTD ^= (1<<7);
				if(PORTD & (1<<7))
				{
					printf("LED_3_ON\n");
				}
				else
				{
					printf("LED_3_OFF\n");
				}
			}
		}
	}
}

