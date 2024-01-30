#include "canFunctions.hpp"
#include "stateHandler.hpp"
#include "config.hpp"

#include <Arduino.h>

// variables
unsigned char* message;
byte data[8] = {0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


// Initialize state
state currentState  = IDLE;
state previousState = IDLE;

void setup() {
  Serial.begin(115200);
  startCAN();
  
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  message = receiveCAN();
  currentState = stateHandler(message);

  switch(currentState) {
    case STATE_1:
      Serial.print("Case 1: ");
      Serial.println(message[1]);
      digitalWrite(7, LOW);
      digitalWrite(9, LOW);
      data[1] = 1;
      break;
    
    case STATE_2:
      Serial.print("Case 2: ");
      Serial.println(message[1]);
      digitalWrite(7, LOW);
      digitalWrite(9, HIGH);
      data[1] = 2;
      break;

    case STATE_3:
      Serial.print("Case 3: ");
      Serial.println(message[1]);
      digitalWrite(7, HIGH);
      digitalWrite(9, LOW);
      data[1] = 3;
      break;

    case STATE_4:
      Serial.print("Case 4: ");
      Serial.println(message[1]);
      digitalWrite(7, HIGH);
      digitalWrite(9, HIGH);
      data[1] = 4;
      break;

    default:
      Serial.println("Issue");
  }

  if (stateChange(previousState, currentState))
  {
    sendStandardCAN(0x300, data);
  }
}