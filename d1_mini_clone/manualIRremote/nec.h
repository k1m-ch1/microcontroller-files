#pragma once

#include <Arduino.h>
#include <stdint.h>

#define LOGGING_QUEUE_SIZE 8

#define STATE_MACHINE_FREQ 8000

#define IR_RECEIVER_PIN D4

enum States {
  START,
  ACG_PASSED,
  FIRST_PAUSE_PASSED,
  FIRST_LOW_OF_BIT_RECOGNIZED,
  PAUSE_PASSED,
  LOW_OF_BIT_RECOGNIZED,
  STATES_COUNT
};

const char *statesAsString[STATES_COUNT] = {"START",
                                            "ACG_PASSED",
                                            "FIRST_PAUSE_PASSED",
                                            "FIRST_LOW_OF_BIT_RECOGNIZED",
                                            "PAUSE_PASSED",
                                            "LOW_OF_BIT_RECOGNIZED"};

extern States loggingQueue[LOGGING_QUEUE_SIZE];

typedef struct {
  uint32_t mean;
  uint32_t epsilon;
} AcceptedRanges;
// this will be in microseconds

const AcceptedRanges aCGRange = {.mean = 9000, .epsilon = 1500};

const AcceptedRanges offPeriodRange = {.mean = 4500, .epsilon = 1000};

const AcceptedRanges lowOfBitRange = {.mean = 562, .epsilon = 200};

const AcceptedRanges highOfBitRange[2] = {{.mean = 562, .epsilon = 200},
                                          {.mean = 1687, .epsilon = 500}};

uint32_t getNextValidCommand();
