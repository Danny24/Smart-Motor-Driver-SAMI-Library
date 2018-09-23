#include "SAMI_2BRobots.h"
#define old_address 0x24
#define new_address 0x28

SAMI_2BRobots motor = SAMI_2BRobots(); //create object from library class

void setup()
{
  Serial.begin(9600);
  while (!Serial); //waits for serial terminal to be open, necessary in newer arduino boards.
  Serial.println("Smart Motor Driver (SAMI) I2C address changer:");

  if (!motor.begin(old_address)) //start SAMI with original address
  {
    Serial.println("Couldn't find SAMI! Check your connections and verify that the address is correct.");
    while (1); //don't do anything more.
  }
  Serial.println("SAMI found and changing I2C address..");

  motor.setAddress(new_address);
  motor.SAVE();
  motor.RESET(); //changes takes efect only after RESET
  delay(20);
  Serial.println("SAMI address change sucessful");
}

void loop()
{


}
