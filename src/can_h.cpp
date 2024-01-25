#include "can_h.hpp"

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

#define CAN0_INT 2          // Set INT to pin 2
MCP_CAN CAN0(10);           // Set CS to pin 10


void startCAN() {
    // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
    CAN0.begin(MCP_ANY, CAN_100KBPS, MCP_16MHZ);
    // Set operation mode to normal so the MCP2515 sends acks to received data.
    CAN0.setMode(MCP_NORMAL);                     
    // Configuring pin for /INT input
    pinMode(CAN0_INT, INPUT);                            
}

unsigned char* receiveCAN() {
    if (!digitalRead(CAN0_INT)) {
        CAN0.readMsgBuf(&rxId, &len, rxBuf);
    }
    return rxBuf;  // Return the pointer to rxBuf
}

void sendStandardCAN(byte data[8]) {
    // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
    byte sndStat = CAN0.sendMsgBuf(0x105, 0, 8, data);
    if(sndStat == CAN_OK){
        Serial.println("Message Sent Successfully!");
    } else {
        Serial.println("Error Sending Message...");
    }
}