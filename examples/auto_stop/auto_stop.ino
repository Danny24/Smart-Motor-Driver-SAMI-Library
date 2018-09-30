#include "SAMI_2BRobots.h"

SAMI_2BRobots motor = SAMI_2BRobots(); //create object from library class

void setup()
{
  Serial.begin(9600);
  while (!Serial); //waits for serial terminal to be open, necessary in newer arduino boards.
  Serial.println("Smart Motor Driver (SAMI) demo:");

  if (!motor.begin(0x24)) //start with default I2C address, if you specify one it will use that one instead
  {
    Serial.println("Couldn't find SAMI! Check your connections and verify that the address is correct.");
    while (1); //don't do anything more.
  }
  Serial.println("SAMI found and ready to work!!!");


  motor.RESET(); //reset SAMI just in case is already running
  delay(20); //wait SAMI re-boot after Reset

  Serial.println("This is the data saved into SAMI memory:");
  Serial.print("Address: 0x"); Serial.println(motor.getAddress(), HEX);
  Serial.print("IOWPU: "); Serial.println(motor.getIOWPU());
  Serial.print("Gear: "); Serial.println(motor.getGear());
  Serial.print("Diameter: "); Serial.println(motor.getDiameter());
  Serial.print("RPM_PID_KP: "); Serial.println(motor.getRPM_PID_KP(), 4);
  Serial.print("RPM_PID_KD: "); Serial.println(motor.getRPM_PID_KD(), 4);
  Serial.print("RPM_PID_KI: "); Serial.println(motor.getRPM_PID_KI(), 4);
  Serial.print("ATS_PID_KP: "); Serial.println(motor.getATS_PID_KP(), 4);
  Serial.print("ATS_PID_KD: "); Serial.println(motor.getATS_PID_KD(), 4);
  Serial.print("ATS_PID_KI: "); Serial.println(motor.getATS_PID_KI(), 4);

  motor.setMode(4); //motor PID enabled, auto-stop PID enabled and safe direction toggle disabled mode select
  motor.setGear(150); //motor gearbox relation 150:1
  motor.setDiameter(70); //wheel diameter is 70 mm
  motor.setSpeed(80); //move fordward at 80 RPM's
  motor.setDistance(1000); //move 1000 mm until auto-stop triggers
  motor.setRPM_PID_KP(1.70); //set gains for motor RPM PID control
  motor.setRPM_PID_KD(22.11);
  motor.setRPM_PID_KI(0.08);
  motor.setATS_PID_KP(3.48); //set gains for auto-stop PID control
  motor.setATS_PID_KD(1.97);
  motor.setATS_PID_KI(0.0000);
  //motor.SAVE(); //uncoment to save this parameters, we highly recommend using autotune before this test and use gains obtained there

  delay(1000);
  Serial.println("Let's go :)!!!");
  motor.Run(1); //Start motor
}

void loop()
{
  do
  {
    Serial.print("Total Moved Distance: "); Serial.println(motor.getDistance());
    Serial.print("Motor actual RPM's: "); Serial.println(motor.getRPM());
    Serial.print("Motor is running: "); Serial.println(motor.isRunning());
    Serial.println(" ");
    delay(100);
  }
  while (motor.isRunning());
  Serial.println("Now stop.");
  while (1);
}
