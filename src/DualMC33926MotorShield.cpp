#include "application.h"
#include "DualMC33926MotorShield.h"
// creates object called motor that can be used to call public functions
// call motor.init() in setup() to map and define input and output pins

// Constructors ////////////////////////////////////////////////////////////////

DualMC33926MotorShield::DualMC33926MotorShield() // called to set up pin map for motor functions
{
  //Default Pin map these should be set differently for the core vs. photon
  _EN = A2;
  _M1IN1 = A4; // PWM
  _M1IN2 = A5; // PWM
  //_M2IN1 = D2; // PWM
  //_M2IN2 = D3; // PWM
  _nSF = A1;
  _M1FB = A0;
  //_M2FB = A1;
}


DualMC33926MotorShield::DualMC33926MotorShield(unsigned char M1IN1, unsigned char M1IN2, unsigned char M1FB,
                           /*unsigned char M2IN1, unsigned char M2IN2, unsigned char M2FB,*/
                           unsigned char EN, unsigned char nSF)
{
  //Pin map set manually if default not desired
  _EN = EN;
  _M1IN1 = M1IN1;
  _M1IN2 = M1IN2;
  //_M2IN1 = M2IN1;
  //_M2IN2 = M2IN2;
  _nSF = nSF;
  _M1FB = M1FB;
  //_M2FB = M2FB;
}

// Public Methods //////////////////////////////////////////////////////////////
void DualMC33926MotorShield::init()
{
// Define pinMode for the pins, called as part of setup in main program

  pinMode(_M1IN1,OUTPUT);
  pinMode(_M1IN2,OUTPUT);
  pinMode(_M1FB,INPUT);
  //pinMode(_M2IN1,OUTPUT);
  //pinMode(_M2IN1,OUTPUT);
  //pinMode(_M2FB,INPUT);
  pinMode(_EN,OUTPUT);
  digitalWrite(_EN,HIGH); // default to on
  pinMode(_nSF,INPUT);

}
// Set speed for motor 1, speed is a number betwenn -400 and 400, 0 stops motor
void DualMC33926MotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 255)  // Max PWM dutycycle
    {speed = 255;}

  if (reverse == 1)
  {
    analogWrite(_M1IN2,0);
    analogWrite(_M1IN1,speed);
    //digitalWrite(_M1IN2,LOW);
    //digitalWrite(_M1IN1, HIGH);
  }
  else
  {
    analogWrite(_M1IN1,0);
    analogWrite(_M1IN2,speed);
    //digitalWrite(_M1IN2,HIGH);
    //digitalWrite(_M1IN1, LOW);
  }
}

// Set speed for motor 2, speed is a number betwenn -400 and 400, 0 stops motor
/*
void DualMC33926MotorShield::setM2Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 255)  // Max PWM dutycycle
    {speed = 255;}

  if (reverse ==1)
  {
    analogWrite(_M2IN2,0);
    analogWrite(_M2IN1,speed);
  }
  else
  {
    analogWrite(_M2IN1,0);
    analogWrite(_M2IN2,speed);
  }
}
*/
// Set speed for motor 1 and 2
void DualMC33926MotorShield::setSpeeds(int m1Speed/*, int m2Speed*/)
{
  setM1Speed(m1Speed);
  //setM2Speed(m2Speed);
}

// Return motor 1 current value in milliamps.
float DualMC33926MotorShield::getM1CurrentMilliamps()
{
   // Particle is 3.3v/ 4096 = .8057mV/count, motor FB is 525 mV/1000mA => 1.5346 mA per count
  return analogRead(_M1FB) * 1.5346;
}

// Return motor 2 current value in milliamps.
/*
float DualMC33926MotorShield::getM2CurrentMilliamps()
{
 // Particle is 3.3v/ 4096 = .8057mV/count, motor FB is 525 mV/1000mA => 1.5346 mA per count
  return analogRead(_M2FB) * 1.5346;
}
*/
// Return error status
unsigned char DualMC33926MotorShield::getFault()
{
  return !digitalRead(_nSF);
}

void DualMC33926MotorShield::enable()
{
// enable motor
  digitalWrite(_EN,HIGH); // default is on
}

void DualMC33926MotorShield::disable()
{
// disable motor
  digitalWrite(_EN,LOW); // default is on
}


DualMC33926MotorShield motor = DualMC33926MotorShield(); // make instance "motor" to be used in program
