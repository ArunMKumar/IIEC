#include "Project.h"
#include "Load.h"
#include "Node.h"
#include "Comm.h"
#include "Wire.h"

int led =13;
Node myNode;

void setup(){
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  myNode.nodeInit();
}

void loop(){
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}


void commRxISR(int dataCount){
  /*
  Interrupt service routine for the Comm receive event
 */

  if (COMM_TYPE_I2C == myNode.commChild.getDeviceType()){
	while (0 < Wire.available()){	// if any data available
		myNode.commChild.commWriteInBuffer(Wire.read());
	}
   }
}
