/*
Source file for the Project
Contains the task structure and the tasks that need to be completed.

Do all that you would do in the sketch here, then just use this call
in the sketch.

All tasks are defined here and the superset of these are exported as 
setup and loop for the arduio sketch to load.
The objects and everything else shall be created here.

Arun M Kumar						30 Nov 2014
*/


#include "Project.h"
#include "Load.h"
#include "Node.h"
#include "Comm.h"



uint8_t Command_Buffer[CMD_FRAME_LEN];
status_t COMM_ESTABLISHED = FALSE;
status_t COMM_ESTABLISHED_CHILD = FALSE;
status_t COMM_ESTABLISHED_PARENT = FALSE;
status_t INIT_DONE = FALSE;
status_t CHILD_DATA_RECEIVED = FALSE;
status_t ASL_RECEIVED = FALSE;

/*
First we need to initialize the loads.
For the time being we use 4 loads and work with them

Initializing the Loads instances here
*/
Load Load1(LOAD_0R, LOAD_0W, LOAD_ID0, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);		// A0,A1 etc. will work with Arduino IDE, ignore error here
Load Load2(LOAD_1R, LOAD_1W, LOAD_ID1, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load3(LOAD_2R, LOAD_2W, LOAD_ID2, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load4(LOAD_3R, LOAD_3W, LOAD_ID3, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);

LoadState_t Loads[NUM_LOADS];

/*
child data structure to store the data
*/
childData_t childs[NUM_CHILDS]; // Change as per project, declared in global scope, should be Zeros everywhere
/*
This array contains the I2C addresses of the childs that we need to ocmmunicate with
*/
addr_t childAddr[NUM_CHILDS] = { CHILD1_I2C_ADDR, CHILD2_I2C_ADDR };
/*
Creating data structure for parent and child comm
*/
deviceAttrib_t parentDevice = { PARENT_COMM_TYPE, 000, PARENT_ADDRESS };
deviceAttrib_t childDevice = { CHILD_COMM_TYPE, 0x00, SRC_ADDRESS };
/*
Creating Node instance here
*/
Node MyNode(NODE_ID, NODE_PID); // all other features shall be initialized in the setup module.


//====================================================================================
//							Load Data
//====================================================================================

void fillLoadState(void){
	/*
		This fills the data from each load into a structure that can be used well by
		the node task, instead of calling load class member functions again and again
		this keeps the flow clean as it acts as a central holding are for data about
		all nodes and loads.
		Call this cyclically
	*/
	for (uint8_t i = 0; i < NUM_LOADS; i++){
		Load1.getLoadState(&Loads[i]);
	}
	
}

status_t Node::establishCommChild(){
	/*
	 * This module establishes communication with the child
	 * nodes
	 * IMP: readchild is a cyclic task and should not be used now
	 */
	// Debug:
	Serial.write("Inside establish Comm Child\n");
	uint8_t Command[1] = { CMD_SEND_ACK };
	for(uint8_t i=0; i < NUM_CHILDS; i++){
			MyNode.ProtocolWriteChild(Command, 1, childAddr[i]);
		}

	// Debug:
	Serial.write("Exit Establish comm child\n");

	return TASK_NO_ERROR;

}

status_t Node::nodeInit(void){
	/*
		This shall initialize all data structures and comm
		parameters for the node instance and also do the communication
		part too.
		Loads are initilaized during this module
	*/

	// Debug:
	Serial.write("Inside nodeInit\n");
	Serial.write("InitDone val: ");
	Serial.print(INIT_DONE);
	Serial.write('\n');

	if (FALSE == INIT_DONE){

		//TASK1: establish communication with the child and parent
		if (NUM_CHILDS){
			if (FALSE == COMM_ESTABLISHED_CHILD){
				establishCommChild();
			}
		}
		// Debug:
		Serial.write("DoneTask1\n");

		/*if (NUM_PARENT){
			if (FALSE == COMM_ESTABLISHED_PARENT){
				thisNode.establishCommParent();
			}
		}*/


		//TASK2 :request childs to send data, calculate priority based on that
		ProtocolReqChildData();
		// Debug:
		Serial.write("DoneTask2\n");
		//thisNode.ProtocolDLRequest();

		//TASK3: wait for parent to send ASL.

		while(getStatus());
		// Debug:
		Serial.write("DoneTask3\n");

		//Assign ASL to children and Loads
		ProtocolAssignLoads();
		// Debug:
		Serial.write("DoneTask4\n");

		//Start Allocation and launch tasks
		//INIT_DONE = TRUE;
	}
	return TASK_NO_ERROR;
}

status_t Node::Task(void){
	/*
	This function shall be executed cyclically everytime.
	This shall perform the periodic tasks that needs to be done for the
	node, eg. Calculating the Priorities and the Load allowance.

	We shall perform the algorith here, but do need to remember that
	we should use modular functions to allow for improvements later.

	Tasks to be performed here are:
	Task 1: Get priority from child nodes and loads
	Task 2: calculate the values and decide which loads to switch off
	Task 3: Communicate the info back to parent
	*/

	//Task 1:

	return thisNode.getStatus();

}

void Init(){
	/*
	Do what we normally keep for Setup function in the sketches
	*/
	// Task 0: Initialize the Node data structure
	MyNode.nodeSetChildAddr(childAddr);	// Fill in the child addresses
	
	while(COMM_NOT_INIT == MyNode.nodeCommInit(&childDevice, &parentDevice));	// HW Initialization takes place here

	// Task 1: We have to Initialize the Child and Load Data structure
	fillLoadState();	// Fill the Load Data structure with the initialized data

}

void TaskMain(void){

}


