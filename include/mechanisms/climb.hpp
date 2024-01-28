#ifndef CLIMB_HPP
#define CLIMB_HPP

#include "main.h"

class Climb {
public:
    pros::ADIDigitalOut CLMUPiston;
    pros::ADIDigitalOut CLMDPiston;

    // constructor
    Climb (int EXP_PORT, char CLMU_PORT, char CLMD_PORT) : 
    CLMUPiston(CLMU_PORT, false), CLMDPiston(CLMD_PORT, false)
    {}

    // control
    void climbUp() {
        CLMDPiston.set_value(true);
        CLMUPiston.set_value(true);
    }

    void climbDown() {
        CLMDPiston.set_value(false);
        CLMUPiston.set_value(false);
    }
};

#endif