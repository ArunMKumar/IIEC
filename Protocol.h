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


#endif