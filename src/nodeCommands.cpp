#include "config.hpp"
#include "nodeCommands.hpp"

byte& systemState::State() {
    static byte state;
    return state;
}

// Create a map to associate function pointers with values
std::map<byte, FunctionPtr> functionDictionary = {
    {0x10, setState},
    {0x20, testInterface_userInput},
    {0x30, exampleNodeFunction}
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
        Serial.print("Function dose not exist: ");
        Serial.println(command[0]);
    }
}

void setState(unsigned char settings[6]) {
    switch (settings[0]) {
        case STARTUP_ADR:
            systemState::State() = STARTUP;
            break;
        case RUN_ADR:
            systemState::State() = RUN;
            break;
        case WAIT_ADR:
            systemState::State() = WAIT;
            break;
        case PLACEHOLDER_ADR_1:
            systemState::State() = STATE_PLACEHOLDER_1;
            break;
        case PLACEHOLDER_ADR_2:
            systemState::State() = STATE_PLACEHOLDER_2;
            break;
        case PLACEHOLDER_ADR_3:
            systemState::State() = STATE_PLACEHOLDER_3;
            break;
        default:
            systemState::State() = ERROR;
            break;
    }
}

void testInterface_userInput_setup() {
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

// this is an example function not for use in a program, it outputs the function setings and function return asress
void exampleNodeFunction(unsigned char settings[6]) {
    Serial.print("EXAMPLE FUNCTION OUTPUT - FUNCTION SETINGS: ");
    Serial.print(settings[0]);
    Serial.print(" : ");
    Serial.print(settings[1]);
    Serial.print(" : ");
    Serial.print(settings[2]);
    Serial.print(" : ");
    Serial.print(settings[3]);
    Serial.print(" : RETURN ADR : ");
    Serial.print(settings[4]+settings[5],HEX);
}