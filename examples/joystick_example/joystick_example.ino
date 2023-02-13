/*
A simple example of how to use the joystick
*/

// Axis and button pins.
const int x_pin = A1;
const int y_pin = A2;
const int button_pin = 2;

void setup() {
  // Set pin mode.
  pinMode(button_pin, INPUT_PULLUP);

  // Start serial.
  Serial.begin(9600);
}

void loop() {
  // Get axis.
  int x_value = analogRead(x_pin);
  int y_value = analogRead(y_pin);

  // Get button.
  int button_value = digitalRead(button_pin);

  // Print values to serial.
  Serial.print(x_value);
  Serial.print(" ");
  Serial.print(y_value);
  Serial.print(" ");
  Serial.println(button_value);

  delay(10);
}
