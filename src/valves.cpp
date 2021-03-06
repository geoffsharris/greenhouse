# include "valves.h"
# include <application.h>

// set pins for valve control
int relayPower = D0; // used to allow valves to move, controls power to valve relays
int relayFertilizer = D1; // high = RO water, low = tap water
int relayRO = D2; // high = fertilizer on, low = fertilizer off
int input_ferlizier_on = D3; // valve 1 open when low
int input_ferlizier_off = D4; // valve 1 closed when low
int input_RO_on = D5; // valve 2 open when low
int input_RO_off = D6; // valve 1 closed when low

// initialize variables for
int fertilizerStatus = 0; // 0 = on, 1 = off
int ROStatus = 0; // 0 = on, 1 = off
int fertilizerReply = 0;
int ROReply = 0;
int ROValveOnInteruptFlag = 0;
int ROValveOffInteruptFlag = 0;
int FertilizerValveOnInteruptFlag = 0;
int FertilizerValveOffInteruptFlag = 0;

Timer relayTimer(15000, relaysOff);
Timer debounceROValveTimer(100, debounceROValve);
Timer debounceFertValveTimer(100, debounceFertValve);

//setup for program input pins to check status of valves
void setupPinsValves()
{
  pinMode(relayPower, OUTPUT);
  pinMode(relayFertilizer, OUTPUT);
  pinMode(relayRO, OUTPUT);
  pinMode(input_ferlizier_on, INPUT_PULLDOWN);
  pinMode(input_ferlizier_off, INPUT_PULLDOWN);
  pinMode(input_RO_on, INPUT_PULLDOWN);
  pinMode(input_RO_off, INPUT_PULLDOWN);
  digitalWrite(relayFertilizer, HIGH);
  digitalWrite(relayRO, HIGH);
  digitalWrite(relayPower, HIGH);

  // attach interupts
  attachInterrupt(input_ferlizier_on, fertilizerOnFlag, RISING);
  attachInterrupt(input_ferlizier_off, fertilizerOffFlag, RISING);
  attachInterrupt(input_RO_on, ROOnFlag, RISING);
  attachInterrupt(input_RO_off, ROOffFlag, RISING);

  // set up function called by Indigo to control valves
  Particle.function("valves", messageValves);
  Particle.variable("fertPosit", fertilizerReply);
  Particle.variable("ROPosit", ROReply);
  valves(fertilizerStatus, ROStatus); // call function to set valves to startup position
}

int messageValves(String command)
{

  if ((command.indexOf("RO") != -1) || (command.indexOf("Fertilizer") != -1))
  {
    if (command.indexOf("RO") != -1)
    {
      int index = command.indexOf("RO");
      Particle.publish("RO valve", command.substring(index+3,index+6));
      if (command.substring(index+3,index+5) == "on")
      {
         ROStatus = 0;
      }
      else if (command.substring(index+3,index+6) == "off")
      {
        ROStatus = 1;
      }
      else return -1;
    }
    if (command.indexOf("Fertilizer") != -1)
    {
      int index = command.indexOf("Fertilizer");
      Particle.publish("Fert valve", command.substring(index+11,index+14));
      if (command.substring(index+11,index+13) == "on")
      {
        fertilizerStatus = 0;
      }
      else if (command.substring(index+11,index+14) == "off")
      {
        fertilizerStatus = 1;
      }
      else return -1;
    }
    Particle.publish("valves was called");
    valves(fertilizerStatus, ROStatus);
    return 1;
  }
  else return -1;
}


void valves(int fertilizer,int RO)
{
    if (fertilizer == 0)
    {
      digitalWrite(relayFertilizer, LOW);
    }
    else if (fertilizer == 1)
    {
      digitalWrite(relayFertilizer, HIGH);
    }
    else
    {
        //log error TBD
    }
    if (RO == 0)
    {
      digitalWrite(relayRO, LOW);
    }
    else if (RO == 1)
    {
      digitalWrite(relayRO, HIGH);
    }
    else
    {
        //log error TBD
    }
    digitalWrite(relayPower, LOW);
    relayTimer.start();

}

void relaysOff()
{
    digitalWrite(relayPower, HIGH);
    digitalWrite(relayFertilizer, HIGH);
    digitalWrite(relayRO, HIGH);
    int _fertilizer_on = digitalRead(input_ferlizier_on);
    int _fertilizer_off = digitalRead(input_ferlizier_off);
    int _RO_on = digitalRead(input_RO_on);
    int _RO_off = digitalRead(input_RO_off);
    if (_fertilizer_on == HIGH && _fertilizer_off == LOW)
    {
        Particle.publish("message", "Fertilizer on");
        fertilizerReply = 1;
    }
    else if (_fertilizer_on == LOW && _fertilizer_off == HIGH)
    {
        Particle.publish("message", "Fertilizer off");
        fertilizerReply = 0;
    }
    else
    {
        Particle.publish("message", "failed");
    }
    if (_RO_on == HIGH && _RO_off == LOW)
    {
        Particle.publish("message", "RO on");
        ROReply = 1;
    }
    else if (_RO_on == LOW && _RO_off == HIGH)
    {
        Particle.publish("message", "RO off");
        ROReply = 0;
    }
    else
    {
        Particle.publish("message", "failed");
    }
    relayTimer.reset();
    relayTimer.stop();
}

void fertilizerOnFlag()
{
 FertilizerValveOnInteruptFlag = 1;
}

void fertilizerOffFlag()
{
 FertilizerValveOffInteruptFlag = 1;
}

void ROOnFlag()
{
 ROValveOnInteruptFlag = 1;
}

void ROOffFlag()
{
 ROValveOffInteruptFlag = 1;
}

void debounceROValve()
{
 int ROOnVal = digitalRead(input_RO_on);
 int ROOffVal = digitalRead(input_RO_off);

 if (ROOnVal == HIGH && ROOffVal == LOW)
 {
   Particle.publish("ValveRO", "on");
 }
 if (ROOnVal == LOW && ROOffVal == HIGH)
 {
   Particle.publish("ValveRO", "off");
 }
 debounceROValveTimer.reset();
 debounceROValveTimer.stop();
}

void debounceFertValve()
{
 int FertOnVal = digitalRead(input_ferlizier_on);
 int FertOffVal = digitalRead(input_ferlizier_off);

 if (FertOnVal == HIGH && FertOffVal == LOW)
 {
   Particle.publish("ValveFert", "on");
 }
 if (FertOnVal == LOW && FertOffVal == HIGH)
 {
   Particle.publish("ValveFert", "off");
 }
 debounceFertValveTimer.reset();
 debounceFertValveTimer.stop();
}
