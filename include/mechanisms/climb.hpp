#ifndef CLIMB_HPP
#define CLIMB_HPP

#include "main.h"

class Climb {
public:
    pros::ADIDigitalOut CLMPiston;
    pros::ADIDigitalOut PTOPiston;

    // constructor
    Climb (int EXP_PORT, char CLM_PORT, char PTO_PORT) : 
    CLMPiston(CLM_PORT, false), PTOPiston(PTO_PORT, false)
    {}

    // control
    void climbUp() {
        CLMPiston.set_value(true);
    }

    void climbDown() {
        CLMPiston.set_value(false);
    }

    void PTOEngage() {
        PTOPiston.set_value(true);
    }

    void PTODisengage() {
        PTOPiston.set_value(false);
    }
};

#endif