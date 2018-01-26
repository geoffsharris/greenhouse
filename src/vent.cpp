# include "vent.h"
# include <application.h>

Vent roofVent; // creates vent object
Vent sideVent; // creates vent object

/*void Vent :: ventInit()
{
 _currentPosition = 0;
 _targetPosition = 0;
}
*/
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

void setupVent()
{
  Particle.function("passedTarget", messageVent); // used to pass target vent position from Indigo
}

int messageVent(String passedTarget) // used to pass message from Inigo and set vent position
{
    // Indigo should pass roof or side vent parameters in
    // sideVent=x, roofVent=y format
    // function will find variable name and pick up a single digit after =
    // will tolerate spaces and other characters between names

    if ((passedTarget.indexOf("roofVent") != -1) || (passedTarget.indexOf("sideVent") != -1))
    {
      if (passedTarget.indexOf("roofVent") != -1)
      {
        int index = passedTarget.indexOf("roofVent");
        String roofVentString = passedTarget.substring(index+9,index+10);
        int roofVentValue = roofVentString.toInt();
        roofVent.setTarget(roofVentValue);
        Particle.publish("roof position", roofVentString);
      }
      if (passedTarget.indexOf("sideVent") != -1)
      {
        int index = passedTarget.indexOf("sideVent");
        String sideVentString = passedTarget.substring(index+9,index+10);
        int sideVentValue = sideVentString.toInt();
        sideVent.setTarget(sideVentValue);
        Particle.publish("side position", sideVentString);
      }
    return 1;
    }
    else return -1;

}
