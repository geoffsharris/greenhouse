#ifndef VALVES_H
#define VALVES_H
#include <application.h>

void setupPinsValves();
int messageValves(String command);
void valves(int fertilizer,int RO);
void relaysOff();
#endif
