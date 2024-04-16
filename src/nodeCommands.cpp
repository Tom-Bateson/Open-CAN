#include "config.hpp"
#include "canFunctions.hpp"
#include "nodeCommands.hpp"

byte& systemState::State() {
    static byte state;
    return state;
}

// Create a map to associate function pointers with values
std::map<byte, FunctionPtr> functionDictionary = {
    {0x10, setState},
    {0x20, handelUserInput_wiperSeting},
    {0x30, exampleNodeFunction}
};

void runNodeCommand(unsigned char command[8]) {
    // Find the function pointer associated with the variable
    auto funcId = functionDictionary.find(command[1]);
    if (funcId != functionDictionary.end() && command[0] == 0x01) {
        // cut the function id and start/stop from the mesage to leave the function steings
        unsigned char functionSetings[6];
        memcpy(functionSetings, command + 2, 6);
        // Call the function using the function pointer
        FunctionPtr func = funcId->second;
        func(functionSetings);
    } else {
        // Handle invalid funcid
        Serial.print("Function dose not exist: ");
        Serial.println(command[1]);
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


void handelUserInput_wiperSeting(unsigned char settings[6]) {
    // mesage arrays
    unsigned char response_sensor[8] = {0x01, 0x20, 0x10, 0x00, 0x00, 0x00, 0xff, 0x01};
    unsigned char response_motor[8] = {0x01, 0x00, 0x10, 0x00, 0x00, 0x00, 0xff, 0x01};


    switch (settings[0])
    {
    case 0x00:
        response_sensor[0] = 0x00;
        response_motor[1] = 0x20;
        break;
    case 0x01:
        response_sensor[0] = 0x00;
        response_motor[1] = 0x21;
        break;
    case 0x02:
        response_sensor[0] = 0x01;
        break;
    }

    // send can mesage to sensor node
    sendStandardCAN(0x203, response_sensor);

    // send can mesage to motor node
    sendStandardCAN(0x205, response_motor);

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
    Serial.println(settings[4]+settings[5],HEX);
}