/*
Ascii banana
Writing bits from key state and typing characters

Author: http://github.com/pbrdmn
*/

#include "Keyboard.h"

#define DEBOUNCE_TIME 50

#define NUM_KEYS 8
int pins[]   = { 7, 8, 9, 10, 16, 14, 15, 18, };
char bits = 0;

int now = 0;
int lastActive = 0;

bool updateBits() {
  int active = 0;

  // read value of keys in as bits.
  for (int i = 0; i < NUM_KEYS; i++) {
    if (digitalRead(pins[i]) == LOW) {
      bitSet(bits, NUM_KEYS - 1 - i);
      active++;
    }
  }

  return active;
}


void setup() {
  for (int i = 0; i < NUM_KEYS; i++) pinMode(pins[i], INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  now = millis();

  bool active = updateBits();
  if (active) {
    lastActive = now;
  } else {
    if (now > lastActive + DEBOUNCE_TIME) {
      Keyboard.write(bits);
      bits = 0;
    }
  }

  delay(10);
}