# include "watermeter.h"
# include <application.h>

retained int waterMeterCount = 0;
int waterMeterPin = D7;
int waterMeterInteruptFlag = 0;
Timer debounceWaterMeterTimer(100, debounceWaterMeter);

void setupWaterMeter()
{
   pinMode(waterMeterPin, INPUT_PULLDOWN);
   attachInterrupt(waterMeterPin, waterMeterCounterFlag, RISING);
   Particle.variable("H2Ocount", waterMeterCount);
   Particle.function("H2Oreset", waterMeterCounterReset);
}

void waterMeterCounterFlag()
{
 waterMeterInteruptFlag = 1;
}

int waterMeterCounterReset(String command)
{
  waterMeterCount = 0;
  return 1;
}

void debounceWaterMeter()
{
 int val = digitalRead(waterMeterPin);
 if (val == HIGH)
 {
   waterMeterCount ++;
   Particle.publish("ValveRO", "off");
   debounceWaterMeterTimer.reset();
   debounceWaterMeterTimer.stop();
 }
}
