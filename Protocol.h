/* Header file for the protocol 
This will contain the methods for 
Handling the I2C data that is received*/

#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "Arduino.h"
#include "Command.h"
// defining parameters
#define PROTOCOL_BUF_LEN	100U


// Defining the error codes
#define BUF_NOERROR		0x00
#define BUF_UNDERFLOW	0x01
#define BUF_OVERFLOW	0x02

class PROTOCOL_BUF{
private:
	uint8_t HEAD;
	uint8_t TAIL;
	uint8_t EleCount;
	uint8_t Status;
	char BUF[PROTOCOL_BUF_LEN];

public:
	PROTOCOL_BUF();
	char readBuffer(unsigned char *loc);
	uint8_t writeBuffer(char ele);
	uint8_t readBufferln(unsigned char *loc,unsigned int len);
	uint8_t writeBufferln(unsigned char *loc, unsigned int len);
	
};


#endif