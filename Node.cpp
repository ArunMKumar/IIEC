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

status_t Node::commInitChild(deviceAttrib_t* data){
	
	return commChild.commSetDevice(data);
}

status_t Node::commInitParent(deviceAttrib_t* data){

	return commParent.commSetDevice(data);
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

status_t Node::TxParent(void){
	
	/*
		No issuess in the current project as both
		Parent and child nodes are in different comm instace
		so we can safely use one particular instance for this 
		task.
	*/
	return Status;
}

status_t Node::TxChild(void){

	/*
	No issuess in the current project as both
	Parent and child nodes are in different comm instace
	so we can safely use one particular instance for this
	task.
	*/

	return Status;
}

status_t Node::Task(void){
	/*
	This function shall be executed cyclically everytime. 
	This shall perform the periodic tasks that needs to be done for the
	node, eg. Calculating the Priorities and the Load allowance.

	We shall perform the algorith here, but do need to remember that
	we should use modular functions to allow for improvements later.
	*/
	Serial.write("Node Task Reached\n");
	Serial.write("ID:");
	Serial.print(ID);
	Serial.write("\nPID:");
	Serial.print(PID);
	


	

	return Status;	

}




