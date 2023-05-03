#include "MotorController.h"
#include <Arduino.h>

void MotorController::setPin(int pin) {
  this->pin = pin;
  motor.attach(pin);
}

int MotorController::getPin() {
  return pin;
}

void MotorController::setPower(double power) {
  this->power = power;
  motor.writeMicroseconds(percentPowerToAngle(power));
}

double MotorController::getPower() {
  return power;
}

void MotorController::stop() {
  setPower(0.0);
}

int MotorController::percentPowerToAngle(double power) {
  return map(power * 1000, -1000, 1000, 1000, 2000);
}
