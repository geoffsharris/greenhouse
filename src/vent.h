#ifndef VENT_H
#define VENT_H
//#include <application.h>
class Vent
{
 public:
 // constructors
 void ventInit();

 // methods
 void setTarget(int targetPosition);
 void setCurrent(int currentPosition);
 unsigned int current();
 unsigned int target();
 // variables


// private:
 int _currentPosition;
 int _targetPosition;

};

//extern Vent vent;

#endif
