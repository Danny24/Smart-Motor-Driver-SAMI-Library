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
  m1.setRPM_PID_KP(1.70);
  m1.setRPM_PID_KD(22.11);
  m1.setRPM_PID_KI(0.08);
  m1.setATS_PID_KP(3.48);
  m1.setATS_PID_KD(1.97);
  m1.setATS_PID_KI(0.0000);

  m2.setMode(4);
  m2.setGear(150);
  m2.setDiameter(70);
  m2.setRPM_PID_KP(1.70);
  m2.setRPM_PID_KD(22.11);
  m2.setRPM_PID_KI(0.08);
  m2.setATS_PID_KP(3.48);
  m2.setATS_PID_KD(1.97);
  m2.setATS_PID_KI(0.0000);

  m3.setMode(4);
  m3.setGear(150);
  m3.setDiameter(70);
  m3.setRPM_PID_KP(1.70);
  m3.setRPM_PID_KD(22.11);
  m3.setRPM_PID_KI(0.08);
  m3.setATS_PID_KP(3.48);
  m3.setATS_PID_KD(1.97);
  m3.setATS_PID_KI(0.0000);

  m4.setMode(4);
  m4.setGear(150);
  m4.setDiameter(70);
  m4.setRPM_PID_KP(1.70);
  m4.setRPM_PID_KD(22.11);
  m4.setRPM_PID_KI(0.08);
  m4.setATS_PID_KP(3.48);
  m4.setATS_PID_KD(1.97);
  m4.setATS_PID_KI(0.0000);

  delay(5000);
  
  m1.setSpeed(100);
  m2.setSpeed(100);
  m3.setSpeed(100);
  m4.setSpeed(100);
}

void loop()
{
  m1.setDistance(1000);
  m2.setDistance(1000);
  m3.setDistance(-1000);
  m4.setDistance(-1000);

  m1.Run(1);
  m2.Run(1);
  m3.Run(1);
  m4.Run(1);
  while (m1.isRunning() | m2.isRunning() | m3.isRunning() | m4.isRunning());

  m1.setDistance(285);
  m2.setDistance(285);
  m3.setDistance(285);
  m4.setDistance(285);

  m1.Run(1);
  m2.Run(1);
  m3.Run(1);
  m4.Run(1);
  while (m1.isRunning() | m2.isRunning() | m3.isRunning() | m4.isRunning());

  m1.setDistance(1000);
  m2.setDistance(1000);
  m3.setDistance(-1000);
  m4.setDistance(-1000);

  m1.Run(1);
  m2.Run(1);
  m3.Run(1);
  m4.Run(1);
  while (m1.isRunning() | m2.isRunning() | m3.isRunning() | m4.isRunning());

  m1.setDistance(-285);
  m2.setDistance(-285);
  m3.setDistance(-285);
  m4.setDistance(-285);

  m1.Run(1);
  m2.Run(1);
  m3.Run(1);
  m4.Run(1);
  while (m1.isRunning() | m2.isRunning() | m3.isRunning() | m4.isRunning());
}
