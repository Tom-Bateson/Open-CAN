#include "can_h.hpp"

#include <Arduino.h>

unsigned char* message;
byte data[8] = {};

void setup()
{
  Serial.begin(115200);
  startCAN();
}


void loop()
{
  // message = receiveCAN();
  // sendStandardCAN();
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/