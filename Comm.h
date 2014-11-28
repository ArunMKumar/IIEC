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

}deviceAttrib;
//====================================================================================
//							COMM CLASS
//====================================================================================

class Comm :protected CYCBUFFER{
	private:
		status_t status;
		comm_t	commType;

	public:
		status_t startTx;	// Public flag to start Transmission
		status_t doneRx;	// Public flag to notify Reception

		Comm();							// Default constructor
		Comm(comm_t); 					// Parameterized constructor
		void commCheckRxStatus(uint8_t*); // Checks the status of the Rx and Tx flags
		void commSetTxStatus(uint8_t, deviceAttrib*);	// Set the Tx flag on or off
		status_t startTx(void);

};

#endif
