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
	inDevice.deviceType = COMM_NOT_DEFINED;
	inDevice.baudRate = COMM_NO_BAUD;
	outDevice.deviceType = COMM_NOT_DEFINED;
	outDevice.baudRate = COMM_NO_BAUD;
}

Comm::Comm(device_t inDeviceType, baud_t inBaud, device_t outDeviceType, baud_t outBaud ){
	/*
		Function to initialize the Comm module
		both the In nad Out devices are set.
		PS: They have to be initialized here
	*/


	// %%%%%%%%%%%%%%%%%% IN DEVICE %%%%%%%%%%%%%%%%%%%%%%%
	if (COMM_TYPE_I2C == inDeviceType){
		inDevice.deviceType = inDeviceType;
		setCommStatus(COMM_INIT);
		// I2C Initialization code
		Wire.begin(SRC_I2C_ADDRESS);	// current devices I2C address

	}

	else if (COMM_TYPE_UART == inDeviceType){
		inDevice.deviceType = inDeviceType;
		setCommStatus(COMM_INIT);
		// Serial Initialization code
		Serial.begin(UART_BAUD_RATE);
	}

	else if (COMM_TYPE_BLE == inDeviceType){
		inDevice.deviceType = inDeviceType;
		setCommStatus(COMM_INIT);
		//BLE initioalization code

	}

	else if (COMM_TYPE_SPI == inDeviceType){
		inDevice.deviceType = inDeviceType;
		setCommStatus(COMM_INIT);
		//SPI Initialization code
	}

	else{
		// error handling
		inDevice.deviceType = COMM_NOT_DEFINED;
		setCommStatus(COMM_NOT_INIT);

	}

	// %%%%%%%%%%%%%%%%%% OUT DEVICE %%%%%%%%%%%%%%%%%%%%%%%
	if (COMM_TYPE_I2C == outDeviceType){
		inDevice.deviceType = outDeviceType;
		setCommStatus(COMM_INIT);
		// I2C Initialization code
		Wire.begin(SRC_I2C_ADDRESS);	// current devices I2C address

	}

	else if (COMM_TYPE_UART == outDeviceType){
		inDevice.deviceType = outDeviceType;
		setCommStatus(COMM_INIT);
		// Serial Initialization code
		Serial.begin(UART_BAUD_RATE);
	}

	else if (COMM_TYPE_BLE == outDeviceType){
		inDevice.deviceType = outDeviceType;
		setCommStatus(COMM_INIT);
		//BLE initioalization code

	}

	else if (COMM_TYPE_SPI == outDeviceType){
		inDevice.deviceType = outDeviceType;
		setCommStatus(COMM_INIT);
		//SPI Initialization code
	}

	else{
		// error handling
		inDevice.deviceType = COMM_NOT_DEFINED;
		setCommStatus(COMM_NOT_INIT);

	}
}

status_t Comm::Transmit(){
	/* This function the data available on the transmit buffer*/
	
		if (FRAME_LEN > outBuffer.dataAvailLen()){
			return  COMM_TX_FAIL;
		}

}
