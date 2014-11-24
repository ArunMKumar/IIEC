/* The header file contains the definitions of the 
various commands and macros that may be used

Arun M Kumar				24 Nov 2014*/

#ifndef __COMMAND_H
#define __COMMAND_H

//====================================================================================
//							SLAVE STATUS and CONSTATNTS
//====================================================================================
#define SLAVE_DATA_LEN	0x10	// 16 bytes of data

// definig the commands
#define SLAVE_OFF   0x00
#define SLAVE_ON    0x01
#define SLAVE_READ  0x02


#define SLAVE_NO_ID	0xFF

// Project dependent Load Read Pins
// currently supporting only UNO and clones

#define SLAVE_1R  A0  //where to read 
#define SLAVE_2R  A1  //where to read 
#define SLAVE_3R  A2  //where to read 
#define SLAVE_4R  A3  //where to read 
#define SLAVE_5R  A4  //where to read 
#define SLAVe_6R  A5  //where to read 

// Project dependent Load Write Pin s : IMP: Leave 0 and 1 for Serial
#define SLAVE_1W  0x02  // Which pin to write to
#define SLAVE_2W  0x03  // Which pin to write to
#define SLAVE_3W  0x04  // Which pin to write to
#define SLAVE_4W  0x05  // Which pin to write to
#define SLAVE_5W  0x06  // Which pin to write to
#define SLAVE_6W  0x07  // Which pin to write to

// Status of the Slaves
#define SLAVE_NOT_INIT		0x00	// If the slave is not connected
#define SLAVE_INIT			0x03	// If theslave is initialized

//Buffer
#define SLAVE_MASTER_BUFF_EMPTY		0x00



//====================================================================================
//							MASTER COMMANDS
//====================================================================================
#define MASTER_NO_ID	0xFA
#define SLAVE_COUNT		0x03

#define MASTER_NOT_INIT	0x00
#define MASTER_INIT		0x03



#endif