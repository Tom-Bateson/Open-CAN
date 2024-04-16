#ifndef NODECOMMANDS_H
#define NODECOMMANDS_H

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <map>

#include "config.hpp"

// state variable prototype
class systemState {
public:
    static byte& State();
};

// Define the function pointer type
typedef void (*FunctionPtr)(unsigned char settings[6]);

// Declare the functionDictionary variable as extern
extern std::map<byte, FunctionPtr> functionDictionary;

// Function prototype for state
void setState(unsigned char* settings);

// Function prototype for comand runner
void runNodeCommand(unsigned char command[8]);

// Function prototype for main functionality
void handelUserInput_wiperSeting(unsigned char* settings);

// example prototype function
void exampleNodeFunction(unsigned char* settings);

#endif
