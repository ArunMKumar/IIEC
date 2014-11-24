int led = 13;

void setup()
{

  /* add setup code here */
	pinMode(led, OUTPUT);

}

void loop()
{

	digitalWrite(led, HIGH);
	delay(100);
	digitalWrite(led, LOW);
	delay(100);
  /* add main program code here */

}
