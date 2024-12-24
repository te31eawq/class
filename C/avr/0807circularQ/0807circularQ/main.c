#define F_CPU
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#define QUEUE_SIZE 4
#define QUEUE_LENGTH 80
volatile int rear=0; // interrupt에서 queue에 data를 저장하는 위치값
volatile int front=0; // pc_command_processing에서 가져가는 위치값
volatile unsigned char rx_buff[QUEUE_SIZE][QUEUE_LENGTH]

ISR(USART0_RX_vect)
{
	volatile static int i=0;
	volatile uint8_t data;
	
	data = UDR0;
	
	if(data =='\r' || data == '\n')
	{
		if((rear+1)%QUEUE_SIZE == front % QUEUE_SIZE)
		{
			return;
		}
		rx_buff[rear][i] = '\0';
		i=0;
		rear++;
		rear %= QUEUE_SIZE;
	}
	else
	{
		if((rear+1) % QUEUE_SIZE == front % QUEUE_SIZE)
		{
			return;
		}
		else
		{
			rx_buff[rear][i++] = data;
		}
	}
}
int is_empty()
{
	if(rear == front)
	{
		return 1;
	}
	return 0;
}

int is_full()
{
	if((rear+1)%QUEUE_SIZE == front)
	{
		return 1;
	}
	return 0;
}

void en_queue(uint8_t data)
{
	if(is_full())
	{
		printf("큐가 가득 찼습니다\n");
	}
	else
	{
		rear = (rear + 1) % QUEUE_SIZE;
		rx_buff[rear]=data;
	}
}

int de_queue()
{
	if(is_empty())
	{
		return -1;
	}
	else
	{
		rear = (rear+1) % QUEUE_SIZE;
		rx_buff[rear]=data;
	}
}

int de_queue()
{
	if(is_empty())
	{
		return -1;
	}
	else
	{
		front = (front + 1) % QUEUE_SIZE;
		return rx_buff[front];
	}
}

void pc_command_processing(void)
{
	if(front != rear)
	{
		printf("%s\n", rx_buff[front]);
		if(strncmp(rx_buff[front], "led_all_on", strlen("led_all_on"))== 0)
		{
			command_type = PC_COMMAND;
			state = LED_ALL_ON;
		}
		else if(strncmp(rx_buff[front], "led_all_off", strlen("led_all_off")) == 0)
		{
			command_type=PC_COMMAND;
			state = LED_ALL_OFF;
		}
		
		front++;
		front %= QUEUE_SIZE;
	}
	if(command_type==PC_COMMAND)
	fp[state]();
}


int main(void)
{
	
    while (1) 
    {
		pc_command_processing();
		bt_command_processing();
		ultrasonic_distance_check();
    }
}

