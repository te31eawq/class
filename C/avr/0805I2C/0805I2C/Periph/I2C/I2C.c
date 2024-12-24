#include "I2C.h"

void I2C_init()
{
	I2C_DDR &= ~((1<<I2C_SCL) | (1<<I2C_SDA));
	TWBR = 72;				// 100khz SCL
	// TWRC = 32;			// 200khz SCL
	// TWBR = 12;			// 400khz SCL
	TWSR = 0;
}

void I2C_start()
{
	//Send START condition
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
	// Wait for TWINT flag set. This indicates that the
	// START condition has been transmitted
	while (!(TWCR & (1<<TWINT)));
}

void I2C_txDevAddr(uint8_t SLA_W)
{
	//Load SLA_W into TWDR Register. Clear
	//TWINT bit in TWCR to start transmission of
	//address
	TWDR = SLA_W;
	TWCR = (1<<TWINT) | (1<<TWEN);
	//잘 보내졌는지 기다리는 소스
	while (!(TWCR & (1<<TWINT)));
}

void I2C_txData(uint8_t data)
{
	//Load DATA into TWDR Register. Clear TWINT
	//bit in TWCR to start transmission of data
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	// 잘 보내졌는지 체크
	while (!(TWCR & (1<<TWINT)));
}

void I2C_stop()
{
	// Transmit STOP condition
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
}

void I2C_txByte(uint8_t SLA_W, uint8_t data)
{
	// 1byte의 data 를 송수신 하는 상황, AVR(Master) -> Device(Slave)
	// 1. Start bit 송신(M->S)
	I2C_start();
	// 2. SLA + W 송신 (M->S)
	I2C_txDevAddr(SLA_W);
	// 3. ACK bit 송신 (S->M)
	// 4. 1btye Data 송신(M->S)
	I2C_txData(data);
	// 5. ACK bit 송신 (S->M)
	// 6. Stop bit 송신 (M->S)
	I2C_stop();
}