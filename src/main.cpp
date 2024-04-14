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


byte variable = 0x10; // Example value



void setup() {
  Serial.begin(115200);
  startCAN();
}

void loop() {
  bool change = receiveCAN(message);
  
  State = stateHandler(message);





  

  // Find the function pointer associated with the variable
  auto it = functionMap.find(variable);
  if (it != functionMap.end()) {
    // Call the function using the function pointer
    FunctionPtr func = it->second;
    func();
    variable = 0x20;
  } else {
    // Handle invalid values
    Serial.println("Invalid value for variable");
  }





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