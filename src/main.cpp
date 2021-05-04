#include <stdio.h>
#include <Arduino.h>
#include <stdint.h>

#include "module1/module1.hpp"

#define MIDI_BAUD_RATE 31250

int main(int argc, char *argv[]) {
  int res = module1_function(0);
  printf("Result = %i\n", res);
  Serial.begin(115200);
  Serial1.begin(MIDI_BAUD_RATE);

  Serial.println("Beginning...\n");
  // Serial6

  while(true) {
    if (Serial1.available() > 0) {
      uint8_t incomingByte = Serial1.read();
      Serial.println(incomingByte);
      Serial1.write(incomingByte);
    } else {
      Serial.println("Not dead!\n");
      delay(1000);
    }

  }
  return res;
}
