/* Header file for the protocol 
This will contain the methods for 
Handling the I2C data that is received*/

#ifndef __CYCBUFFER_H
#define __CYCBUFFER_H

#include "Arduino.h"
#include "Command.h"
#include "Project.h"

class CYCBUFFER{
private:
	uint8_t HEAD;
	uint8_t TAIL;
	uint8_t EleCount;
	uint8_t Status;
	char BUF[BUFFER_LEN];

public:
	CYCBUFFER();
	status_t dataAvailLen();
	status_t flushBuffer(void);
	status_t fillRandom(void);
	status_t readBuffer(uint8_t *loc);
	status_t writeBuffer(uint8_t ele);
	status_t readBufferln(uint8_t *loc,uint16_t len);
	status_t writeBufferln(uint8_t *loc, uint16_t len);
	
};


#endif /*CYCBUFFER_H*/
