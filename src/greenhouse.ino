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

}

/*int geofftest(String command)
{
  return 1;
}
*/
