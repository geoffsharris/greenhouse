# include "valves.h"
# include <application.h>

int relay_power = D0; // used to allow valves to move, controls power to valve relays
int relay_valve1 = D1; // high = RO water, low = tap water
int relay_valve2 = D2; // high = fertilizer on, low = fertilizer off
int input_valve1_closed = D3; // valve 1 open when low
int input_valve1_open = D4; // valve 1 closed when low
int input_valve2_closed = D5; // valve 2 open when low
int input_valve2_open = D6; // valve 1 closed when low

//setup for program input pins to check status of valves
int position1_valve1; // true = position1, false = running or position 2
int position2_valve1; // true = position2, false = running or position 1
int position1_valve2; // true = position1, false = running or position 2
int position2_valve2; // true = position2, false = running or position 1

Timer relay1_timer(15000, relays_off);
Timer relay2_timer(15000, relays_off);


void setup_pins_valves()
    {
        pinMode(relay_power, OUTPUT);
        pinMode(relay_valve1, OUTPUT);
        pinMode(relay_valve2, OUTPUT);
        pinMode(input_valve1_closed, INPUT_PULLUP);
        pinMode(input_valve1_open, INPUT_PULLUP);
        pinMode(input_valve2_closed, INPUT_PULLUP);
        pinMode(input_valve2_open, INPUT_PULLUP);
        digitalWrite(relay_valve1, HIGH);
        digitalWrite(relay_valve2, HIGH);
        digitalWrite(relay_power, HIGH);

        Particle.function("water", run_valve1);
        Particle.function("fertilizer", run_valve2);
    }

int run_valve1(String command)
{
  if(command == "RO")
  {

    valve1(0);
    return 1;
  }
  else if(command == "TAP")
  {
    valve1(1);
    return 1;
  }
  else return -1;
}

int run_valve2(String command)
{
  if(command == "on")
  {

    valve2(0);
    return 1;
  }
  else if(command == "off")
  {
    valve2(1);
    return 1;
  }
  else return -1;
}


void valve1(int command)
{
    if (command == 0)
    {
        digitalWrite(relay_valve1, LOW);
        digitalWrite(relay_power, LOW);
        relay1_timer.start();
    }
    else if (command == 1)
    {
        digitalWrite(relay_valve1, HIGH);
        digitalWrite(relay_power, LOW);
        relay1_timer.start();
    }
    else
    {
        //log error TBD
    }

}

void valve2(int command)
{
    if (command == 0)
    {
        digitalWrite(relay_valve2, LOW);
        digitalWrite(relay_power, LOW);
        relay2_timer.start();
    }
    else if (command == 1)
    {
        digitalWrite(relay_valve2, HIGH);
        digitalWrite(relay_power, LOW);
        relay2_timer.start();
    }
    else
    {
        //log error TBD
    }

}

void relays_off()
{
    digitalWrite(relay_power, HIGH);
    digitalWrite(relay_valve1, HIGH);
    digitalWrite(relay_valve2, HIGH);
    int valve1_sensor_open = digitalRead(input_valve1_open);
    int valve1_sensor_closed = digitalRead(input_valve1_closed);
    int valve2_sensor_open = digitalRead(input_valve2_open);
    int valve2_sensor_closed = digitalRead(input_valve2_closed);
        if (valve1_sensor_open == LOW && valve1_sensor_closed == HIGH)
        {
            Particle.publish("message", "RO set");
        }
        else if (valve1_sensor_open == HIGH && valve1_sensor_closed == LOW)
        {
            Particle.publish("message", "TAP set");
        }
        else
        {
            Particle.publish("message", "failed");
        }
        if (valve2_sensor_open == LOW && valve2_sensor_closed == HIGH)
        {
            Particle.publish("message", "fertilizer on");
        }
        else if (valve2_sensor_open == HIGH && valve2_sensor_closed == LOW)
        {
            Particle.publish("message", "fertilizer off");
        }
        else
        {
            Particle.publish("message", "failed");
        }
        relay1_timer.reset();
        relay1_timer.stop();
        relay2_timer.reset();
        relay2_timer.stop();
}
