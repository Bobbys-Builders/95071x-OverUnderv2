#ifndef KICKER_HPP
#define KICKER_HPP

#include "main.h"

class Kicker {
public:
    pros::Motor KCKLMotor;
    pros::Motor KCKRMotor;

    pros::Rotation KCKRotation;

    double target = 0;
    double velocity = 0;

    // constructor
    Kicker (int KCKL_PORT, int KCKR_PORT, int KCKROT_PORT) : 
    KCKLMotor(KCKL_PORT, MOTOR_GEAR_200, false), KCKRMotor(KCKR_PORT, MOTOR_GEAR_200, true), KCKRotation(KCKROT_PORT, true)
    {
        // KCKLMotor.set_voltage_limit(600);
        KCKRotation.reset();
        KCKLMotor.set_brake_mode(MOTOR_BRAKE_COAST);
        KCKRMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    }

    // telemetry

    double getAvgTemp() {
        return (KCKLMotor.get_temperature() + KCKLMotor.get_temperature()) / 2;
    }

    double getMaxTemp() {
        return fmax(KCKLMotor.get_temperature(), KCKLMotor.get_temperature());
    }

    double getRealVelocity() {
        return (KCKLMotor.get_actual_velocity() + KCKLMotor.get_actual_velocity()) / 2;
    }

    double getPosition() {
        return modabs(KCKRotation.get_angle(), 36000);
    }

    // control
    void moveVelocity(double velocity) {
        velocity = fmin(fmax(velocity, -200), 200);

        KCKLMotor.move_velocity(velocity);
        KCKRMotor.move_velocity(velocity);
        // KCKLMotor.move_voltage(velocity*12000/200);
        // KCKRMotor.move_voltage(velocity*12000/200);
    }

    void updateVelocity() {
        velocity += sign(target - velocity) * fmin(20, fabs(target - velocity));
    }

    // void updateVelocity(double t) {
    //     velocity += sign(t - velocity) * fmin(60, fabs(t - velocity));
    // }


    double sign(double input) {
        if (input == 0) return 1;
        return fabs(input) / input;
    }

    double modabs(double value, double mod) {
    return fmod(fmod(value, mod) + mod, mod);
    }
    
};

#endif