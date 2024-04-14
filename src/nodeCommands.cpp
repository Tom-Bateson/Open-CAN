#include "config.hpp"
#include "nodeCommands.hpp"

// Create a map to associate function pointers with values
std::map<byte, FunctionPtr> functionDictionary = {
    {0x10, testInterface_userInput_setup},
    {0x20, testInterface_userInput}
};

void runNodeCommand(unsigned char command[8]) {
    // Find the function pointer associated with the variable
    auto funcId = functionDictionary.find(command[0]);
    if (funcId != functionDictionary.end()) {
        // cut the function id and start/stop from the mesage to leave the function steings
        unsigned char functionSetings[6];
        memcpy(functionSetings, command + 2, 6);
        // Call the function using the function pointer
        FunctionPtr func = funcId->second;
        func(functionSetings);
    } else {
        // Handle invalid funcid
        Serial.println("Function dose not exist");
    }
}



// void runNodeComand(unsigned char comand[8]) {
//     auto funcId = functionDictionary.find(comand[0]);
//     if (funcId != functionDictionary.end()) {
//         FunctionPtr func = funcId->second;
//         unsigned char functionSetings[6];
//         // Copy the last 6 elements of comand byteArray into functionSetings byteArray
//         memcpy(functionSetings, comand + 2, 6);
//         func(functionSetings);
//     }
// }

void testInterface_userInput_setup(unsigned char settings[6]) {
    pinMode(4, OUTPUT);
    pinMode(A3, INPUT_PULLUP);

    pinMode(5, OUTPUT);
    pinMode(A4, INPUT_PULLUP);

    pinMode(6, OUTPUT);
    pinMode(A5, INPUT_PULLUP);
}

void testInterface_userInput(unsigned char settings[6]) {
    Serial.println(settings[0]);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
}