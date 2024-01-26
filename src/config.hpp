#ifndef CONFIG_H
#define CONFIG_H

// hardware config
#define INT_PIN        2
#define CHIP_SELECT    10
// can bus config
#define CAN_SPEED      CAN_100KBPS
#define MCP_CLOCK      MCP_16MHZ
// address masking config
#define FILTER_MASK    0x03FF0000
#define FILTER_1_ID    0x01000000
#define FILTER_2_ID    0x01010000

#endif