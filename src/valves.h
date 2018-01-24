#ifndef VALVES_H
#define VALVES_H
#include <application.h>

void setup_pins_valves();
int run_valve1(String command);
int run_valve2(String command);
void valve1(int command);
void valve2(int command);
void relays_off();
#endif
