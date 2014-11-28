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
//							device Attribute structures
//====================================================================================

typedef struct{
	device_t	deviceType;	
	baud_t		baudRate;
}deviceAttrib_t;

//====================================================================================
//							COMM CLASS
//====================================================================================

class Comm{
	private:
		status_t status;
		deviceAttrib_t inDevice;
		deviceAttrib_t outDevice;
		CYCBUFFER InBuf;	// Input Buffer for communication
		CYCBUFFER outBuf;	// Output Buffer for Communication

	public:
		status_t startTx;	// Public flag to start Transmission
		status_t doneRx;	// Public flag to notify Reception

		Comm();							// Default constructor
		Comm(comm_t); 					// Parameterized constructor
		void commCheckRxStatus(uint8_t*); // Checks the status of the Rx and Tx flags
		void commSetTxStatus(uint8_t);	// Set the Tx flag on or off
		void commRxISR(void);	// ISR for incoming communication
		status_t commTask(void);
		status_t startTx(void);

};

#endif
