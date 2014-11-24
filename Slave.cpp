/* Source file for the slave class 
Arun M Kumar	24 November 2014*/


#include "Arduino.h"
#include "Slave.h"

Slave::Slave(){
	/* Default constructor of the class Slave*/
	_rpin = 0x00;
	_wpin = 0x00;

	//pinMode(XXXX) // Do not assign any pin modes now
	// we want the data to be avialble before we can proceed
	ID = SLAVE_NO_ID;
	Status = SLAVE_NOT_INIT;
}

Slave::Slave(uint8_t rpin, uint8_t wpin, uint8_t ID){
	/* Parameterized constructor for the
	slave class*/
	/* we assign the read and the write pin here*/
	_rpin = rpin;
	_wpin = wpin; 

	/* Setting the modes of the pins*/
	pinMode(_wpin, OUTPUT);
	// No need to set pinMode for read as it is an analog input
	this->ID = ID;
}

char Slave::read(){
	/* This reads the current value of the load*/
	DCL = analogRead(_rpin);
	return DCL;
}

void Slave::write(uint8_t Logic){
	/* This writes the current value of the load*/
	digitalWrite(_wpin, Logic);
	return;
}

int Slave::readSet(dataset *loc){
	/* This function reads the current parameter of the Slave device
	and put sthem in a buffer to be read by the user*/
	loc->ID = ID;
	loc->MID = MID;
	loc->PRIO = PRIO;		
	loc->DPRIO = DPRIO;		
	loc->ASL = ASL;			
	loc->DCL = DCL;			
	loc->Status = Status;		
}