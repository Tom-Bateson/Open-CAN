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
    case STARTUP: {
      // begin serial
      Serial.begin(115200);
      // start the interface to the can module over spi
      startCAN();
      // run through setup of node comands that need it (BAD - find a better way to do this)
      testInterface_wiperMotor_setup();
      // after setup teansition to initail operating state
      systemState::State() = RUN;

      unsigned char send[8] = {0x20, 0x00, 0x10, 0x00, 0x00, 0x00, 0xff, 0x01};
      // unsigned char send[8] = {0};
      // send[0] = 0x20; // change and add mesage formating


      // send state to wipers user imput to start them
      sendStandardCAN(0x201,send);

      // // clear the mesage buffer redy for the next mesage
      // memset(message, 0, sizeof(message));

    
      break;
    }

    case RUN:
      
      // check the can modules buffer for a new mesage and update the  mesage array
      receiveCAN(message);
      // run the command indecated by the message
      // runNodeCommand(message);

      
      Serial.print("MESAGE: ");
      Serial.print(message[0]);
      Serial.print(" : ");
      Serial.print(message[1]);
      Serial.print(" : ");
      Serial.print(message[2]);
      Serial.print(" : ");
      Serial.print(message[3]);
      Serial.print(" : ");
      Serial.print(message[4]);
      Serial.print(" : ");
      Serial.print(message[5]);
      Serial.print(" : RETURN ADR : ");
      Serial.println(message[6]+message[7],HEX);
      

      // on receve from wiper send pesage to sensor if needed

      // receve from sensor info and store



      break;

    case WAIT:
      
      break;

    case ERROR:
      
      break;
  }
}