#ifndef VALVES_H
#define VALVES_H
#include <application.h>

void setup_pins_valves();
int message(String command);
void valves(int fertilizer,int RO);
void relays_off();
#endif
