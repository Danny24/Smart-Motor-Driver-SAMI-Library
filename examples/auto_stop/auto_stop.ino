#include "SAMI_2BRobots.h"

SAMI_2BRobots motor = SAMI_2BRobots(); //create object from library class

void setup()
{
  Serial.begin(9600);
  while (!Serial); //waits for serial terminal to be open, necessary in newer arduino boards.
  Serial.println("Smart Motor Driver (SAMI) demo:");

  if (!motor.begin()) //start with default I2C address, if you specify one it will use that one instead
  {
    Serial.println("Couldn't find SAMI! Check your connections and verify that the address is correct.");
    while (1); //don't do anything more.
  }
  Serial.println("SAMI found and ready to work!!!");

  motor.setMode(7); //motor PID enabled, auto-stop PID enabled and safe direction toggle enabled mode select
  motor.setGear(150); //motor gearbox relation 150:1
  motor.setDiameter(42); //wheel diameter is 42 mm
  motor.setDistance(1000); //move 1000 mm until auto-stop triggers
  motor.setSpeed(80); //move fordward at 80 RPM's
  motor.setRPM_PID_KP(0.10); //set gains for motor RPM PID control
  motor.setRPM_PID_KD(0.01);
  motor.setRPM_PID_KI(0.04);
  motor.setATS_PID_KP(0.15); //set gains for auto-stop PID control
  motor.setATS_PID_KD(0.08);
  motor.setATS_PID_KI(0.03);
  motor.Run(1); //Start motor
}

void loop()
{
  Serial.print("Remaining distance: "); Serial.println(motor.getDistance());
  Serial.print("Motor actual RPM's: "); Serial.println(motor.getRPM());
  Serial.println(" ");
  delay(500);
}
