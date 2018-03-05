# include "watermeter.h"
# include <application.h>

retained int waterMeterCount = 0;
int waterMeterPin = D7;

void setupWaterMeter()
{
   pinMode(waterMeterPin, INPUT_PULLUP);
   attachInterrupt(waterMeterPin, waterMeterCounter, CHANGE);
   Particle.variable("H2Ocount", waterMeterCount);
   Particle.function("H2Oreset", waterMeterCounterReset);
}

void waterMeterCounter()
{
  waterMeterCount ++;
}

int waterMeterCounterReset(String command)
{
  waterMeterCount = 0;
  return 1;
}
