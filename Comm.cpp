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

Comm::Comm(device_t DeviceType, baud_t Baud, id_t address){

	/* Parametrized constructor initializes 
	the device that is being used and the baud rate to follow
	Baud rate may not always make sense based on the device*/
	
	Device.deviceType = DeviceType;
	Device.baudRate = Baud;
	Device.address = address;

	if (COMM_TYPE_I2C == DeviceType){
		Wire.begin(Device.address);	// Initialize the I2C bus on the node
		status = COMM_INIT;
	}
}
