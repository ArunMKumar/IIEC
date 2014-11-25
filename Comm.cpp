/*
Source file for the Comm.
Contains definitions for the comm

Arun M Kumar		25 NOV 2014
*/


#include "Comm.h"
#include "Wire.h"

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

void Comm::setTxDataAvail(){
	strartTx = COMM_DATA_AVAIL;
}
