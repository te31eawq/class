#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ap/ledmachine/ledmachine.h"

int main(void)
{
	ledmachineinit();
	while(1)
	{
		ledmachineexecute();
	}
}