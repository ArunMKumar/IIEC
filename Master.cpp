/* Source file for the Master

Arun M Kumar		24 Nov 2014*/

#include "ARduino.h"
#include "Master.h"


Master::Master(){
	/* Default constructor */
	this->MID = MASTER_NO_ID;
	this->Status = MASTER_NOT_INIT;
}

Master::Master(uint8_t MID){
	//Assign the Master ID to the master
	// This is a parameterized constructor
	this->MID = MID;
	this->Status = MASTER_INIT;
}

