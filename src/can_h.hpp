#ifndef MCP_CAN_FUNCTIONS_H
#define MCP_CAN_FUNCTIONS_H

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>



void startCAN();
unsigned char* receiveCAN();
void sendStandardCAN(byte data[8]);

#endif // MCP_CAN_FUNCTIONS_H

