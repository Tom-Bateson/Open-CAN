#include "canFunctions.hpp"
#include "stateHandler.hpp"
#include "config.hpp"

#include <Arduino.h>

// variables
unsigned char* message;
byte data[8] = {};

// Initialize state
state currentState = IDLE;

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
      Serial.println("Case 1");
      digitalWrite(7, LOW);
      digitalWrite(9, LOW);
      break;
    
    case STATE_2:
      Serial.println("Case 2");
      digitalWrite(7, LOW);
      digitalWrite(9, HIGH);
      break;

    case STATE_3:
      Serial.println("Case 3");
      digitalWrite(7, HIGH);
      digitalWrite(9, LOW);
      break;

    case STATE_4:
      Serial.println("Case 4");
      digitalWrite(7, HIGH);
      digitalWrite(9, HIGH);
      break;

    default:
      Serial.println("Issue");
  }

  // sendStandardCAN();
}