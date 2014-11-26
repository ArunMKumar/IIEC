/*
 * Load.h
 *
 *  Created on: Nov 25, 2014
 *      Author: kumaar6
 */

#ifndef __LOAD_H_
#define __LOAD_H_

#include "Arduino.h"
#include "Project.h"
#include "CycBuffer.h"
#include "Command.h"

// Structure to read the data about the load
typedef struct{
	id_t ID;
	state_t State;	//current state of the load
	time_t onTime;	// time since load is on
	time_t offTime;	// time since load is off
	prio_t PRIO;	// assigned priority
	prio_t DPRIO;	// Dynamic priority
	load_t ASLoad;	// actual sanctioned load
	load_t DCLoad;	// Currently consuming load
	load_t DLoad;	// demanded load
}LoadState_t;



class Load{

	/* Load type class, contains the methods and attributes
	 * associated with the load type
	 */
	private:
		id_t ID;
		pin_t _rpin;
		pin_t _wpin;
		state_t State;
		time_t onTime;
		time_t offTime;
		prio_t PRIO;
		prio_t DPRIO;
		load_t ASLoad;
		load_t DCLoad;
		load_t DLoad;

	public:
		Load();
		Load(pin_t, pin_t, id_t, prio_t, load_t);
		uint8_t readLoad();
		void writeLoad(uint8_t Logic);
		void getLoadState(LoadState_t*);
		status_t Task(void); // Contains the cyclic task that need to be called periodically
};


#endif /* LOAD_H_ */
