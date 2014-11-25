/* Header file for the protocol 
This will contain the methods for 
Handling the I2C data that is received*/

#ifndef __CYCBUFFER_H
#define __CYCBUFFER_H

#include "Arduino.h"
#include "Command.h"
#include "Project.h"
// defining parameters
#define BUFFER_LEN	100U


// Defining the error codes
#define BUF_NOERROR		0x00
#define BUF_UNDERFLOW	0x01
#define BUF_OVERFLOW	0x02

class CYCBUFFER{
private:
	uint8_t HEAD;
	uint8_t TAIL;
	uint8_t EleCount;
	uint8_t Status;
	char BUF[BUFFER_LEN];

public:
	CYCBUFFER();
	char readBuffer(unsigned char *loc);
	uint8_t writeBuffer(char ele);
	uint8_t readBufferln(unsigned char *loc,unsigned int len);
	uint8_t writeBufferln(unsigned char *loc, unsigned int len);
	
};


#endif
