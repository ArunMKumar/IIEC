/* The header file contains the definitions of the 
various commands and macros that may be used

Arun M Kumar				24 Nov 2014*/

#ifndef __COMMAND_H
#define __COMMAND_H


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

#define LOAD_1R  A0  //where to read
#define LOAD_2R  A1  //where to read
#define LOAD_3R  A2  //where to read
#define LOAD_4R  A3  //where to read
#define LOAD_5R  A4  //where to read
#define LOAD_6R  A5  //where to read

// Project dependent Load Write Pin s : IMP: Leave 0 and 1 for Serial
#define LOAD_1W  0x02  // Which pin to write to
#define LOAD_2W  0x03  // Which pin to write to
#define LOAD_3W  0x04  // Which pin to write to
#define LOAD_4W  0x05  // Which pin to write to
#define LOAD_5W  0x06  // Which pin to write to
#define LOAD_6W  0x07  // Which pin to write to

#define LOAD_DATA_LEN	0x10	// 16 bytes of data
#define LOAD_NO_ID		0xFF

//defining the commands
#define LOAD_OFF   0x00
#define LOAD_ON    0x01
#define LOAD_READ  0x02




//====================================================================================
//							SLAVE STATUS and CONSTATNTS
//====================================================================================



// Status of the Slaves
#define SLAVE_NOT_INIT		0x00	// If the slave is not connected
#define SLAVE_INIT			0x03	// If theslave is initialized

//Buffer
#define SLAVE_MASTER_BUFF_EMPTY		0x00



//====================================================================================
//							MASTER COMMANDS
//====================================================================================
#define NODE_NO_ID		0xFA
#define SLAVE_COUNT		0x03

#define MASTER_NOT_INIT	0x00
#define MASTER_INIT		0x03



#endif
