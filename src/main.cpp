#include "canFunctions.hpp"
#include "stateHandler.hpp"
#include "config.hpp"
#include "nodeCommands.hpp"

#include <Arduino.h>

// variables
unsigned char message[8];
byte data[8] = {0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Initialize state
state State  = STARTUP;


byte variable[8] = {0x10, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00}; // Example value
byte variable2[8] = {0x20, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00}; // Example value


void setup() {
  Serial.begin(115200);
  startCAN();
  runNodeCommand(variable);
}

void loop() {
  bool change = receiveCAN(message);
  
  State = stateHandler(message);

  runNodeCommand(variable2);



  

  // // Find the function pointer associated with the variable
  // auto funcId = functionDictionary.find(variable[0]);
  // if (funcId != functionDictionary.end()) {
  //   // cut the function id and start/stop from the mesage to leave the function steings
  //   unsigned char functionSetings[6];
  //   memcpy(functionSetings, variable + 2, 6);
  //   // Call the function using the function pointer
  //   FunctionPtr func = funcId->second;
  //   func(functionSetings);
  //   variable[0] = 0x20;
  // } else {
  //   // Handle invalid funcid
  //   Serial.println("Function dose not exist");
  // }





  // switch(State) {
  //   case STARTUP:
  //     testInterface_userInput_setup();
  //     break;
    
  //   case STATE_1:
      
  //     break;

  //   case STATE_2:
      
  //     break;

  //   case STATE_3:
      
  //     break;

  //   default:
  //     Serial.println("Issue");
  // }

  if (change)
  {
    sendStandardCAN(0x005, message);
  }
  
}