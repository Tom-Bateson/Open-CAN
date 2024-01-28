#ifndef CANFUNCTIONS_H
#define CANFUNCTIONS_H

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>

void startCAN();
unsigned char* receiveCAN();
void sendStandardCAN(unsigned int address, byte data[8]);

#endif