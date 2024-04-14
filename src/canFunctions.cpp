#include "canFunctions.hpp"
#include "config.hpp"

long unsigned int rxId;
unsigned char len;
// unsigned char rxBuf[8];
unsigned char rxBuf_Old[8];

#define CAN0_INT INT_PIN                            // Set INT pin
MCP_CAN CAN0(CHIP_SELECT);                          // Set CS pin 

void startCAN() {
    // Initialize MCP2515 running at 16MHz with a baudrate of 100kb/s and the masks and filters disabled
    CAN0.begin(MCP_STDEXT, CAN_SPEED, MCP_CLOCK);
    // set both masks to check all adress bits
    CAN0.init_Mask(0,0,FILTER_MASK);                // Init first mask...
    CAN0.init_Mask(1,0,FILTER_MASK);                // Init second mask... 
    // set filters to allow adresses for device
    CAN0.init_Filt(0,0,FILTER_1_ID);                // Init first filter...
    CAN0.init_Filt(1,0,FILTER_2_ID);                // Init second filter...
    // Set operation mode to normal so the MCP2515 sends acks to received data
    CAN0.setMode(MCP_NORMAL);   

    // CAN0.enOneShotTX(); 

    // Configuring pin for /INT input
    pinMode(CAN0_INT, INPUT);     

    // send, receve & error LED pins
    pinMode(7, OUTPUT);
    pinMode(9, OUTPUT);  
    pinMode(3, OUTPUT);                      
}

bool receiveCAN(unsigned char rxBuf[8]) {

    memcpy(rxBuf_Old, rxBuf, 8); // Copy the contents of rxBuf into rxBuf_Old

    if (!digitalRead(CAN0_INT)) {
        CAN0.readMsgBuf(&rxId, &len, rxBuf);
    }

    bool change = memcmp(rxBuf_Old, rxBuf, 8) != 0;

    if (change)
    {
        digitalWrite(7, HIGH);
        delay(10);
        digitalWrite(7, LOW);
    }

    return change;
}

void sendStandardCAN(unsigned int address, byte data[8]) {
    
    while (CAN0.sendMsgBuf(address, 0, 8, data) != CAN_OK) {
        Serial.println("Error Sending Message...");
        digitalWrite(3, HIGH);
        delay(10);
    }

    Serial.println("Message Sent Successfully!");
    digitalWrite(3, LOW);
    digitalWrite(9, HIGH);
    delay(10);
    digitalWrite(9, LOW);
    
    // byte sndStat = CAN0.sendMsgBuf(0x001, 0, 8, data);
    // if(sndStat == CAN_OK){
    //     Serial.println("Message Sent Successfully!");
    // } else {
    //     Serial.println("Error Sending Message...");
    // }
}