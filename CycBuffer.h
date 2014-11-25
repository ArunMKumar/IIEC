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
	uint8_t dataAvailLen();
	uint8_t readBuffer(uint8_t *loc);
	uint8_t writeBuffer(uint8_t ele);
	uint8_t readBufferln(uint8_t *loc,uint16_t len);
	uint8_t writeBufferln(uint8_t *loc, uint16_t len);
	
};


#endif
