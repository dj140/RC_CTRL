#ifndef __SBUS_H
#define __SBUS_H
//#include "FileGroup.h"
#include "Arduino.h"



void sbusPreparePacket(uint8_t packet[], uint16_t channels[], uint8_t isSignalLoss, uint8_t isFailsafe);


#endif

