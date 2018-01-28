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

SYSTEM_THREAD(ENABLED);
STARTUP(WiFi.selectAntenna(ANT_INTERNAL));
//Vent roofVent; now instantiated in header
//Vent sideVent; now instantiated in header
//DualMC33926MotorShield motor = DualMC33926MotorShield(); now instantiated in header


void setup()
 {
   setupPinsValves();
   setupVent();
   setupLogic();
   Time.zone(-8);
 }

void loop()
{
  //checkLogic();
}
