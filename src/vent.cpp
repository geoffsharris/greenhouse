# include "vent.h"
//# include <application.h>

//Vent vent; // creates vent object


void Vent :: ventInit()
{
 _currentPosition = 0;
 _targetPosition = 0;
}

void Vent :: setTarget(int targetPosition)
 {
 _targetPosition = targetPosition;
 }

 void Vent :: setCurrent(int currentPosition)
 {
 _currentPosition = currentPosition;
 }

unsigned int Vent :: current()
{
    return _currentPosition;
}

unsigned int Vent :: target()
{
    return _targetPosition;
}
