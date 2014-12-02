/* Test Module for COMM transmit.*/

#include "Comm.h"
#include <Wire.h>

int led = 13;

Comm out(COMM_TYPE_I2C, COMM_NO_BAUD, SRC_I2C_ADDRESS);

void setup(){
  Wire.begin(SRC_I2C_ADDRESS);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  
  digitalWrite(led, HIGH);
  
  Serial.write("writing to buffer\n");
  for(int i=0;i <20; i++){
      out.commWriteBuffer('A');
  }
  
  Serial.write("Transmit Start\n");
  out.startTx = TRUE;
  out.Transmit(4); 
  Serial.write("Transmitting done\n");
  delay(100);
  digitalWrite(led, LOW);
  delay(2000);
}



