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

//====================================================================================
//							LOAD COMMANDS
//====================================================================================

#define LOAD_NOT_INIT 	0x00
#define LOAD_INIT		0x010
#define LOAD_DATA_READY	0x02

#define STATE_NOT_INIT	0x00
#define STATE_ON		0x01
#define STATE_OFF		0x03

#define TIME_NOT_INIT	0x00
#define ID_NOT_INIT		0x00

#define PRIO_MIN		1.0f
#define PRIO_MAX		6.0f
#define PRIO_NOT_INIT	(PRIO_MAX)	// currently the least priority

#define PIN_LOW				0x00
#define PIN_HIGH			0x01
#define PIN_INPUT			0x00
#define PIN_OUTPUT			0x01
#define PIN_INPUT_PULLUP 	0x02

// Project dependent Load Read Pins
// currently supporting only UNO and clones

#define LOAD_0R  A0  //where to read
#define LOAD_1R  A1  //where to read
#define LOAD_2R  A2  //where to read
#define LOAD_3R  A3  //where to read
#define LOAD_4R  A4  //where to read
#define LOAD_5R  A5  //where to read

// Project dependent Load Write Pin s : IMP: Leave 0 and 1 for Serial
#define LOAD_0W  0x02  // Which pin to write to
#define LOAD_1W  0x03  // Which pin to write to
#define LOAD_2W  0x04  // Which pin to write to
#define LOAD_3W  0x05  // Which pin to write to
#define LOAD_4W  0x06  // Which pin to write to
#define LOAD_5W  0x07  // Which pin to write to

// Priority for the LOAD, currently taking range 1-6
#define LOAD_PRIO0	0U
#define LOAD_PRIO1	1U
#define LOAD_PRIO2	2U
#define LOAD_PRIO3	3U
#define LOAD_PRIO4	4U
#define LOAD_PRIO5	5U
#define LOAD_PRIO6	6U

#define LOAD_MAX_PRIO		(LOAD_PRIO0)
#define LOAD_MIN_PRIO		(LOAD_PRIO6)
#define LOAD_PRIO_DEFAULT	(LOAD_PRIO3)

// Ids for the Loads
#define LOAD_ID0	0U
#define LOAD_ID1	1U
#define LOAD_ID2	2U
#define LOAD_ID3	3U
#define LOAD_ID4	4U
#define LOAD_ID5	5U
#define LOAD_ID6	6U

// Load Limits
#define LOAD_CLASS1		60
#define LAOD_CLASS2		50
#define LOAD_CLASS3		40
#define LOAD_CLASS4		30
#define LOAD_CLASS5		20
#define LOAD_CLASS6		10

#define LOAD_CLASS_DEFAULT	(LOAD_CLASS3)

#define LOAD_DATA_LEN	0x10	// 16 bytes of data
#define LOAD_NO_ID		0xFF

//defining the commands
#define LOAD_OFF   0x00
#define LOAD_ON    0x01
#define LOAD_READ  0x02


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
		uint16_t readLoad();	// analog Read return 16 bit value, 10 bit resolution

		void writeLoad(uint8_t Logic);
		void getLoadState(LoadState_t*);
		prio_t getLoadPrio(void);
		prio_t getLoadDprio(void);

		void getLoad(load_t*, load_t*, load_t*);
		status_t Task(void); // Contains the cyclic task that need to be called periodically
};


#endif /* LOAD_H_ */
