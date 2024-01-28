#ifndef WINGS_HPP
#define WINGS_HPP

#include "main.h"

class Wings {
public:
    pros::ADIDigitalOut FLPiston;
    pros::ADIDigitalOut FRPiston;
    pros::ADIDigitalOut BLPiston;
    pros::ADIDigitalOut BRPiston;

    // constructor
    Wings (int EXP_PORT, char FLP_PORT, char FRP_PORT, char BLP_PORT, char BRP_PORT) : 
    FLPiston(FLP_PORT, false), FRPiston(FRP_PORT, false), 
    BLPiston(BLP_PORT, false), BRPiston(BRP_PORT, false)
    {}

    // control
    void extFrontWings() {
        FLPiston.set_value(true);
        FRPiston.set_value(true);
    }

    void retFrontWings() {
        FLPiston.set_value(false);
        FRPiston.set_value(false);
    }

    void extBackWings() {
        BLPiston.set_value(true);
        BRPiston.set_value(true);
    }

    void retBackWings() {
        BLPiston.set_value(false);
        BRPiston.set_value(false);
    }

    void extFLWing() {
        FLPiston.set_value(true);
    }
    void retFLWing() {
        FLPiston.set_value(false);
    }

    void extFRWing() {
        FRPiston.set_value(true);
    }
    void retFRWing() {
        FRPiston.set_value(false);
    }

    void extBLWing() {
        BLPiston.set_value(true);
    }
    void retBLWing() {
        BLPiston.set_value(false);
    }

    void extBRWing() {
        BRPiston.set_value(true);
    }
    void retBRWing() {
        BRPiston.set_value(false);
    }
};

#endif