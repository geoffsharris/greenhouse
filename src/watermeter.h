#ifndef WATERMETER_H
#define WATERMETER_H
#include <application.h>

void setupWaterMeter();
void waterMeterCounterFlag();
int waterMeterCounterReset(String command);
void debounceWaterMeter();
#endif
