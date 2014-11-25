/*
Communication handler for handling the communication
betwene nodes.
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

class Comm{
	private:
		status_t status;
		status_t strartTx;
		status_t doneRx;
		comm_t	commType;
		// Commneted just for testing purpose
		/*CYCBUFFER outBuffer;	
		CYCBUFFER inBuffer;*/

	public:
		CYCBUFFER outBuffer;
		CYCBUFFER inBuffer;
		Comm();	// default constructor to initialize the communication
		Comm(comm_t);
		void setTxDataAvail();
		void setCommType(comm_t);
		void setCommStatus(state_t);
		status_t Transmit(); 
};

#endif