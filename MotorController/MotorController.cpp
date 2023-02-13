#include "MotorController.h"

void MotorController::setPin(int pin) {
  this->pin = pin;
  motor.attach(pin);
}

int MotorController::getPin() {
  return pin;
}

void MotorController::setPower(double power) {
  this->power = power;
  motor.write(percentPowerToAngle(power));
}

double MotorController::getPower() {
  return power;
}

void MotorController::stop() {
  setPower(0.0);
}

void MotorController::setDeadZones(int motorMinDeadZone, int motorMaxDeadZone) {
  this->motorMinDeadZone = motorMinDeadZone;
  this->motorMaxDeadZone = motorMaxDeadZone;
}

int MotorController::percentPowerToAngle(double power) {
  int angle = 90 + (power * 90);
  
  // Min dead zone.
  if (angle < motorMinDeadZone) {
    angle = motorMinDeadZone;
  }

  // Max dead zone.
  if (angle > motorMaxDeadZone) {
    angle = motorMaxDeadZone;
  }

  return angle;
}