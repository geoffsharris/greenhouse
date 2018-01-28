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

Timer relayTimer(15000, relaysOff);

//setup for program input pins to check status of valves
void setupPinsValves()
{
  pinMode(relayPower, OUTPUT);
  pinMode(relayFertilizer, OUTPUT);
  pinMode(relayRO, OUTPUT);
  pinMode(input_ferlizier_on, INPUT_PULLUP);
  pinMode(input_ferlizier_off, INPUT_PULLUP);
  pinMode(input_RO_on, INPUT_PULLUP);
  pinMode(input_RO_off, INPUT_PULLUP);
  digitalWrite(relayFertilizer, HIGH);
  digitalWrite(relayRO, HIGH);
  digitalWrite(relayPower, HIGH);
  // set up function called by Indigo to control valves
  Particle.function("valves", messageValves);
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
    if (_fertilizer_on == LOW && _fertilizer_off == HIGH)
    {
        Particle.publish("message", "Fertilizer on");
    }
    else if (_fertilizer_on == HIGH && _fertilizer_off == LOW)
    {
        Particle.publish("message", "Fertilizer off");
    }
    else
    {
        Particle.publish("message", "failed");
    }
    if (_RO_on == LOW && _RO_off == HIGH)
    {
        Particle.publish("message", "RO on");
    }
    else if (_RO_on == HIGH && _RO_off == LOW)
    {
        Particle.publish("message", "RO off");
    }
    else
    {
        Particle.publish("message", "failed");
    }
    relayTimer.reset();
    relayTimer.stop();
}
