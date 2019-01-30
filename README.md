# Smart-Motor-Driver-SAMI-Library
Arduino library for SAMI the Smart Motor Driver by 2BRobots.

Here is how to use the library: 

First yu will need to include the library in the Arduino sketch

#include "SAMI_2BRobots.h"

Them create object from library class, you can use any other name instead of "motor", if using multiple motors create one ob ject per motor

SAMI_2BRobots motor = SAMI_2BRobots();

Now init SAMI, by default it uses address 0x24. For other addres just define it. This returns true if sucess and false when fail

motor.begin();

motor.begin(address);

There is also this functions to control SAMI, please check documentation and examples for know how to use it

motor.getAddress(); //return I2C address

motor.inverted(bool); //allows to swap motor direction CCW and CW in software. Set true or false.

motor.setAddress (address); //set I2C address, it requires SAVE and RESET before changes takes efect

motor.isRunning(); //returns 1 or 0 indicating if the motor is running or not

motor.Run (); //send 0 or 1 to stop or start the motor 

motor.getIOWPU(); //returns 1 or 0 indicating if the internal pull-ups are enabled or not

motor.setIOWPU (); //send 0 or 1 to enable or disable internal pull-ups, it requires SAVE and RESET before changes takes efect

motor.getMode(); //gets the actual operation mode

motor.setMode (); //changes the operation mode

motor.SAVE(); //saves non-volatile data

motor.RESET(); //it resets SAMI

motor.getGear(); //gets the gear relation

motor.setGear (); //sets the gear relation

motor.getDiameter(); //gets the wheeel diameter

motor.setDiameter (); //sets the wheeel diameter

motor.getRPM(); //gets the actual RPM's of the motor

motor.getSpeed(); //gets the desired speed to run the motor

motor.setSpeed (); //sets the desired speed to run the motor

motor.getDistance(); //gets the desired distance to run the motor or the total traveled distance since start

motor.setDistance();  //sets the desired distance to run the motor before auto-stop triggers 

motor.getAngle(); //gets the desired degrees to run the motor or the total traveled distance since start

motor.setAngle();  //sets the desired degrees to run the motor before auto-stop triggers 

motor.getRPM_PID_KP(); //gets gains

motor.setRPM_PID_KP(); //sets gains 

motor.getRPM_PID_KD();

motor.setRPM_PID_KD(); 

motor.getRPM_PID_KI();

motor.setRPM_PID_KI(); 

motor.getATS_PID_KP();

motor.setATS_PID_KP();

motor.getATS_PID_KD();

motor.setATS_PID_KD();

motor.getATS_PID_KI();

motor.setATS_PID_KI(); 
