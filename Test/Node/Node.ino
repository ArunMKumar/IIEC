/* Test Code for Node

Result: Every Task was being calleda s expected.
*/

#include "Wire.h"
#include "Node.h"
#include "Load.h"
#include "Comm.h"

int led = 13;


/*
Initilaizing the Devices with the devicce attributes
*/
deviceAttrib_t outComm={COMM_TYPE_I2C,0,SRC_I2C_ADDRESS};

/*
  Initializing the Loads instances here
*/

Load Load1(LOAD_0R, LOAD_0W, LOAD_ID0, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load2(LOAD_1R,LOAD_1W, LOAD_ID1, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load3(LOAD_2R, LOAD_2W, LOAD_ID2, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load4(LOAD_3R, LOAD_3W, LOAD_ID3, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);


/*
Initializing the current node here
*/
Node thisNode(NODE_ID, NODE_PID);  // Initializing the Node

void setup(){
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  thisNode.commInitChild(&outComm);
}

void loop(){
  digitalWrite(led, LOW);
  thisNode.Task(); 
  delay(100);
  Load1.Task();
  Load2.Task();
  Load3.Task();
  Load4.Task();
  digitalWrite(led, HIGH);
  delay(100);
}

  
