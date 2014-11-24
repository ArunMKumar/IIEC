/* Header file for the operation of the master

Arun M Kumar			24 Nov 2014*/


#ifndef __MASTER_H
#define __MASTER_H

#include "Arduino.h"
#include "Protocol.h"
#include "Command.h"
#include "Slave.h"

class Master{
	/* Class to define the attributes and the methods
	associated with the Master class*/

	private:
		uint8_t MID;
		float PRIO;
		float DPRIO;
		uint8_t ASL;
		uint8_t DCL;
		//uint8_t slaveCount;	// No of slaves ::: HARD CODED for now
		Slave slaves[SLAVE_COUNT];
		uint8_t Status;
		PROTOCOL_BUF inBuf;	// Input buffer for the master --- from Slave
		PROTOCOL_BUF outBuf; // Output buffer for the master --- to Slave

public:
	Master();	// default constructor
	Master(uint8_t MID);
	uint8_t cmdSlave(unsigned char);
	uint8_t fillInBuff();
	uint8_t fillOutBuff();
	// All data in below functions obtained from the inBuf
	uint8_t getPrio();	// get the current Prio from the salves
	uint8_t getLoad();	// get the current load stats from slave
	uint8_t setLoad();	// set the load limit on slave
};

#endif