#ifndef DualMC33926MotorShield_h
#define DualMC33926MotorShield_h

#include "application.h"

class DualMC33926MotorShield
{
  public:
    // CONSTRUCTORS
    DualMC33926MotorShield(); // Default pin selection.
    DualMC33926MotorShield(unsigned char M1IN1, unsigned char M1IN2, unsigned char M1FB,
                           /*unsigned char M2IN1, unsigned char M2IN2, unsigned char M2FB,*/
                           unsigned char EN, unsigned char nSF); // User-defined pin selection.

    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ.
    void setM1Speed(int speed); // Set speed for M1.
    void setM2Speed(int speed); // Set speed for M2.
    void setSpeeds(int m1Speed/*, int m2Speed*/); // Set speed for both M1 and M2.
    float getM1CurrentMilliamps(); // Get current reading for M1.
    //float getM2CurrentMilliamps(); // Get current reading for M2.
    unsigned char getFault(); // Get fault reading.
    void enable();
    void disable();

  private:
    unsigned char _EN;
    unsigned char _M1IN1;
    unsigned char _M1IN2;
    //unsigned char _M2IN1;
    //unsigned char _M2IN2;
    unsigned char _nSF;
    unsigned char _M1FB;
    //unsigned char _M2FB;
};

extern DualMC33926MotorShield motor;

#endif
