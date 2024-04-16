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
    {0x20, testInterface_wiperMotorOnce},
    {0x21, testInterface_wiperMotorSeting},
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

void testInterface_wiperMotor_setup() {
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
}

// finctions for testInterface_wiperMotorOnce & testInterface_wiperMotorSeting
unsigned long previousMillis = 0;

void testInterface_wiperMotorOnce(unsigned char settings[6]) {
    // Get the current time
    unsigned long currentMillis = millis();

    unsigned long interval = 10 * settings[0];

    if (currentMillis - previousMillis >= interval) {
        // Save the last time a mesage was sent
        previousMillis = currentMillis;
        
        digitalWrite(5, HIGH);
    }


}

void testInterface_wiperMotorSeting(unsigned char settings[6]) {
    // Get the current time
    unsigned long currentMillis = millis();

    unsigned long interval = 10 * settings[0];

    // set indecator leds to off
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);

    Serial.println("KILL YOURSELF S");

    // switch (settings[1])
    // {
    // case 0x00:
    //     digitalWrite(6, HIGH);
    //     break;
    // case 0x01:
    //     digitalWrite(5, HIGH);
    //     break;
    // case 0x02:
    //     digitalWrite(4, HIGH);
    //     break;
    // }


    // if (once == true) {
    //     response[2] = 0x00;
    //     digitalWrite(6, HIGH);
    // } else if (auto_on == false) {
    //     response[2] = 0x01;
    //     digitalWrite(5, HIGH);
    // } else if (auto_on == true) {
    //     response[2] = 0x02;
    //     digitalWrite(4, HIGH);
    // }
    
    if (currentMillis - previousMillis >= interval) {
        // Save the last time a mesage was sent
        previousMillis = currentMillis;
        // send can mesage with user imput state
        // sendStandardCAN(0x005, response);
    }
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