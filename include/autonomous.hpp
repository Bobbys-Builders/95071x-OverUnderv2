#ifndef AUTONOMOUS_HPP
#define AUTONOMOUS_HPP

#include "setup.hpp"
#include "tasks.hpp"
#include "teleop.hpp"
#include "skills.hpp"


void noAuton() {}

void auton1() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-600); // deploy intake
    
    print_task.suspend();
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void preauton1() {
    drive.hold();
    drive.imu.set_heading(0);
    driveDisabled = false;
    setPos(5*24+6, 1*24+7.5);
    
    driveDisabled = true;
    driveMode = 0;
    // maxTurnConstant = 35;
    maxMoveSpeed = 450;
    drive.stop();

}

    // bryan has a skill issue
	switch (curSelected) {
        case 1:
        noAuton();
        break;

        case 2:
        auton1();
        break;

        case 3:
        preauton1();
        break;
	}
}

#endif