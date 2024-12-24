#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "driver/button/button.h"
#include "driver/led/led.h"
#include "ap/trafficsignal/ledmachine.h"
#include "gpio/periph/gpio.h"


uint32_t timeTick = 0;

uint8_t button3press()
{
   static uint8_t res = 1;
   uint8_t button = (PINA & (1<<2));
   
   if((button == 0) && (res == 1))
   {
      res = 0;
      return 1;
   }
   if((button != 0) && (res == 0))
   {
      res = 1;
      return 0;
   }
   return 0;
}


void TrafficSignal_CONTROL();

int main(void)
{
   
   while(1)
   {
      if(((TRAFFIC_BUTTON_PIN) & (1<<TRAFFIC_BUTTON_AUTO)) == 0)
      {
         trafficModeState = AUTO;
      }
      else if(((TRAFFIC_BUTTON_PIN) & (1<<TRAFFIC_BUTTON_MANUAL)) == 0)
      {
         trafficModeState = MANUAL;
      }
      
      
      switch(trafficModeState)
      {
         case AUTO :
         TrafficSignal_AUTO();
         break;
         case MANUAL :
         TrafficSignal_MANUAL();
         break;
         /*case CONTROL :
         TrafficSignal_CONTROL();
         break;*/
      }
      
      _delay_ms(1);
      timeTick++;
   }
}