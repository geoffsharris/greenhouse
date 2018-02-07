# include "vent.h"
# include "DualMC33926MotorShield.h"
# include "logic.h"
# include <application.h>

Vent roofVent = Vent(); // creates vent object
Vent sideVent = Vent(); // creates vent object

int motorFlag = 0; //1 for forward, 0 for stop, -1 for reverse
int secondCounter = 0;
extern int geoff;

Timer ventRunTimer(1000, positionCounter);
Timer indigoTimer(600000,indigoWatchdog);
Timer ventDelayTimer(10000, delayedVentOff);

 Vent :: Vent()
{
 _currentPosition = 1;
 _targetPosition = 1;
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

void Vent :: runVentMotor(int ventID, int currentPosition, int targetPosition)
{
  int direction = targetPosition - currentPosition;
  if (ventID == 0) // roofVent
  {
   // positive number will drive motor forward, negative backward
  if (direction >0)
    {
      motor.setM1Speed(255); // run motor forward
      motorFlag = 1;
      ventRunTimer.start();
      Particle.publish("log","roofVent motor forward");
    }
  else if (direction <0)
    {
      motor.setM1Speed(-255); // run motor backward
      motorFlag = -1;
      ventRunTimer.start();
      Particle.publish("log","roofVent motor reverse");
    }
  else if (direction == 0)
    {
      if (currentPosition == 1 || currentPosition == 6)
      {
        ventDelayTimer.start();
        //motor.setM1Speed(0); // stop motor
        motorFlag = 0;
        ventRunTimer.reset();
        ventRunTimer.stop();
        Particle.publish("log","roofVent motor stop delay");
      }
      else if (currentPosition > 1 && currentPosition < 6)
      {
        //ventDelayTimer.start();
        motor.setM1Speed(0); // stop motor
        motorFlag = 0;
        ventRunTimer.reset();
        ventRunTimer.stop();
        Particle.publish("log","roofVent motor stop");
      }
    }
  }
  else if (ventID == 1) // sideVent all variables need to be updated for second vent
  {
   if (direction >0)
     {
       motor.setM1Speed(255); // run motor forward
       motorFlag = 1;
       ventRunTimer.start();
       Particle.publish("log","sideVent motor forward");
     }
   else if (direction <0)
     {
       motor.setM1Speed(-255); // run motor backward
       motorFlag = -1;
       ventRunTimer.start();
       Particle.publish("log","sideVent motor reverse");
     }
   else if (direction == 0)
     {
       motor.setM1Speed(0); // run motor backward
       motorFlag = 0;
       ventRunTimer.reset();
       ventRunTimer.stop();
       Particle.publish("log","sideVent motor stopped");
     }
  }
  else
  {
    Particle.publish("log","Error in else runVentMotor");
  }
}



void setupVent()
{
  Particle.function("vent", messageVent); // used to pass target vent position from Indigo
  indigoTimer.start(); // timer start to make sure indigo data is loaded at least every 10 minutes
}

int messageVent(String passedTarget) // used to pass message from Indigo and set vent position
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
        roofVentValue = constrain(roofVentValue, 1, 6);
        roofVent.setTarget(roofVentValue);
        Particle.publish("roof position", roofVentString);
      }
      if (passedTarget.indexOf("sideVent") != -1)
      {
        int index = passedTarget.indexOf("sideVent");
        String sideVentString = passedTarget.substring(index+9,index+10);
        int sideVentValue = sideVentString.toInt();
        sideVentValue = constrain(sideVentValue, 1, 6);
        sideVent.setTarget(sideVentValue);
        Particle.publish("side position", sideVentString);
      }
      indigoTimer.reset();
    return 1;
    }
    else return -1;
}

void indigoWatchdog()
{
  int currentTime = Time.hour();
  int currentMonth = Time.month();
  if ((currentMonth >= 4) && currentMonth <=10)
  {
    if (currentTime >= 9 && currentTime <= 10)
    {
        roofVent.setTarget(2);
    }
    else if (currentTime >= 11 && currentTime <= 17)
    {
        roofVent.setTarget(3);
    }
    else
    {
        roofVent.setTarget(1);
    }
  }
  else if ((currentMonth <= 3) || currentMonth >=11)
  {
    if (currentTime >= 11 && currentTime <= 14)
    {
        roofVent.setTarget(3);
    }
    else
    {
        roofVent.setTarget(1);
    }
  }
  Particle.publish("log", "packet failure - using backup program", PRIVATE);
  indigoTimer.reset(); // reset timer so this gets called again if connection is not restored
}

void positionCounter()
{
  if (motorFlag == -1)
  {
    secondCounter--;
  }
  else if (motorFlag == 1)
  {
    secondCounter++;
  }
  if (secondCounter == 0)
  {
    roofVent.setCurrent(1);
    roofVent.runVentMotor(0,roofVent.current(),roofVent.target());
  }
  else if (secondCounter == 6)
  {
    roofVent.setCurrent(2);
    roofVent.runVentMotor(0,roofVent.current(),roofVent.target());
  }
  else if (secondCounter == 12)
  {
    roofVent.setCurrent(3);
    roofVent.runVentMotor(0,roofVent.current(),roofVent.target());
  }
  else if (secondCounter == 25)
  {
    roofVent.setCurrent(4);
    roofVent.runVentMotor(0,roofVent.current(),roofVent.target());
  }
  else if (secondCounter == 40)
  {
    roofVent.setCurrent(5);
    roofVent.runVentMotor(0,roofVent.current(),roofVent.target());
  }
  else if (secondCounter == 55)
  {
    roofVent.setCurrent(6);
    roofVent.runVentMotor(0,roofVent.current(),roofVent.target());
  }
  else if (secondCounter < 0)
  {
    Particle.publish("log", "you have an error in your code");
  }
  Particle.publish("motor is running", String(secondCounter));
  geoff = roofVent.current();
}

void delayedVentOff()
{
  motor.setM1Speed(0);
  motorFlag = 0;
  ventDelayTimer.reset();
  ventDelayTimer.stop(); // stop motor
}
