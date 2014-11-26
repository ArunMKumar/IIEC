/*
 * Node.cpp
 *	Source file for the Nodes,
 *	contaisn the definition of the methods for
 *	Node class
 *  Created on: Nov 25, 2014
 *      Author: kumaar6
 */

#include "Node.h"

Node::Node(){
	//Default constructor for the Node
	this->ID  = NODE_NO_ID;
	this->PID = NODE_NO_ID;
}

Node::Node(id_t ID, id_t PID){
	// Parameterized constructor for the Node
	this->ID = ID;
	this->PID = PID;
}

void Node::setNodePRIO(prio_t PRIO){
	/* This method calculates the cumulative
	 * priority of the node
	 */
	this->PRIO = PRIO;
}

void Node::setNodeLoads(load_t ASL, load_t DCL, load_t DLoad){
	/* This method calculates the various
	load parameters for the node*/
	this->ASL = ASL;
	this->DCL = DCL;
	this->DLoad = DLoad;
}




