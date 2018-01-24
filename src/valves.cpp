# include "valves.h"
# include <application.h>

int relay_power = D0; // used to allow valves to move, controls power to valve relays
int relay_fertilizer = D1; // high = RO water, low = tap water
int relay_RO = D2; // high = fertilizer on, low = fertilizer off
int input_ferlizier_on = D3; // valve 1 open when low
int input_ferlizier_off = D4; // valve 1 closed when low
int input_RO_on = D5; // valve 2 open when low
int input_RO_off = D6; // valve 1 closed when low

//setup for program input pins to check status of valves
int fertilizer_status = 0; // true = position1, false = running or position 2
int RO_status = 0; // true = position2, false = running or position 1

Timer relay_timer(15000, relays_off);

void setup_pins_valves()
    {
        pinMode(relay_power, OUTPUT);
        pinMode(relay_fertilizer, OUTPUT);
        pinMode(relay_RO, OUTPUT);
        pinMode(input_ferlizier_on, INPUT_PULLUP);
        pinMode(input_ferlizier_off, INPUT_PULLUP);
        pinMode(input_RO_on, INPUT_PULLUP);
        pinMode(input_RO_off, INPUT_PULLUP);
        digitalWrite(relay_fertilizer, HIGH);
        digitalWrite(relay_RO, HIGH);
        digitalWrite(relay_power, HIGH);

        Particle.function("command", message);
        valves(RO_status,fertilizer_status); // call function to set valves to startup position
    }

int message(String command)
{

  if(command == "RO=on")
  {
    RO_status = 0;
    //valve1(0);
  }
  else if(command == "RO=off")
  {
    RO_status = 1;
    //valve1(1);
  }
  else if(command == "Fertilizer=on")
  {
    fertilizer_status = 0;
    //valve2(0);
  }
  else if(command == "Fertilizer=off")
  {
    fertilizer_status = 1;
    //valve2(1);
  }
  else return -1;
  valves(RO_status,fertilizer_status);
  return 1;

}


void valves(int fertilizer,int RO)
{
    if (fertilizer == 0)
    {
        digitalWrite(relay_fertilizer, LOW);
    }
    else if (fertilizer == 1)
    {
        digitalWrite(relay_fertilizer, HIGH);
    }
    else
    {
        //log error TBD
    }
    if (RO == 0)
    {
        digitalWrite(relay_RO, LOW);
    }
    else if (RO == 1)
    {
        digitalWrite(relay_RO, HIGH);
    }
    else
    {
        //log error TBD
    }
    digitalWrite(relay_power, LOW);
    relay_timer.start();

}

void relays_off()
{
    digitalWrite(relay_power, HIGH);
    digitalWrite(relay_fertilizer, HIGH);
    digitalWrite(relay_RO, HIGH);
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
            Particle.publish("message", "fertilizer on");
        }
        else if (_RO_on == HIGH && _RO_off == LOW)
        {
            Particle.publish("message", "fertilizer off");
        }
        else
        {
            Particle.publish("message", "failed");
        }
        relay_timer.reset();
        relay_timer.stop();
}
