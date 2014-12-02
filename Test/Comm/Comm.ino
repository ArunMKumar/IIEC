/* 
Test Script for Comm module 
*/

#include "Comm.h"
#include "Wire.h"

int led = 13;
uint8_t buffer[12] = {1,2,3,4,5,6,7,8,9,10,11,12};

Comm tComm(COMM_TYPE_I2C);

void setup(){
   pinMode(led, OUTPUT);
}


void loop(){
  Serial.write("Filling Buffer...");
  tComm.outBuffer.writeBufferln(buffer, 11);
  digitalWrite(led, HIGH);
  delay(50);
  
  if(COMM_TX_FAIL == tComm.Transmit()){
    digitalWrite(led, HIGH);
  }
  else 
    digitalWrite(led, LOW);
  delay(50);
}

