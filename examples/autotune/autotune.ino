#include <PIDAutotuner.h>
#include "SAMI_2BRobots.h"

SAMI_2BRobots motor = SAMI_2BRobots();
PIDAutotuner tuner1 = PIDAutotuner();
PIDAutotuner tuner2 = PIDAutotuner();

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!motor.begin(0x24)) //start with default I2C address, if you specify one it will use that one instead
  {
    Serial.println("Couldn't find SAMI! Check your connections and verify that the address is correct.");
    while (1); //don't do anything more.
  }
  Serial.println("SAMI found, hold on...");
  motor.RESET();
  delay(200);

  motor.setIOWPU(1); //when set to 1 SAMI internal pull-ups are enabled, clear to 0 to disable pull-ups
  motor.setMode(1); //select only PWM mode
  motor.setGear(150); //motor gearbox relation 150:1
  motor.setDiameter(70); //wheel diameter is 70 mm, needed later
  motor.Run(1); //Start motor

  Serial.println("Running auto-tunner");
  Serial.println("First where are going to tune motor Speed...");

  int loopInterval = 10000;
  int target = 100; //this value must be half of the RPM the motor is capable of deliver
  int range_min = -1023;
  int range_max = 1023;

  // Set the target value to tune to
  // This will depend on what you are tuning. This should be set to a value within
  // the usual range of the setpoint. For low-inertia systems, values at the lower
  // end of this range usually give better results. For anything else, start with a
  // value at the middle of the range.
  tuner1.setTargetInputValue(target);

  // Set the loop interval in microseconds
  // This must be the same as the interval the PID control loop will run at
  tuner1.setLoopInterval(loopInterval);

  // Set the output range
  // These are the maximum and minimum possible output values of whatever you are
  // using to control the system
  tuner1.setOutputRange(range_min, range_max);

  // Set the Ziegler-Nichols tuning mode
  // Set it to either PIDAutotuner::znModeBasicPID, PIDAutotuner::znModeLessOvershoot,
  // or PIDAutotuner::znModeNoOvershoot. Test with znModeBasicPID first, but if there
  // is too much overshoot you can try the others.
  tuner1.setZNMode(PIDAutotuner::znModeNoOvershoot);

  // This must be called immediately before the tuning loop
  tuner1.startTuningLoop();

  // Run a loop until tuner.isFinished() returns true
  long microseconds = micros();
  while (!tuner1.isFinished()) {

    // This loop must run at the same speed as the PID control loop being tuned
    long prevMicroseconds = microseconds;
    microseconds = micros();

    // Get input value here (temperature, encoder position, velocity, etc)
    double input = motor.getRPM();

    // Call tunePID() with the input value
    double output = tuner1.tunePID(input);

    // Set the output - tunePid() will return values within the range configured
    // by setOutputRange(). Don't change the value or the tuning results will be
    // incorrect.
    motor.setSpeed(output);

    // This loop must run at the same speed as the PID control loop being tuned
    while (micros() - microseconds < loopInterval) delayMicroseconds(1);
  }

  // Turn the output off here.
  motor.setSpeed(0);
  motor.Run(0);

  // Get PID gains - set your PID controller's gains to these
  double kp = tuner1.getKp();
  double ki = tuner1.getKi();
  double kd = tuner1.getKd();

  Serial.println("Tunning speed complete, gains obtained are:");
  Serial.print("KP: "); Serial.println((float)kp, 4);
  Serial.print("KD: "); Serial.println((float)kd, 4);
  Serial.print("KI: "); Serial.println((float)ki, 4);
  motor.setRPM_PID_KP(kp);
  motor.setRPM_PID_KD(kd);
  motor.setRPM_PID_KI(ki);
  while (motor.getRPM() != 0);
  delay(2000);
  Serial.println(" ");

  Serial.println("Now we are going to tune auto-stop when the travel distance is reach...");
  motor.setMode(2); //select speed PID mode, we will be using previusly obtained gains
  motor.setDistance(0);
  motor.Run(1); //Start motor
  target = 1000; //target distance, doesn't matter just assign a realistic value diferent to 0
  range_min = -200; //motor maximun capable speed backwards
  range_max = 200; //motor maximun capable speed fordwards

  // Set the target value to tune to
  // This will depend on what you are tuning. This should be set to a value within
  // the usual range of the setpoint. For low-inertia systems, values at the lower
  // end of this range usually give better results. For anything else, start with a
  // value at the middle of the range.
  tuner2.setTargetInputValue(target);

  // Set the loop interval in microseconds
  // This must be the same as the interval the PID control loop will run at
  tuner2.setLoopInterval(loopInterval);

  // Set the output range
  // These are the maximum and minimum possible output values of whatever you are
  // using to control the system
  tuner2.setOutputRange(range_min, range_max);

  // Set the Ziegler-Nichols tuning mode
  // Set it to either PIDAutotuner::znModeBasicPID, PIDAutotuner::znModeLessOvershoot,
  // or PIDAutotuner::znModeNoOvershoot. Test with znModeBasicPID first, but if there
  // is too much overshoot you can try the others.
  tuner2.setZNMode(PIDAutotuner::znModeNoOvershoot);

  // This must be called immediately before the tuning loop
  tuner2.startTuningLoop();

  microseconds = micros();
  while (!tuner2.isFinished()) {

    // This loop must run at the same speed as the PID control loop being tuned
    long prevMicroseconds = microseconds;
    microseconds = micros();

    // Get input value here (temperature, encoder position, velocity, etc)
    double input = motor.getDistance();

    // Call tunePID() with the input value
    double output = tuner2.tunePID(input);

    // Set the output - tunePid() will return values within the range configured
    // by setOutputRange(). Don't change the value or the tuning results will be
    // incorrect.
    motor.setSpeed(output);

    // This loop must run at the same speed as the PID control loop being tuned
    while (micros() - microseconds < loopInterval) delayMicroseconds(1);
  }

  // Turn the output off here.
  motor.setSpeed(0);
  motor.Run(0);

  // Get PID gains - set your PID controller's gains to these
  kp = tuner2.getKp();
  ki = tuner2.getKi() / 10000;
  kd = tuner2.getKd() / 100;

  Serial.println("Tunning auto-stop complete, gains obtained are:");
  Serial.print("KP: "); Serial.println((float)kp, 4);
  Serial.print("KD: "); Serial.println((float)kd, 4);
  Serial.print("KI: "); Serial.println((float)ki, 4);
  motor.setATS_PID_KP(kp);
  motor.setATS_PID_KD(kd);
  motor.setATS_PID_KI(ki);
  Serial.println("Tunning complete, saving data into SAMI...");
  motor.SAVE();
  motor.RESET();
  delay(10);
  Serial.println("Done. SAMI configurations are:");
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
  Serial.println("Thank you :)");

}

void loop() {

  // ...
}
