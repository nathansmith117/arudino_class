#include "MotorController.h"

// Controlls a motor with my motor controller library and a pot.
#define POT_PIN A5

const int motor_pin = 9;
MotorController motor;

void setup() {
  motor.setPin(motor_pin);
  Serial.begin(9600);
}

void loop() {
  int input_value = analogRead(POT_PIN);
  double power = (input_value / 336.5) - 1;
  Serial.println(power);

  motor.setPower(power);
  delay(15);
}
