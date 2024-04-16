#include "config.hpp"
#include "canFunctions.hpp"
#include "stateHandler.hpp"
#include "nodeCommands.hpp"

#include <Arduino.h>

// mesage array
unsigned char message[8] = {0};

void setup() {
  // Set the initial state to STARTUP
  systemState::State() = STARTUP;
}

void loop() {
  switch(systemState::State()) {
    case STARTUP:
      // begin serial
      Serial.begin(115200);
      // start the interface to the can module over spi
      startCAN();
      // run through setup of node comands that need it (BAD - find a better way to do this)
      testInterface_rainSensor_setup();
      // after setup teansition to initail operating state
      systemState::State() = RUN;
      break;
    
    case RUN:
      // check the can modules buffer for a new mesage and update the  mesage array
      receiveCAN(message);
      // run the command indecated by the message
      runNodeCommand(message);
      break;

    case WAIT:
      
      break;

    case ERROR:
      
      break;
  }

  // if (change)
  // {
  //   sendStandardCAN(0x005, message);
  // }
  
}