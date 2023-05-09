#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "roboSignals.h"

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

const int BUTTON1 = 3;
const int BUTTON2 = 4;
const int BUTTON3 = 5;
const int BUTTON4 = 6;

const float DEAD_ZONE = 0.03;

void setup() {
  Serial.begin(9600);

  // Set pins.
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);

  // Setup radio.
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
  // Get joystick and convert to float.
  float x = (float)analogRead(A0) / 512.0 - 1.0;
  float y = (float)analogRead(A1) / 512.0 - 1.0;

  // Dead zones.
  if (abs(x) <= DEAD_ZONE) {
    x = 0.0;
  } if (abs(y) <= DEAD_ZONE) {
    y = 0.0;
  }

  // Push signals.
  pushSignal(newRoboSignal(0, millis()));
  pushSignal(newRoboSignal(1, digitalRead(BUTTON1)));
  pushSignal(newRoboSignal(2, digitalRead(BUTTON2)));
  pushSignal(newRoboSignal(3, digitalRead(BUTTON3)));
  pushSignal(newRoboSignal(4, digitalRead(BUTTON4)));
  pushSignal(newRoboSignal(5, x));
  pushSignal(newRoboSignal(6, y));

  //radio.write(&newRoboSignal(4, x), sizeof(RoboSignal));
  //radio.write(&newRoboSignal(5, y), sizeof(RoboSignal));

  // Sends the signals that have been pushed.
  sendSignals(&radio);

  //delay(10);
}
