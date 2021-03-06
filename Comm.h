/*
Communication handler for handling the communication
between nodes.
Should abstract the physical layer of communication and
should do comm based on communication.

Arun M Kumar		25 Nov 2011
*/

#ifndef __COMM_H
#define __COMM_H

#include "Arduino.h"
#include "Project.h"
#include "Command.h"
#include "CycBuffer.h"


//====================================================================================
//							COMM Macros
//====================================================================================

#define COMM_NOT_DEFINED	0x00	// No Communication defined
#define COMM_TYPE_I2C		0x01	// CommunicatioN over I2C
#define COMM_TYPE_UART		0x02	// Communication over UART
#define COMM_TYPE_BLE		0x03	// Communication over BLE
#define COMM_TYPE_SPI		0x04	// Communication over SPI

#define PARENT_COMM_TYPE	COMM_TYPE_I2C
#define CHILD_COMM_TYPE		COMM_TYPE_I2C


#define COMM_NOT_INIT		0x00
#define COMM_INIT			0x01
#define COMM_ERROR			0x02

#define COMM_DATA_AVAIL		0x01

#define COMM_TX_SUCCESS		0x00
#define COMM_TX_FAIL		0x01

#define COMM_NO_BAUD		0x00
#define COMM_UART9600		9600U


//====================================================================================
//							device Attribute structures
//====================================================================================

typedef struct{
	device_t	deviceType;	
	baud_t		baudRate;
	id_t		address;
}deviceAttrib_t;

//====================================================================================
//							COMM CLASS
//====================================================================================

class Comm{
	private:
		status_t status;
		deviceAttrib_t Device;	// type and Baud rate
		CYCBUFFER inBuffer;		// Input Buffer for communication
		CYCBUFFER outBuffer;	// Output Buffer for Communication

	public:
		status_t startTx;	// Public flag to start Transmission
		status_t doneRx;	// Public flag to notify Reception

		Comm();										// Default constructor
		Comm(device_t, baud_t, id_t); 				// Parameterized constructor
		status_t commSetDevice(deviceAttrib_t*);
		device_t getDeviceType(void);
		void commCheckRxStatus(uint8_t*);			// Checks the status of the Rx and Tx flags
		void commSetTxStatus(uint8_t);				// Set the Tx flag on or off

		//void commRxISR(int);						// ISR for incoming communication

		status_t commTask(void);					// Cyclic task to manage the buffers
		status_t Transmit(id_t);					// Transmit to  a particular node

		void setCommStatus(status_t);
		status_t getCommStatus(void);

		status_t commWriteBuffer(uint8_t);
		status_t commWriteBufferWord(uint32_t);
		status_t commWriteBufferFloat(uint32f_t);
	//	status_t commWriteBufferString(uint8_t*);

		status_t commWriteInBuffer(uint8_t);
		status_t commReadBuffer(uint8_t*);
		status_t commReadBufferWord(uint32_t*);
		status_t commReadBufferFloat(uint32f_t*);

		uint8_t commInDataAvail();
		uint8_t commOutDataAvail();
		
		device_t commGetDeviceType(void);
};


void commRxISR(int);

#endif
