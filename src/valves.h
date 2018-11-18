#ifndef VALVES_H
#define VALVES_H
#include <application.h>

void setupPinsValves();
int messageValves(String command);
void valves(int fertilizer,int RO);
void relaysOff();
void fertilizerOnFlag();
void fertilizerOffFlag();
void ROOnFlag();
void ROOffFlag();
void debounceROValve();
void debounceFertValve();
#endif
