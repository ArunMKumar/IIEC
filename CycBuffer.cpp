/* Source file for handling the Protocol
Arun M Kumar			24 Nov 2014*/


#include "Arduino.h"
#include "CycBuffer.h"


CYCBUFFER::CYCBUFFER(){
	/* here we initialize our buffer*/
	HEAD = 0x00;	// Head at the zeroth element
	TAIL = 0x00;	// tail at first element
	EleCount = 0x00;	// No element present
	Status = BUF_NOERROR;
}

status_t CYCBUFFER::readBuffer( uint8_t *loc){
	if (0 == EleCount){
		return BUF_UNDERFLOW;	// Check for underflow
	}

	else {
		*loc = BUF[HEAD];
		EleCount--;
		HEAD = (HEAD + 1) % BUFFER_LEN;
	}

	return BUF_NOERROR;
}

status_t CYCBUFFER::writeBuffer(uint8_t ele){
	if (BUFFER_LEN == EleCount){
		return BUF_OVERFLOW;		// check for overflow
	}

	else{
		BUF[TAIL] = ele;
		EleCount++;
		TAIL = (TAIL + 1) % BUFFER_LEN;
	}
	

	return BUF_NOERROR;
}

status_t CYCBUFFER::readBufferln(uint8_t *loc, uint16_t len){
	
		// Read a particular length of data 
	while (len){
		if (BUF_NOERROR == this->readBuffer(loc)){
			len--;	// reduce the counter
		}
		else{
			return BUF_UNDERFLOW;
		}
	}
	return BUF_NOERROR;
}

status_t CYCBUFFER::writeBufferln(uint8_t *loc, uint16_t len){

	while (len){
		if (BUF_NOERROR == writeBuffer(*loc)){	// writeBuffer accepts values, not pointers
			len--;	// reduce the counter
			loc++;	// read from next location
		}
		else{			
			return BUF_OVERFLOW;		
		}
	}	
}

status_t CYCBUFFER::dataAvailLen(void){
	return EleCount;
}

status_t CYCBUFFER::flushBuffer(void){
	/*
	Resets the buffer to a state when it was just formed
	IMP: Does not remove garbage data
	*/
	HEAD = 0x00;
	TAIL = 0x01;
	EleCount = 0x00;
	Status = BUF_NOERROR;

	return Status;
}

status_t CYCBUFFER::fillRandom(void){
	/*
		Fills the buffer with random data
		in the range 0-299
	*/
	flushBuffer();
	while (BUFFER_LEN > EleCount){
		if (BUF_OVERFLOW == writeBuffer(uint8_t(random(300)))){
			return BUF_OVERFLOW;
		}

		else
			continue;
	}
}