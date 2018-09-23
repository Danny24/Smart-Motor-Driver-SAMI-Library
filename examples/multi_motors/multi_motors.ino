#include "SAMI_2BRobots.h"

SAMI_2BRobots m1 = SAMI_2BRobots();
SAMI_2BRobots m2 = SAMI_2BRobots();
SAMI_2BRobots m3 = SAMI_2BRobots();
SAMI_2BRobots m4 = SAMI_2BRobots();

void setup()
{
  m1.begin(0x25);
  m2.begin(0x26);
  m3.begin(0x27);
  m4.begin(0x28);

  m1.RESET();
  m2.RESET();
  m3.RESET();
  m4.RESET();
  delay(20);

  m1.setMode(4);
  m1.setGear(150);
  m1.setDiameter(70);
  m1.setRPM_PID_KP(0.17);
  m1.setRPM_PID_KD(0.06);
  m1.setRPM_PID_KI(0.12);
  m1.setATS_PID_KP(1.90971803);
  m1.setATS_PID_KD(78.50527954);
  m1.setATS_PID_KI(0.03070187);

  m2.setMode(4);
  m2.setGear(150);
  m2.setDiameter(70);
  m2.setRPM_PID_KP(0.17);
  m2.setRPM_PID_KD(0.06);
  m2.setRPM_PID_KI(0.12);
  m2.setATS_PID_KP(1.90971803);
  m2.setATS_PID_KD(78.50527954);
  m2.setATS_PID_KI(0.03070187);

  m3.setMode(4);
  m3.setGear(150);
  m3.setDiameter(70);
  m3.setRPM_PID_KP(0.17);
  m3.setRPM_PID_KD(0.06);
  m3.setRPM_PID_KI(0.12);
  m3.setATS_PID_KP(1.90971803);
  m3.setATS_PID_KD(78.50527954);
  m3.setATS_PID_KI(0.03070187);

  m4.setMode(4);
  m4.setGear(150);
  m4.setDiameter(70);
  m4.setRPM_PID_KP(0.17);
  m4.setRPM_PID_KD(0.06);
  m4.setRPM_PID_KI(0.12);
  m4.setATS_PID_KP(1.90971803);
  m4.setATS_PID_KD(78.50527954);
  m4.setATS_PID_KI(0.03070187);

  delay(1000);

  m1.setSpeed(80);
  m2.setSpeed(80);
  m3.setSpeed(80);
  m4.setSpeed(80);

  m1.setDistance(400);
  m2.setDistance(400);
  m3.setDistance(-400);
  m4.setDistance(-400);

  m1.Run(1);
  m2.Run(1);
  m3.Run(1);
  m4.Run(1);
}

void loop()
{
  while (1);
  m1.setDistance(400);
  m2.setDistance(-400);
  m1.setSpeed(100);
  m2.setSpeed(100);
  m1.Run(1);
  m2.Run(1);
  do
  {
    delay(50);
  }
  while (m1.isRunning() || m2.isRunning());
  delay(500);
  m1.setSpeed(50);
  m2.setSpeed(50);
  m1.setDistance(80);
  m2.setDistance(80);
  m1.Run(1);
  m2.Run(1);
  delay(100);
  do
  {
    delay(50);
  }
  while (m1.isRunning() || m2.isRunning());
  delay(500);
}
