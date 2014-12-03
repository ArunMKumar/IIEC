/*
Source file for the Comm.
Contains definitions for the comm

Arun M Kumar		25 NOV 2014
*/


#include "Comm.h"
#include "Command.h"
#include <Wire.h>

Comm::Comm(){
	/*
		Default constructor No Comm type defined
	*/
	status		= COMM_NOT_INIT;
	Device.deviceType = COMM_NOT_DEFINED;
	Device.baudRate = COMM_NO_BAUD;
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
		Wire.onReceive(commRxISR);// ISR for incoming communication
		status = COMM_INIT;
	}
}

device_t Comm::getDeviceType(){
	/* Returns the device type of the comm module*/
	return Device.deviceType;
}

status_t Comm::commSetDevice(deviceAttrib_t* data){
	
	Device = *data;

	// Debug:
	Serial.write("CommSetDevice Called\n");

	if (COMM_TYPE_I2C == Device.deviceType){
		Wire.begin(Device.address);	// Initialize the I2C bus on the node
		Wire.onReceive(commRxISR);// ISR for incoming communication
		status = COMM_INIT;
		// Debug:
		Serial.write("I2C initialized\n");
	}

	if (COMM_TYPE_BLE == Device.deviceType){
		// methods for BLE init
	}
	//debug
	Serial.write("CommSetDevice Exit\n");
	return status;
}

void Comm::commSetTxStatus(uint8_t status){
	/*
		Set the Tx status as TRUE or FALSE
	*/
	// Debug:
	Serial.write("Inside Comm set Tx satus\n");

	startTx = status;
}

status_t Comm::Transmit(id_t address){
	/*
	This method transmit the data on the bus which is 
	specified for this Comm instance to the
	destination address
	*/

	Serial.write("Inside Transmit\n");


	uint8_t data;

	if (FALSE == startTx){
		Serial.write("startTx Fail\n");
		return COMM_TX_FAIL;
	}

	if (COMM_NOT_INIT == status){
		Serial.write("Init FAil\n");
		return COMM_TX_FAIL;
	}

	/*
	####################	I2C		######################### 
	*/

	if (COMM_TYPE_I2C == Device.deviceType){
		/*
			If we need to send over I2C
		*/
		Wire.beginTransmission(address);		// Start I2C Comm

		while(outBuffer.dataAvailLen()){
			/*
				Transmit all the data in one go
			*/
			outBuffer.readBuffer(&data);
			Wire.write(data);
		}

		Wire.endTransmission();				 // End I2C Comm
	}

	/*
	####################	I2C		#########################
	*/
	Serial.write("Transmit End\n");
	commSetTxStatus(FALSE);
	return COMM_TX_SUCCESS;
}

void Comm::setCommStatus(status_t Status){
	/*
		Sets the status of the comm module
	*/
	this-> status = Status;
}

status_t Comm::getCommStatus(void){
	/*
		returns the status of the comm module
	*/
	return status;
}

status_t Comm::commWriteBuffer(uint8_t data){
	/*This module writes data to the comm instance's 
	out buffer one byte at a time*/

	// Debug:
	Serial.write("Enter Comm Write Buffer \n");

	return outBuffer.writeBuffer(data);
}

status_t Comm::commWriteBufferWord(uint32_t data){
	return outBuffer.writeBufferWord(data);
}

status_t Comm::commWriteBufferFloat(uint32f_t data){
	return outBuffer.writeBufferFloat(data);
}

status_t Comm::commWriteBufferString(uint8_t* data){
	/* 
		Method writes string contents till space is available
		if the space runs out at runtime, data written will not be revealed
		check bufferavail before writing anything
	*/
	while (BUF_NOERROR == outBuffer.getBufferStatus()){
		outBuffer.writeBuffer(*data);
		data += sizeof(uint8_t);
		if (('\n' == *data) && (1 < outBuffer.dataAvailLen())){
			outBuffer.writeBuffer(*data);
			return BUF_NOERROR;
		}
			
	}

	return outBuffer.getBufferStatus();
}

status_t Comm::commReadBuffer(uint8_t* loc){
	return inBuffer.readBuffer(loc);
}

status_t Comm::commReadBufferWord(uint32_t* loc){
	return inBuffer.readBufferWord(loc);
}

status_t Comm::commReadBufferFloat(uint32f_t* loc){
	return inBuffer.readBufferFloat(loc);
}

device_t Comm::commGetDeviceType(void){
	/*
	returns the device type for this comm instance
	*/
	return  Device.deviceType;
}

status_t Comm::commWriteInBuffer(uint8_t data){
	/* 
		Writes dat to the input buffer
	*/
	return inBuffer.writeBuffer(data);
}

uint8_t Comm::commInDataAvail(){
	return inBuffer.dataAvailLen();
}

uint8_t Comm::commOutDataAvail(){
	return outBuffer.dataAvailLen();
}
