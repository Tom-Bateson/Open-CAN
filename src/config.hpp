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
// adress for states
#define STARTUP_ADR         0x00
#define RUN_ADR             0x01
#define WAIT_ADR            0x02
#define PLACEHOLDER_ADR_1   0x03
#define PLACEHOLDER_ADR_2   0x04
#define PLACEHOLDER_ADR_3   0x05
// Define states
enum state {
  STARTUP,
  RUN,
  WAIT,
  STATE_PLACEHOLDER_1,
  STATE_PLACEHOLDER_2,
  STATE_PLACEHOLDER_3,
  ERROR
};

#endif