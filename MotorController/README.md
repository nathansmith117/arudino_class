# A pwm motor controller

# Installing
Place "MotorController.cpp" and "MotorController.h" in your project folder.

# Motor controllers you might use.

## TalonSRX docs
https://docs.google.com/gview?url=https://link.vex.com/vexpro/pdf/217-8080-Talon-SRX-Users-Guide&embedded=true

## VictorSPX docs
https://content.vexrobotics.com/vexpro/pdf/VictorSPX-UserGuide-20190117.pdf

## More motor controller stuff
https://content.vexrobotics.com/vexpro/pdf/VictorSPX-InfoSheet-20171129.pdf

# MotorController class

#### void setPin(int pin);
Sets the pwm pin used by the controller.
                                                               
#### int getPin();
Returns the current pwm pin.

#### void setPower(double power);
Sets the percent power output.

-1.0 to 1.0
                                                               
#### double getPower();
Gets the percent power the motor is set to.

-1.0 to 1.0
                                                               
#### void stop();
Sets power to 0.0
                                                               
#### void setDeadZones(int motorMinDeadZone, int motorMaxDeadZone); // Been removed
The motor may not be perfect so there are dead zones.

By default motorMinDeadZone is 0 and motorMaxDeadZone is 180

# Example code

```
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
```
