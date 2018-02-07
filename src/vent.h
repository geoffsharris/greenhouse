#ifndef VENT_H
#define VENT_H
#include <application.h>
#include "DualMC33926MotorShield.h"
class Vent
{
 public:
 // constructors
 Vent();

 // methods

 void setTarget(int targetPosition);
 void setCurrent(int currentPosition);
 unsigned int current();
 unsigned int target();
 void runVentMotor(int ventID, int currentPosition, int targetPosition);
 // variables


// private:
 int _currentPosition;
 int _targetPosition;

};

int messageVent(String command);
void setupVent();
void indigoWatchdog();
void positionCounter();
void delayedVentOff();
extern Vent roofVent;
extern Vent sideVent;

#endif
