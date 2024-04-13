#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "main.h"

class Intake {
public:
    pros::Motor INTLMotor;
    pros::Motor INTRMotor;

    // constructor
    Intake (int INTL_PORT, int INTR_PORT) : 
    INTLMotor(INTL_PORT, MOTOR_GEAR_200, true), INTRMotor(INTR_PORT, MOTOR_GEAR_200, false)
    {
        // INTMotor.set_voltage_limit(600);
    }

    // telemetry

    double getTemperature() {
        return (INTLMotor.get_temperature()+INTRMotor.get_temperature())/2;
    }

    int getRealVelocity() {
        return (INTLMotor.get_actual_velocity()+INTRMotor.get_actual_velocity())/2;
    }

    // control
    void moveVelocity(double velocity) {
        velocity = fmin(fmax(velocity, -600), 600);

        INTLMotor.move_velocity(velocity);
        INTRMotor.move_velocity(velocity);
    }

    // void updateVelocity() {
    //     velocity += sign(target - velocity) * fmin(60, fabs(target - velocity));
    // }

    // void updateVelocity(double t) {
    //     velocity += sign(t - velocity) * fmin(60, fabs(t - velocity));
    // }
    
};

#endif