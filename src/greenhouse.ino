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
 Vent roofVent;
 Vent sideVent;

 void setup() {

 setup_pins_valves();

 }

 void loop() {

 }
