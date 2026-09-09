#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "nec.h"

void initReceiver() { pinMode(IR_RECEIVER_PIN, INPUT); }

bool detectEdgeFalling(bool prevState, bool currentState) {
  return prevState && (!currentState);
}

bool detectEdgeRising(bool prevState, bool currentState) {
  return (!prevState) && currentState);
}

uint32_t getNextValidCommand() {
  // this essentially runs the state machine until we get a valid 32 bit command
  // (blocking) and CPU intensive because it's polling
  uint32_t validCommand = 0;
  uint32_t validBitsCount = 0;
  // TODO: fix micros wrapping around.
  uint32_t stateMachineDelay = micros();
  States currentState = START;
  uint32_t lastFallingEdgeTimestamp = micros();
  uint32_t lastRisingEdgeTimestamp = micros();
  uint32_t lastTransitionTimestamp = micros();

  bool prevPinState = 1;
  bool currentPinState = 1;

  while (validBitsCount < 32) {
    stateMachineDelay = micros();
    // run the state machine until we get a valid command (blocking)
    prevPinState = currentPinState;
    currentPinState = digitalRead(IR_RECEIVER_PIN);

    switch (currentState) {
    case START:
      break;
    case ACG_PASSED:
      break;
    case FIRST_PAUSE_PASSED:
      break;
    case FIRST_LOW_OF_BIT_RECOGNIZED:
      break;
    case PAUSE_PASSED:
      break;
    case LOW_OF_BIT_RECOGNIZED:
      break;
    case STATES_COUNT:
      break;
    }

    stateMachineDelay = micros() - stateMachineDelay;
    if (stateMachineDelay > 0) {
      delayMicroseconds(stateMachineDelay);
    }
  }
}
