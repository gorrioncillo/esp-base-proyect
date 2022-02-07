#include "Arduino.h"

void setup()
{
Serial.begin (115200);
Serial.println ("Initial program");
}

void loop()
{
Serial.println ("hola mundo");
delay (1000);
}
