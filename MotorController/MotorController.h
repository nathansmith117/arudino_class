#include <Servo.h>

#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

class MotorController {
  public:
  void setPin(int pin);
  int getPin();
  
  // 1 to -1
  void setPower(double power);
  double getPower();

  void stop();
  void setDeadZones(int motorMinDeadZone, int motorMaxDeadZone);

  private:
  int pin;
  double power = 0.0;
  Servo motor;

  // The motor may not be perfect so there are dead zones.
  int motorMinDeadZone = 6;
  int motorMaxDeadZone = 180;
  
  // 180 = full forward, 90 = not moving, 0 to full backwards.
  int percentPowerToAngle(double power);
};

#endif