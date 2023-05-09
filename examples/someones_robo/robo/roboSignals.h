#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#ifndef ROBO_SIGNALS_H
#define ROBO_SIGNALS_H

// Max number of signals that can be sent at a time.
#ifndef SIGNALS_MAX
#define SIGNALS_MAX 20
#endif

typedef uint8_t EVENT;
typedef float VALUE;

typedef struct RoboSignal {
  EVENT event; // Will be used as the index in signals list.
  VALUE value;
} RoboSignal;

typedef void (*EVENT_CB)(RoboSignal signal);

RoboSignal newRoboSignal(EVENT event, VALUE value) {
  return (RoboSignal){event, value};
}

// Not for direct use.
typedef struct SignalsList {
  VALUE values[SIGNALS_MAX];
  EVENT events[SIGNALS_MAX];
  size_t eventsSize = 0;
} SignalsList;

SignalsList newSignals;
SignalsList lastSignals;

// Add signal to signals list.
void pushSignal(RoboSignal signal) {
  newSignals.values[signal.event] = signal.value;
  newSignals.events[newSignals.eventsSize] = signal.event;
  ++newSignals.eventsSize;
}

void sendSignals(const RF24 * radio) {
  int i;

  bool useLastSignals = newSignals.eventsSize == lastSignals.eventsSize;

  EVENT event;
  RoboSignal signal;

  if (newSignals.eventsSize == 0) {
    return;
  }

  // Send events that have changed and copy.
  for (i = 0; i < newSignals.eventsSize; ++i) {
    event = newSignals.events[i];

    // Send signal if changed.
    if (newSignals.values[event] != lastSignals.values[event] || !useLastSignals) {
      signal = newRoboSignal(event, newSignals.values[event]);
      radio->write(&signal, sizeof(RoboSignal));
    }

    // Copy over.
    lastSignals.values[event] = newSignals.values[event];
    lastSignals.events[i] = event;
  }

  lastSignals.eventsSize = newSignals.eventsSize;

  // Clear.
  newSignals.eventsSize = 0;
}

void readSignals(const RF24 * radio, const EVENT_CB cb) {
  RoboSignal signal;

  // Read signals and call cb.
  while (radio->available()) {
    radio->read(&signal, sizeof(RoboSignal));
    cb(signal);
  }
}

void printSignalDebug(RoboSignal signal) {
  Serial.print("Event: ");
  Serial.print(signal.event);
  Serial.print(", Value: ");
  Serial.print(signal.value);
  Serial.print(", Time: ");
  Serial.println(millis());
}

#endif