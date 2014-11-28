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

Comm::Comm(device_t inDeviceType, baud_t inBaud, device_t outDeviceType, baud_t outBaud){
}
