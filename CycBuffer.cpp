/* Source file for handling the Protocol
Arun M Kumar			24 Nov 2014

*/


#include "Arduino.h"
#include "CycBuffer.h"


CYCBUFFER::CYCBUFFER(){
	/* here we initialize our buffer*
	 * Both the HEAD and TAIL are at the same position.
	 * The variable EleCount helps us in solving tricky
	 * overrun issues
	 */
	HEAD = 0x00;	// Head at the zeroth element
	TAIL = 0x00;	// tail at first element
	EleCount = 0x00;	// No element present
	Status = BUF_NOERROR;
}

status_t CYCBUFFER::readBuffer( uint8_t *loc){
	/*
	 * This method reads a byte of data and returns a
	 * state of the bus. The data is received on the address
	 * that is being passed as a parameter.
	 */
	if (UNDERFLOW){
		return BUF_UNDERFLOW;	// Check for underflow
	}

	else {
		*loc = BUF[HEAD];
		EleCount -= sizeof(uint8_t);
		HEAD = (HEAD + sizeof(uint8_t)) % BUFFER_LEN;
	}

	return BUF_NOERROR;
}

status_t CYCBUFFER::writeBuffer(uint8_t ele){
	/*
	 * This method writes a byte of data on to the buffer.
	 * This return the state of the bus after the writing process.
	 * The element to be written is passed as the parameter.
	 */
	if (OVERFLOW){
		return BUF_OVERFLOW;		// check for overflow
	}

	else{
		BUF[TAIL] = ele;
		EleCount += sizeof(uint8_t);
		TAIL = (TAIL + sizeof(uint8_t)) % BUFFER_LEN;
	}
	

	return BUF_NOERROR;
}

status_t CYCBUFFER::readBufferWord(uint16_t *loc){
	/*
	 * This Method reads a 16bit value from the buffer
	 * and puts it into an appropriate location
	 */
	if(UNDERFLOW){
		return BUF_UNDERFLOW;
	}

	else{
		/*
		 * *loc = *((uint16_t*)BUF + HEAD);
		 * This would not work as this is a cyclic buffer and if the
		 * word is placed at the last element before warping then this
		 * trick would fail.
		 */
		uint8_t highByte, lowByte = 0;
		if(IS_BIG_ENDIAN){
			// First byte would be high byte
			readBuffer(&highByte);
			readBuffer(&lowByte);
			*loc = (((uint16_t)highByte << 8) | (uint16_t)lowByte);
		}
		else{
			// read low byte first
			readBuffer(&lowByte);
			readBuffer(&highByte);
			*loc = (((uint16_t)lowByte << 8) | (uint16_t)highByte);
		}
	}

	return BUF_NOERROR;
}

status_t CYCBUFFER::writeBufferWord(uint16_t ele){
	/*
	 * This method writes a 16bit data onto the buffer.
	 * The data to be written is passed as a parameter.
	 */

	if (OVERFLOW){
		return BUF_OVERFLOW;
	}

	else{
		/*
		 * This would not work as this is a cyclic buffer and if the
		 * word is placed at the last element before warping then this
		 * trick would fail.
		 */
		uint8_t highByte, lowByte = 0;
		if(IS_BIG_ENDIAN){
			// First byte would be high byte
			writeBuffer(ele & HIGH_BYTE);
			writeBuffer(ele & LOW_BYTE);
		}

		else{
			// read low byte first
			writeBuffer(ele & LOW_BYTE);
			writeBuffer(ele & HIGH_BYTE);
		}
	}
	return BUF_NOERROR;
}

status_t CYCBUFFER::readBufferFloat(uint32f_t* loc){
	/*
	 * This function reads a float value from the buffer
	 * The data is stored in a bit order so we have to adapt it to
	 * some other form before we can change it.
	 * This method uses a union to convert between 4bytes and float,
	 * so please ensure that both the devices communicating have the
	 * same byte order and same endianness.
	 */

	uint8_t temp;
	float_long_Buffer bufRead = 0U;

	if(UNDERFLOW){
		return BUF_UNDERFLOW;
	}

	else{
		/*
		 * Here we convert the written data to float
		 */
		readBuffer(&temp);
		bufRead |= ((uint32_t)temp << 24);	// first byte

		readBuffer(&temp);
		bufRead |= ((uint32_t)temp << 16);	// second byte

		readBuffer(&temp);
		bufRead |= ((uint32_t)temp << 8);	// third byte

		readBuffer(&temp);
		bufRead |= (uint32_t)temp;	// fourth byte

		*loc = bufRead.val_float;
	}

	return BUF_NOERROR;
}

status_t CYCBUFFER::writeBufferFloat(uint32f_t ele){
	/*
	 * This method writes the float value in a
	 * byte oriented manner over the buffer
	 */

	float_long_Buffer bufWrite = 0U;
	bufWrite.val_long = ele;

	if(OVERFLOW){
		return BUF_OVERFLOW;
	}

	else{
		writeBuffer((uint8_t) (bufWrite.val_long >> 24));
		writeBuffer((uint8_t) (bufWrite.val_long >> 16));
		writeBuffer((uint8_t) (bufWrite.val_long >> 8));
		writeBuffer((uint8_t)  bufWrite.val_long);
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
	return BUF_NOERROR;
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
		in the range 0-199
	*/
	flushBuffer();
	while (BUFFER_LEN >= EleCount){
		if (BUF_OVERFLOW == writeBuffer(uint8_t(random(200)))){
			return BUF_OVERFLOW;
		}

		else
			continue;
	}

	return BUF_NOERROR;
}
