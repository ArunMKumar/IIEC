/*
Header file for the protocol that is defined.
This protocol shall be independent of the 
communication method used. atleast in this project

This is NOT a class, these are just methods that will
extract the info from the buffers inside

Node -> Comm -> Buffer and populates the attributes inside 
the Node and the Load class.

Arun M Kumar				26 Nov 2014
*/


#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "Arduino.h"
#include "Command.h"
#include "Project.h"
#include "Comm.h"
#include "Node.h"


#define FRAME_HEADER		0xFA
#define FRAME_SIZE			sizeof(childData)

/*
Frame shall be packed like 

Header	ID		PID		PRIO	DPRIO		ASL		DCL		DLOAD 
0xFA	1B		1B		4B		4B			2B		2B		2B

*/


status_t getVal(Node*);	// Read From In buffer and set the data.
	
status_t setVal(Node*);	// Write to Out Buffer from the set data.

#endif