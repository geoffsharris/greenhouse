# include "logic.h"
# include "vent.h"
# include "DualMC33926MotorShield.h"
# include <application.h>
# define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)

extern int motorFlag; //1 for forward, 0 for stop, -1 for reverse
int geoff = 1; // part of testing functions below for removal
int geoff2 = 1; // part of testing functions below for removal
extern int secondCounter;
Timer logicTimer(15000, checkPosition); // timer to call function check if vent is in correct position
Timer synchTime(ONE_DAY_MILLIS, synchClock); // timer to synch clock every 24 hrs
//Timer ventRunTimer(1000, positionCounter); // timer to count seconds that vent motor is running


void setupLogic()
{
  Particle.variable("roofcurrent", geoff); // for testing to remove
  Particle.variable("rooftarget", geoff2); // for testing to remove
  Particle.function("currentRoof", positionTesting); // for testing to remove
  roofVent.setTarget(1); // initialize vent target at 1 closed

  // run motor in reverse to make sure vent is closed on startup
  motorFlag = -1; // set motor flag for reverse run to close vent at startup
  motor.setM1Speed(-255); // run motor for 60 sec to make sure it is closed at startup
  delay(5000); //set to 60000 once testing done
  motor.setM1Speed(0); // set motor to off
  logicTimer.start(); // start timer that checks position logic every 60 seconds
  secondCounter = 0; // set second counter used for position tracking at 0 which is closed position
  motorFlag = 0; // set motor flag for to 0
  // motor set up complete

  Particle.publish("setup complete");
}

int positionTesting(String command) // for testing to send positions
{
  int positionTest = command.toInt(); // convert sting to int for manipulation
  roofVent.setCurrent(positionTest); // pass message to roofVent
  Particle.publish("positionCurrent called", String(roofVent.current()));
  geoff = roofVent.current();
  return 1;
}

void synchClock()
{
  Particle.syncTime();
  if (Time.isDST() == true)
  {
    Time.zone(-7);
  }
  else
  {
    Time.zone(-8);
  }

}

void checkPosition() // called ever x seconds by timer to check position
                      // logic to run motors and establish positions should be implemented here
{
   //Particle.publish("vent actions"); // for testing

   if (roofVent.current() != roofVent.target() && motorFlag != 0)
   {
     Particle.publish("log","motor running");
   }
   else if (roofVent.current() == roofVent.target() && motorFlag == 0)
   {
     Particle.publish("log","everything is good");
   }
   else if ((roofVent.current() != roofVent.target() && motorFlag == 0) || (roofVent.current() == roofVent.target() && motorFlag != 0))
   {
     roofVent.runVentMotor(0, roofVent.current(), roofVent.target());
     Particle.publish("log","trigger motor program" );
   }
   else
   {
     Particle.publish("log","else Error in vent position check:");
   }
}    // end positionCheck





/*void positionCounter()
{
  Particle.publish("motor is running", String(secondCounter));
  if (motorFlag == -1)
  {
    secondCounter--;
  }
  else if (motorFlag == 1)
  {
    secondCounter++;
  }
}*/
/*void checkLogic()
{
if (motorFlag != 0)
  {
    if (secondCounter == 0)
    {
      roofVent.setCurrent(1);
    }
    else if (secondCounter == 6)
    {
      roofVent.setCurrent(2);
    }
    else if (secondCounter == 12)
    {
      roofVent.setCurrent(3);
    }
    else if (secondCounter == 25)
    {
      roofVent.setCurrent(4);
    }
    else if (secondCounter == 40)
    {
      roofVent.setCurrent(5);
    }
    else if (secondCounter == 55)
    {
      roofVent.setCurrent(6);
    }
    geoff = roofVent.current();
    checkPosition(); // for testing purposes
  }
}
*/
