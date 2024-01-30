#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include "config.hpp"

state stateHandler(unsigned char* message);
bool stateChange(state &previous, state &current);

#endif