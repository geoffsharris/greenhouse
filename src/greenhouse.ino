/*
 * Project greenhouse
 * Description:
 * Author:
 * Date:
 */

 #include "valves.h"
 #include "vent.h"
 #include "DualMC33926MotorShield.h"

 SYSTEM_THREAD(ENABLED);
 STARTUP(WiFi.selectAntenna(ANT_INTERNAL));
 //Vent roofVent; now instantiated in header
 //Vent sideVent;
 //DualMC33926MotorShield motor = DualMC33926MotorShield(); now instantiated in header

 void setup() {

 setup_pins_valves();
 setupVent();

 }

 void loop() {

 }
