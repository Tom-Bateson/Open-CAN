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
// adress...
#define PLACEHOLDER1   0x00
#define PLACEHOLDER2   0x01
#define PLACEHOLDER3   0x02
#define PLACEHOLDER4   0x03
// Define states...
enum state {
  STARTUP,
  STATE_1,
  STATE_3,
  STATE_2,
  ERROR,
  IDLE
};

#endif