#ifndef NODECOMMANDS_H
#define NODECOMMANDS_H

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <map>

// Define the function pointer type
typedef void (*FunctionPtr)();

// Declare the functionMap variable as extern
extern std::map<byte, FunctionPtr> functionMap;

// Function prototype for setup
void testInterface_userInput_setup();

// Function prototype for main functionality
void testInterface_userInput();

#endif
