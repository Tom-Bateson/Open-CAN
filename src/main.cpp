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
      testInterface_wiperMotor_setup();
      // after setup teansition to initail operating state
      systemState::State() = RUN;

      // message[8]
      // send state to wipers user imput to start them
      sendStandardCAN(0x000,message);

      break;
    
    case RUN:
      // check the can modules buffer for a new mesage and update the  mesage array
      receiveCAN(message);
      // run the command indecated by the message
      runNodeCommand(message);



      // on receve from wiper send pesage to sensor if needed

      // receve from sensor info and store



      break;

    case WAIT:
      
      break;

    case ERROR:
      
      break;
  }
}