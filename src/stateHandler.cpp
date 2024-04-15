// #include "stateHandler.hpp"

// state stateHandler(unsigned char* message) {
//     if (true)    {
//         switch (message[0]) {
//             case PLACEHOLDER1:
//                 return STARTUP;
//                 break;
//             case PLACEHOLDER2:
//                 return STATE_1;
//                 break;
//             case PLACEHOLDER3:
//                 return STATE_2;
//                 break;
//             case PLACEHOLDER4:
//                 return STATE_3;
//                 break;
//             default:
//                 return IDLE;
//                 break;
//         }
//     }
// }

// bool stateChange(state &previous, state current) {
//     if (previous != current) {
//         previous = current;
//         return true;
//     } else {
//         return false;
//     }
// }