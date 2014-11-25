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

	}

	else if (COMM_TYPE_UART == commType){
		setCommType(commType);
		setCommStatus(COMM_INIT);
		// Serial Initialization code
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


void Comm::setCommStatus(status_t status){
	this->status = status;
}

void Comm::setCommType(comm_t commType){
	this->commType = commType;
}

