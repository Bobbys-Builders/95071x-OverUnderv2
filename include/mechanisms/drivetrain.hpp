#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include "main.h"

class Drivetrain {
public:
    pros::Motor FLMotor;
    pros::Motor MLMotor;
    pros::Motor BLMotor;
    pros::Motor FRMotor;
    pros::Motor MRMotor;
    pros::Motor BRMotor;

    pros::Rotation vOdom;
    pros::Rotation hOdom;
    pros::ADIDigitalOut odomPiston;

    double lastVOdom = 0;
    double lastHOdom = 0;

    pros::IMU imu;

    // constructor
    Drivetrain (int FL_PORT, int ML_PORT, int BL_PORT, int FR_PORT, int MR_PORT, int BR_PORT, int IMU_PORT, int VODOM_PORT, int HODOM_PORT, int EXP_PORT, char ODOM_PORT) : 
    FLMotor(FL_PORT, MOTOR_GEARSET_06, false), MLMotor(ML_PORT, MOTOR_GEARSET_06, false), BLMotor(BL_PORT, MOTOR_GEARSET_06, true), 
    FRMotor(FR_PORT, MOTOR_GEARSET_06, true), MRMotor(MR_PORT, MOTOR_GEARSET_06, true), BRMotor(BR_PORT, MOTOR_GEARSET_06, false), 
    imu(IMU_PORT), vOdom(VODOM_PORT, true), hOdom(HODOM_PORT, false), odomPiston(ODOM_PORT)
    {
        vOdom.reset_position();
        hOdom.reset_position();
    }

    // telemetry
    double getAvgTemps() {
        return (FLMotor.get_temperature() + MLMotor.get_temperature() + BLMotor.get_temperature() 
        + FRMotor.get_temperature() + MRMotor.get_temperature() + BRMotor.get_temperature()) / 6;
    }

    int getMaxTemp() {
        return fmax(FLMotor.get_temperature(), fmax(MLMotor.get_temperature(), fmax(BLMotor.get_temperature(), 
        fmax(FRMotor.get_temperature(), fmax(MRMotor.get_temperature(), BRMotor.get_temperature())))));
    }

    // returns in degrees
    double getPositionV() {
        double pos = vOdom.get_position() - lastVOdom;
        lastVOdom = vOdom.get_position();
        return pos / 100;
    }

    double getPositionH() {
        double pos = hOdom.get_position() - lastHOdom;
        lastHOdom = hOdom.get_position();
        return pos / 100;
    }
    
    double getPositionLeft() {
        return (FLMotor.get_position() + MLMotor.get_position() + BLMotor.get_position()) / 3;
    }

    double getPositionRight() {
        return (FRMotor.get_position() + MRMotor.get_position() + BRMotor.get_position()) / 3;
    }

    // int getVelocityLeft() {
    //     return (FLMotor.get_actual_velocity() + BLMotor.get_actual_velocity() + TLMotor.get_actual_velocity()) / 3;
    // }

    // int getVelocityRight() {
    //     return (FRMotor.get_actual_velocity() + BRMotor.get_actual_velocity() + TRMotor.get_actual_velocity()) / 3;
    // }

    // void reset() {
    //     FLMotor.tare_position();
    //     BLMotor.tare_position();
    //     TLMotor.tare_position();
    //     FRMotor.tare_position();
    //     BRMotor.tare_position();
    //     TRMotor.tare_position();
    // }

    // control
    // moves the left motors using velocity
    void moveVelocityLeft(double velocity) {
        velocity = fmin(fmax(velocity, -600), 600); // limits velocity to max/min

        FLMotor.move_velocity(velocity);
        MLMotor.move_velocity(velocity);
        BLMotor.move_velocity(velocity);
    }

    // moves the right motors using velocity
    void moveVelocityRight(double velocity) {
        velocity = fmin(fmax(velocity, -600), 600); // limits velocity to max/min

        FRMotor.move_velocity(velocity);
        MRMotor.move_velocity(velocity);
        BRMotor.move_velocity(velocity);
    }

    void moveVoltageLeft(int voltage) {
        voltage = fmin(fmax(voltage, -12000), 12000); // limits voltage to max/min

        FLMotor.move_voltage(voltage);
        MLMotor.move_voltage(voltage);
        BLMotor.move_voltage(voltage);
    }

    void moveVoltageRight(int voltage) {
        voltage = fmin(fmax(voltage, -12000), 12000); // limits voltage to max/min

        FRMotor.move_voltage(voltage);
        MRMotor.move_voltage(voltage);
        BRMotor.move_voltage(voltage);
    }

    void moveRelativeLeft(int ticks, double velocity) {
        velocity = fmin(fmax(velocity, -600), 600); // limits velocity to max/min

        FLMotor.move_relative(ticks, velocity);
        MLMotor.move_relative(ticks, velocity);
        BLMotor.move_relative(ticks, velocity);
    }

    void moveRelativeRight(int ticks, double velocity) {
        velocity = fmin(fmax(velocity, -600), 600); // limits velocity to max/min

        FRMotor.move_relative(ticks, velocity);
        MRMotor.move_relative(ticks, velocity);
        BRMotor.move_relative(ticks, velocity);
    }

    // moves the right motors using velocity + PID
    // double integralLeft = 0;
    // double lastErrorLeft = 0;
    // void movePIDLeft(double velocity, double kP = 5, double kI = 7, double kD = 15) {
    //     velocity = fmin(fmax(velocity, -600), 600); // limits velocity to max/min

    //     double error = velocity - getVelocityLeft();
    //     if (fabs(error) > 5) {
    //         integralLeft += error;
    //         double derivative = error - lastErrorLeft;
    //         moveVoltageLeft(kP * error + kI * integralLeft + kD * derivative);

    //         lastErrorLeft = error;
    //     }
    // }

    // // moves the right motors using velocity + PID
    // double integralRight = 0;
    // double lastErrorRight = 0;
    // void movePIDRight(double velocity, double kP = 5, double kI = 7, double kD = 15) {
    //     velocity = fmin(fmax(velocity, -600), 600); // limits velocity to max/min

    //     double error = velocity - getVelocityRight();
    //     if (fabs(error) > 5) {
    //         integralRight += error;
    //         double derivative = error - lastErrorRight;
    //         moveVoltageRight(kP * error + kI * integralRight + kD * derivative);

    //         lastErrorRight = error;
    //     }
    // }
    
    void stop() {
        moveVoltageLeft(0);
        moveVoltageRight(0);
    }

    void hold() {
        FLMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
        MLMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
        BLMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
        FRMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
        MRMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
        BRMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    }
    
    void coast() {
        FLMotor.set_brake_mode(MOTOR_BRAKE_COAST);
        MLMotor.set_brake_mode(MOTOR_BRAKE_COAST);
        BLMotor.set_brake_mode(MOTOR_BRAKE_COAST);
        FRMotor.set_brake_mode(MOTOR_BRAKE_COAST);
        MRMotor.set_brake_mode(MOTOR_BRAKE_COAST);
        BRMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    }

};

#endif