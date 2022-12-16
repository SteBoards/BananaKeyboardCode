/*
Banana
Demonstrating tap behaviour with on/off debouncing.

Author: http://github.com/pbrdmn
*/

#include "Keyboard.h"

#define DEBOUNCE_TIME 50
#define TIMEOUT 2000

// hardware pins (do not edit)
#define NUM_KEYS 8
int pins[]   = { 7, 8, 9, 10, 16, 14, 15, 18 };

// define key outputs here
char keys[]  = { KEY_ESC, KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19 };

bool prevVal[NUM_KEYS];
int timePressed[NUM_KEYS];

int now = 0;

boolean readSwitch(int i) {
  // return quickly if debouncing
  if (timePressed[i] + DEBOUNCE_TIME > now) return prevVal[i];

  // read new button value
  bool val = digitalRead(pins[i]);

  // if state change
  if (val != prevVal[i]) {
    if (val == LOW) {
      // record when press started
      timePressed[i] = now;
    } else {
      // calculate press duration
      int duraion = now - timePressed[i];
      
      // handle button press for duration
      if (duraion < DEBOUNCE_TIME) {
        // ignore noise
      } else if (duraion < TIMEOUT) {
        // handle tap
        Keyboard.write(keys[i]);
      } else {
        // held too long
      }
    }
    
    prevVal[i] = val;
  }

  // Clock Rollover - millis rolls over every 49 days or so
  if (timePressed[i] > now) {
    timePressed[i] = 0;
  }

  // Return pin val
  return prevVal[i];
}


void setup() {
  for (int i = 0; i < NUM_KEYS; i++) {
    pinMode(pins[i], INPUT_PULLUP);
    prevVal[i] = LOW;
    timePressed[i] = 0;
  }
  Keyboard.begin();
}

void loop() {
  now = millis();

  for (int i = 0; i < NUM_KEYS; i++) {
    readSwitch(i);
  }
}