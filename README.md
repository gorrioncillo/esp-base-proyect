# esp-base-proyect
ESP base project with LDR sensor, mqtt comunication protocol and servo motor as actuator.  

## Why
This is a proyect that will be a base/example for other proyects that will need testing, and CI automation.  
And a plus with code formating with astyle, static code analisys.

## Description
This is just a simple proyect, using Platformio, that will read a analog sensor, in this case a LDR, and using MQTT as a protocol of comunication to a broker.  
From the broker the ESP8266 will subscribe to a topic that publish data to move a servo motor, this will be the actuator.

## Documentation
ALL the documentation that will be used and the procedures to recreate this proyect will be write here on the README.md file.  
This because it will be easy to find information and then go deeper on some topic if you need.

## Links
[platformio oficial documentation](https://docs.platformio.org/en/latest/)  
[astyle](http://astyle.sourceforge.net/)
  We can use the hooks/pre-commit file to format the source code (.ino .hpp .cpp .h) files before the commit.  
  For this you need the file .astyle on the root of the proyect and `sudo apt install astyle` on ubuntu o the exe on the path for windows.

