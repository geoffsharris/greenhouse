/*
 * Project greenhouse
 * Description:
 * Author:
 * Date:
 */

#include "valves.h"
#include "vent.h"
#include "DualMC33926MotorShield.h"
#include "logic.h"
#include "watermeter.h"

SYSTEM_THREAD(ENABLED);
STARTUP(WiFi.selectAntenna(ANT_INTERNAL));
//Vent roofVent; now instantiated in header
//Vent sideVent; now instantiated in header
//DualMC33926MotorShield motor = DualMC33926MotorShield(); now instantiated in header
extern int waterMeterInteruptFlag;
extern Timer debounceWaterMeterTimer;
extern int waterMeterInteruptFlag;

void setup()
 {
   setupPinsValves();
   setupWaterMeter();
   setupVent();
   motor.init();
   setupLogic();
   Time.zone(-8);
   //Particle.function("reset", geofftest);
 }

void loop()
{
  if (waterMeterInteruptFlag == 1)
  {
    debounceWaterMeterTimer.start();
    waterMeterInteruptFlag = 0;
  }

  if (ROValveOnInteruptFlag == 1 || ROValveOffInteruptFlag == 1)
  {
    debounceROValveTimer.start();
    ROValveOnInteruptFlag = 0;
    ROValveOffInteruptFlag = 0;
  }

  if (FertilizerValveOnInteruptFlag == 1 || FertilizerValveOffInteruptFlag == 1)
  {
    debounceFertValveTimer.start();
    FertilizerValveOnInteruptFlag = 0;
    FertilizerValveOffInteruptFlag = 0;
  }
}
