/*
 * A pwd motor controller.
 * Been tested with victorspx and talonsrx and might work with others (---:
*/

#include <Servo.h>

#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

class MotorController {
  public:

  // Sets the pwd pin used by the controller.
  void setPin(int pin);

  // Returns the current pwd pin.
  int getPin();
  
  // Sets the percent power output.
  // -1.0 to 1.0
  void setPower(double power);

  // Gets the percent power the motor is set to.
  // -1.0 to 1.0
  double getPower();

  // Sets power to 0.0
  void stop();

  // The motor may not be perfect so there are dead zones.
  // By default motorMinDeadZone is 0 and motorMaxDeadZone is 180.
  void setDeadZones(int motorMinDeadZone, int motorMaxDeadZone);

  private:
  int pin;
  double power = 0.0;
  Servo motor;

  int motorMinDeadZone = 0;
  int motorMaxDeadZone = 180;
  
  // Converts percerent power to angle.
  // 180 = full forward, 90 = not moving, 0 to full backwards.
  int percentPowerToAngle(double power);
};

#endif
