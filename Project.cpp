/*
Source file for the Project
Contains the task structure and the tasks that need to be completed.

Do all that you would do in the sketch here, then just use this call
in the sketch.

Arun M Kumar						30 Nov 2014
*/


#include "Project.h"
#include "Load.h"
#include "Node.h"

/*
	First we need to initialize the loads.
	For the time being we use 4 loads and work with them

		Initializing the Loads instances here
*/

Load Load1(LOAD_0R, LOAD_0W, LOAD_ID0, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load2(LOAD_1R, LOAD_1W, LOAD_ID1, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load3(LOAD_2R, LOAD_2W, LOAD_ID2, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load4(LOAD_3R, LOAD_3W, LOAD_ID3, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);


/*
	Creating the Node instanc here
*/

Node thisNode(NODE_ID, NODE_PID);


/*
Now lets create the basic functions Init and Task
*/

void Init(){
	/*
	Do what we normally keep for Setup function in the sketches
	*/

}




void TaskMain(void){

}


