#include "config.hpp"
#include "nodeCommands.hpp"

// Create a map to associate function pointers with values
std::map<byte, FunctionPtr> functionMap = {
    {0x10, testInterface_userInput_setup},
    {0x20, testInterface_userInput}
};

// void runNodeComands() {
    
// }

// // Find the function pointer associated with the variable
// auto it = functionMap.find(variable);
//     if (it != functionMap.end()) {
//     // Call the function using the function pointer
//     FunctionPtr func = it->second;
//     func();
//     variable = 0x200;
//     } else {
//     // Handle invalid values
//     Serial.println("Invalid value for variable");
// }

void testInterface_userInput_setup() {
    pinMode(4, OUTPUT);
    pinMode(A3, INPUT_PULLUP);

    pinMode(5, OUTPUT);
    pinMode(A4, INPUT_PULLUP);

    pinMode(6, OUTPUT);
    pinMode(A5, INPUT_PULLUP);
}

void testInterface_userInput() {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
}