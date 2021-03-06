/* Source file for handling the Protocol
Arun M Kumar			24 Nov 2014

*/


#include "Arduino.h"
#include "CycBuffer.h"

/*
	Function to check the endianess            
*/
status_t IS_BIG_ENDIAN(){
	uint16_t val = 0x01;
	return (!*(uint8_t *)(&val));
}

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
		Status = BUF_UNDERFLOW;
		return Status;	// Check for underflow
	}

	else {
		*loc = BUF[HEAD];
		EleCount -= sizeof(uint8_t);
		HEAD = (HEAD + sizeof(uint8_t)) % BUFFER_LEN;
	}

	Status = BUF_NOERROR;
	return Status;
}

status_t CYCBUFFER::writeBuffer(uint8_t ele){
	/*
	 * This method writes a byte of data on to the buffer.
	 * This return the state of the bus after the writing process.
	 * The element to be written is passed as the parameter.
	 */
	//debug:
	//Serial.write("Enter CYC Write Buffer \n");

	if (OVERFLOW){
		Status = BUF_OVERFLOW;
		return Status;		// check for overflow
	}

	else{
		BUF[TAIL] = ele;
		EleCount += sizeof(uint8_t);
		TAIL = (TAIL + sizeof(uint8_t)) % BUFFER_LEN;
	}
	
	Status = BUF_NOERROR;

	//debug:
	//Serial.write("Exit CYC Write Buffer \n");
	return Status;
}

status_t CYCBUFFER::readBufferWord(uint32_t *loc){
	/*
	 * This Method reads a 16bit value from the buffer
	 * and puts it into an appropriate location
	 */
	if(UNDERFLOW || (sizeof(uint16_t) > EleCount)){		// cannot read 2 bytes
		Status = BUF_UNDERFLOW;
		return Status;
	}

	else{
		/*
		 * *loc = *((uint16_t*)BUF + HEAD);
		 * This would not work as this is a cyclic buffer and if the
		 * word is placed at the last element before warping then this
		 * trick would fail.
		 */
		uint8_t temp = 0U;
		uint32_t result = 0U;

		if(IS_BIG_ENDIAN()){		
				/*
				* Here we convert the written data to float
				*/
				readBuffer(&temp);
				result |= ((uint32_t)temp << 24);	// first byte

				readBuffer(&temp);
				result |= ((uint32_t)temp << 16);	// second byte

				readBuffer(&temp);
				result |= ((uint32_t)temp << 8);	// third byte

				readBuffer(&temp);
				result |= (uint32_t)temp;	// fourth byte

				*loc = result;
		}

		else{
			/*
			* Here we convert the written data to float
			*/
			readBuffer(&temp);
			result |= ((uint32_t)temp);	// first byte

			readBuffer(&temp);
			result |= ((uint32_t)temp << 8);	// second byte

			readBuffer(&temp);
			result |= ((uint32_t)temp << 16);	// third byte

			readBuffer(&temp);
			result |= ((uint32_t)temp <<24);	// fourth byte

			*loc = result;
		}
	}

	Status = BUF_NOERROR;
	return Status;
}

status_t CYCBUFFER::writeBufferWord(uint32_t ele){
	/*
	 * This method writes a 16bit data onto the buffer.
	 * The data to be written is passed as a parameter.
	 */

	if (OVERFLOW || (sizeof(uint16_t) > (BUFFER_LEN - EleCount))){ // CAnnot write 2 bytes to buffer
		Status = BUF_OVERFLOW;
		return Status;
	}

	else{
		/*
		 * This would not work as this is a cyclic buffer and if the
		 * word is placed at the last element before warping then this
		 * trick would fail.
		 */
		if(IS_BIG_ENDIAN()){
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

	Status = BUF_NOERROR;
	return Status;
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
	float_long_Buffer bufRead;
	bufRead.val_long= 0U;	// Fill the union with zeros

	if (UNDERFLOW || (sizeof(uint32f_t) > EleCount)){
		Status = BUF_UNDERFLOW;
		return Status;
	}

	else{
		/*
		 * Here we convert the written data to float
		 */
		readBuffer(&temp);
		bufRead.val_long |= ((uint32_t)temp << 24);	// first byte

		readBuffer(&temp);
		bufRead.val_long |= ((uint32_t)temp << 16);	// second byte

		readBuffer(&temp);
		bufRead.val_long |= ((uint32_t)temp << 8);	// third byte

		readBuffer(&temp);
		bufRead.val_long |= (uint32_t)temp;	// fourth byte

		*loc = bufRead.val_float;
	}

	Status = BUF_NOERROR;
	return Status;
}

status_t CYCBUFFER::writeBufferFloat(uint32f_t ele){
	/*
	 * This method writes the float value in a
	 * byte oriented manner over the buffer
	 */

	float_long_Buffer bufWrite;
	bufWrite.val_long= 0U;	// Fill the union with zeros
	bufWrite.val_long = ele;

	if (OVERFLOW || (sizeof(uint32f_t) > (BUFFER_LEN - EleCount))){
		Status = BUF_OVERFLOW;
		return Status;
	}

	else{
		writeBuffer((uint8_t) (bufWrite.val_long >> 24));
		writeBuffer((uint8_t) (bufWrite.val_long >> 16));
		writeBuffer((uint8_t) (bufWrite.val_long >> 8));
		writeBuffer((uint8_t)  bufWrite.val_long);
	}

	Status = BUF_NOERROR;
	return Status;
}

status_t CYCBUFFER::readBufferln(uint8_t *loc, uint16_t len){
	
		// Read a particular length of data 
	while (len){
		if (BUF_NOERROR == this->readBuffer(loc)){
			len--;	// reduce the counter
		}
		else{
			Status = BUF_UNDERFLOW;
			return Status;
		}
	}
	Status = BUF_NOERROR;
	return Status;
}

status_t CYCBUFFER::writeBufferln(uint8_t *loc, uint16_t len){

	while (len){
		if (BUF_NOERROR == writeBuffer(*loc)){	// writeBuffer accepts values, not pointers
			len--;	// reduce the counter
			loc++;	// read from next location
		}
		else{		
			Status = BUF_UNDERFLOW;
			return Status;		
		}
	}

	Status = BUF_NOERROR;
	return Status;
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

status_t CYCBUFFER::getBufferStatus(void){
	return Status;
}
