/*
Source file for the Comm.
Contains definitions for the comm

Arun M Kumar		25 NOV 2014
*/


#include "Comm.h"
#include "Wire.h"
#include "Command.h"

Comm::Comm(){
	/*
		Default constructor No Comm type defined
	*/
	status		= COMM_NOT_INIT;
	commType	= COMM_NOT_DEFINED;

}

Comm::Comm(comm_t commType){
	/*
		Function to initialize the Comm module
	*/
	if (COMM_TYPE_I2C == commType){
		setCommType(commType);
		setCommStatus(COMM_INIT);
		// I2C Initialization code
		Wire.begin(SRC_I2C_ADDRESS);

	}

	else if (COMM_TYPE_UART == commType){
		setCommType(commType);
		setCommStatus(COMM_INIT);
		// Serial Initialization code
		Serial.begin(UART_BAUD_RATE);
	}

	else if (COMM_TYPE_BLE == commType){
		setCommType(commType);
		setCommStatus(COMM_INIT);
		//BLE initioalization code

	}

	else if (COMM_TYPE_SPI == commType){
		setCommType(commType);
		setCommStatus(COMM_INIT);
		//SPI Initialization code
	}

	else{
		// error handling
		setCommType(COMM_NOT_DEFINED);
		setCommStatus(COMM_NOT_INIT);

	}
}

status_t Comm::Transmit(){
	/* This function the data available on the transmit buffer*/
	
		if (FRAME_LEN > outBuffer.dataAvailLen()){
			return  COMM_TX_FAIL;
		}
		
		if (COMM_TYPE_I2C == commType){

		uint8_t loc = 0x00;
		Wire.beginTransmission(DEST_I2C_ADDRESS);	// Start Tx
		
		for (uint8_t count = 0; count < FRAME_LEN; count++){
				outBuffer.readBuffer(&loc);	// read the data in a temp location
				Wire.write(loc);
		}

		Wire.endTransmission(); // End Tx
		return COMM_TX_SUCCESS;
		}


		if (COMM_TYPE_UART == commType){

			uint8_t loc = 0x00;
			
			for (uint8_t count = 0; count < FRAME_LEN; count++){
				outBuffer.readBuffer(&loc);	// read the data in a temp location
			}
			return COMM_TX_SUCCESS;
		}




}

void Comm::setCommStatus(status_t status){
	this->status = status;
}

void Comm::setCommType(comm_t commType){
	this->commType = commType;
}

void Comm::setTxDataAvail(void){
	strartTx = COMM_DATA_AVAIL;
}

status_t Comm::flushInBuffer(void){
	/*
	Just call the individual flush buffer utility.
	Permissions and integrity check for later release
	*/
	return inBuffer.flushBuffer();
}

status_t Comm::flushOutBuffer(void){
	/*
	Just call the individual flush buffer utility.
	Permissions and integrity check for later release
	*/
	return outBuffer.flushBuffer();
}

status_t Comm::fillRandomIn(void){
	/* 
		Fills In buffer with random data 
		in the range 0-299
	*/
	return inBuffer.fillRandom();
}

status_t Comm::fillRandomOut(void){
	/*
	Fills Out buffer with random data
	in the range 0-299
	*/
	return outBuffer.fillRandom();
}

status_t Comm::readInBuffer(uint8_t *loc){
	/* 
		reads one byte from the In buffer	
	*/
	if (BUF_NOERROR == inBuffer.readBuffer(loc)){
		return BUF_NOERROR;
	}

	else
		return BUF_UNDERFLOW;
}

status_t Comm::readInBufferln(uint8_t* loc, uint16_t len){
	/* 
		Reads a length of data at a time
	*/
	if (BUF_NOERROR == inBuffer.readBufferln(loc, len)){
		return BUF_NOERROR;
	}

	else
		return BUF_UNDERFLOW;
}

status_t Comm::writeOutBuffer(uint8_t ele){
	/*
		Writes a single element to the out buffer
	*/
	if (BUF_NOERROR == outBuffer.writeBuffer(ele)){
		return BUF_NOERROR;
	}

	else
		return BUF_OVERFLOW;
}

status_t Comm::writeOutBufferln(uint8_t *loc, uint16_t len){
	/*
		Write a length of character to the buffer
	*/
	if (BUF_NOERROR == outBuffer.writeBufferln(loc, len)){
		return BUF_NOERROR;
	}

	else
		return BUF_OVERFLOW;
}