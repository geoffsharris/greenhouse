/*
 * Project greenhouse
 * Description:
 * Author:
 * Date:
 */

 #include "valves.h"

 SYSTEM_THREAD(ENABLED);
 STARTUP(WiFi.selectAntenna(ANT_INTERNAL));

 void setup() {

 setup_pins_valves();

 }

 void loop() {

 }
