/*
 * Load.cpp
 *	 Source file for the Load.h file
 *  Created on: Nov 25, 2014
 *      Author: kumaar6
 */

#include "Load.h"


Load::Load(){
	//default constructor for the load class
	ID 		= ID_NOT_INIT;
	State 	= STATE_NOT_INIT;	//current state of the load
	onTime 	= TIME_NOT_INIT;	// time since load is on
	offTime	= TIME_NOT_INIT;	// time since load is off
	PRIO	= PRIO_NOT_INIT;	// assigned priority
	DPRIO	= PRIO_NOT_INIT;	// Dynamic priority
	ASLoad	= LOAD_NOT_INIT;	// actual sanctioned load
	DCLoad	= LOAD_NOT_INIT;	// Currently consuming load
	DLoad	= LOAD_NOT_INIT;	// demanded load
}


Load::Load(pin_t rpin, pin_t wpin, id_t ID, prio_t prio, load_t load){
	// Parameterized constructor for the load type class
	_rpin = rpin;
	_wpin = wpin;
	pinMode(_wpin, PIN_OUTPUT);

	this->ID = ID;
	this->PRIO = prio;
	DLoad = load;
}


uint8_t Load::readLoad(){
	// just return the analog values
	return analogRead(_rpin);
}

void Load::writeLoad(uint8_t Logic){
	// write the requested value to the pin
	digitalWrite(_wpin, Logic);
}

void Load::getLoadState(LoadState_t *Buf){
	Buf-> ID 		= this-> ID;
	Buf-> State		= this-> State;	//current state of the load
	Buf-> onTime	= this-> onTime;	// time since load is on
	Buf-> offTime	= this-> offTime;	// time since load is off
	Buf-> PRIO		= this-> PRIO;	// assigned priority
	Buf-> DPRIO		= this-> DPRIO;	// Dynamic priority
	Buf-> ASLoad	= this-> ASLoad;	// actual sanctioned load
	Buf-> DCLoad	= this-> DCLoad;	// Currently consuming load
	Buf-> DLoad		= this-> DLoad;	// demanded load
}


void Load::LoadTask(){
	return;
}




