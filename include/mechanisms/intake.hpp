#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "main.h"

class Intake {
public:
    pros::Motor INTMotor;

    // constructor
    Intake (int INT_PORT) : 
    INTMotor(INT_PORT, MOTOR_GEAR_200, false)
    {
        // INTMotor.set_voltage_limit(600);
    }

    // telemetry

    double getTemp() {
        return INTMotor.get_temperature();
    }

    int getRealVelocity() {
        return INTMotor.get_actual_velocity();
    }

    // control
    void moveVelocity(double velocity) {
        velocity = fmin(fmax(velocity, -200), 200);

        INTMotor.move_velocity(velocity);
    }

    // void updateVelocity() {
    //     velocity += sign(target - velocity) * fmin(60, fabs(target - velocity));
    // }

    // void updateVelocity(double t) {
    //     velocity += sign(t - velocity) * fmin(60, fabs(t - velocity));
    // }
    
};

#endif