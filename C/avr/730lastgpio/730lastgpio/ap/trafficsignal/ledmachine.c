#include "ledmachine.h" 

uint8_t trafficState;
uint32_t timeTick = 0;

void TrafficSignal_REDGREEN()
{
	TRAFFIC_LED_PORT = (1<<TRAFFIC_LIGHT_VRED | 1<<TRAFFIC_LIGHT_HGREEN);
}
void TrafficSignal_REDYELLOW()
{
	TRAFFIC_LED_PORT = (1<<TRAFFIC_LIGHT_VRED | 1<<TRAFFIC_LIGHT_HYELLOW);
}
void TrafficSignal_GREENRED()
{
	TRAFFIC_LED_PORT = (1<<TRAFFIC_LIGHT_VGREEN | 1<<TRAFFIC_LIGHT_HRED);
}

void TrafficSignal_YELLOWRED()
{
	TRAFFIC_LED_PORT = (1<<TRAFFIC_LIGHT_VYELLOW | 1<<TRAFFIC_LIGHT_HRED);
}

void TrafficSignal_AUTO()
{
	static uint32_t prevTime = 0;
	
	switch(trafficState)
	{
		case RED_GREEN :
		TrafficSignal_REDGREEN();
		if(timeTick - prevTime >= 3000)
		{
			trafficState = RED_YELLOW;
			timeTick = 0;
		}
		
		break;
		case RED_YELLOW :
		TrafficSignal_REDYELLOW();
		if(timeTick - prevTime >= 1000)
		{
			trafficState = GREEN_RED;
			timeTick = 0;
		}
		break;
		case GREEN_RED :
		TrafficSignal_GREENRED();
		if(timeTick - prevTime >= 3000)
		{
			trafficState = YELLOW_RED;
			timeTick = 0;
		}
		break;
		case YELLOW_RED :
		TrafficSignal_YELLOWRED();
		if(timeTick - prevTime >= 1000)
		{
			trafficState = RED_GREEN;
			timeTick = 0;
		}
		break;
	}
}

void TrafficSignal_MANUAL()
{
	
	switch(trafficState)
	{
		case RED_GREEN :
		TrafficSignal_REDGREEN();
		if(button3press())
		{
			trafficState = RED_YELLOW;
		}
		break;
		case RED_YELLOW :
		TrafficSignal_REDYELLOW();
		if(button3press())
		{
			trafficState = GREEN_RED;
		}
		break;
		case GREEN_RED :
		TrafficSignal_GREENRED();
		if(button3press())
		{
			trafficState = YELLOW_RED;
		}
		break;
		case YELLOW_RED :
		TrafficSignal_YELLOWRED();
		if(button3press())
		{
			trafficState = RED_GREEN;
		}
		break;
	}
}

int main(void)
{
	TRAFFIC_LED_DDR = 0xff;
	TRAFFIC_BUTTON_PORT = 0xff;
	TRAFFIC_BUTTON_DDR &= ~(((1<<TRAFFIC_BUTTON_AUTO) | (1<<TRAFFIC_BUTTON_MANUAL) | (1<<TRAFFIC_BUTTON_CONTROL)) == 0); //DDRA = DDRA & 0bxxxxx000
	uint8_t trafficModeState = AUTO;
	
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
