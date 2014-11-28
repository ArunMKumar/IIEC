/* Header file for the protocol 
This will contain the methods for 
Handling the I2C data that is received

The objective is to provide an abstract data type
that is used to realize the communication buffer
without the need for redundantly checking the logic.
the interface allows it to be used directly with a configurable
size for the buffer.

Do check the error codes when using these functions.
This File needs to be included to get the buffer related
error messages.

Features are Hardware specific, may be limited to Arduino only

Arun M Kumar		28 Nov 2011*/



#ifndef __CYCBUFFER_H
#define __CYCBUFFER_H

#include "Arduino.h"
#include "Project.h"


//====================================================================================
//							BUFFER STATUSES
//====================================================================================
// defining parameters
#define BUFFER_LEN		100U

// Defining the error codes
#define BUF_NOERROR		0x00
#define BUF_UNDERFLOW	0x01
#define BUF_OVERFLOW	0x02
//====================================================================================

// Macro to check endianess
#define IS_BIG_ENDIAN (!(*(uint8_t *)(&(uint16_t)0x01)))
#define HIGH_BYTE		0xFF00
#define LOW_BYTE		0x00FF


#define OVERFLOW (BUFFER_LEN == EleCount)
#define UNDERFLOW (0 == EleCount)

//====================================================================================
//							BUFFER CLASS
//====================================================================================

/*
 * This is just a data structure that shall be inherited by the class COMM
 * as a protected or a private member based on the settings provided.
 *
 */
class CYCBUFFER{
public:
	uint8_t HEAD;
	uint8_t TAIL;
	uint8_t EleCount;
	uint8_t Status;
	char BUF[BUFFER_LEN];


	CYCBUFFER();
	status_t dataAvailLen(void);
	status_t flushBuffer(void);
	status_t fillRandom(void);
	status_t readBuffer(uint8_t*);
	status_t writeBuffer(uint8_t);
	status_t readBufferWord(uint16_t*);
	status_t writeBufferWord(uint16_t);
	status_t readBufferFloat(uint32f_t *);	// To read a float value
	status_t writeBufferFloat(uint32f_t);	// To write a float value
	status_t readBufferln(uint8_t*,uint16_t);
	status_t writeBufferln(uint8_t*, uint16_t);
};
//====================================================================================

#endif /*CYCBUFFER_H*/
