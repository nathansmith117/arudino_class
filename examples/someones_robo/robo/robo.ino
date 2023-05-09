#include "MotorController.h"
#include "roboSignals.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

float joystickX, joystickY;

const int rightMotorId = 3;
const int leftMotorId = 5;

MotorController rightMotor;
MotorController leftMotor;

const float DRIVE_SPEED = 0.25;

long int millisPerLoop = 0;
long int lastTime = 0;
long int lastTimeWireless = 0;
long int wirelessSpeed = 0;

const long int MIN_WIRELESS_SPEED = 500;

// Handler for signals from radio.
void eventHandler(RoboSignal signal) {
  //printSignalDebug(signal);

  switch (signal.event) {
    case 0: // Get how much time has passed.
      if (lastTimeWireless == 0) {
        lastTimeWireless = signal.value;
      } else {
        wirelessSpeed = signal.value - lastTimeWireless;
        lastTimeWireless = signal.value;
      }
      
      break;
    case 5:
      joystickX = signal.value;
      break;
    case 6:
      joystickY = signal.value;
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(9600);

  // Setup radio.
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  joystickX = 0.0;
  joystickY = 0.0;

  rightMotor.setPin(rightMotorId);
  leftMotor.setPin(leftMotorId);
}

void loop() {
  readSignals(&radio, eventHandler);

  //Serial.print(joystickX);
  //Serial.print(" ");
  //Serial.println(joystickY);
  Serial.println(wirelessSpeed);

  // Get time passed.
  millisPerLoop = millis() - lastTime;
  lastTime = millis();

  wirelessSpeed += millisPerLoop;

  // To much has passed.
  if (wirelessSpeed >= MIN_WIRELESS_SPEED) {
    joystickX = 0.0;
    joystickY = 0.0;
  }

  rightMotor.setPower((-joystickY - joystickX) * DRIVE_SPEED);
  leftMotor.setPower((joystickY - joystickX) * DRIVE_SPEED);
  //rightMotor.setPower(-joystickY);
  //leftMotor.setPower(joystickY);


  //delay(10);
}
