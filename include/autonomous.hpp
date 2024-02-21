#ifndef AUTONOMOUS_HPP
#define AUTONOMOUS_HPP

#include "setup.hpp"
#include "tasks.hpp"
#include "teleop.hpp"

void testAuton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();
    drive.imu.set_heading(0);
    setPos(0, 0);
    arcMovement = false;
    driveDisabled = false;
    driveMode = 1;

    move(6, movePID, turnPID, 0, 250);
    // swerve(90, turnPID, 0, 250);
    // swerve(180, turnPID, 0, 250);
    // driveMode = 2;
    // swerve(90, turnPID, 0, 250);
    // driveMode = 1;
    // turn(0, turnPID, 0, 250);
    // move(24, movePID, turnPID, 0, 250);
    // driveMode = 2;
    // swerve(90, turnPID, 0, 250);
    // driveMode = 1;
    // swerve(180, turnPID, 0, 250);
    // driveMode = 0;
    // swerve(0.0, 0.0, turnPID, 0, 250);
    // move(positionError(0, 0), movePID, turnPID, 0, 250);
    // turn(0, turnPID, 0, 250);
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    print_task.suspend(); 
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void noAuton() {}

void closeSafeAuton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-200); // deploy intake
    wings.extBRWing(); // descore triball
    driveMode = 1;
    setTargetPos(5*24+12, 1*24+12);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);
    setTargetPos(xPos, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    wings.retBackWings();
    
    driveMode = 2; // score alliance triball
    setTargetPos(5*24, 20);
    maxMoveSpeed = 450;
    untilTargetPos(5, 1000);
    
    // driveDisabled = true; // ram backwards
    // drive.moveVelocityLeft(-500);
    // drive.moveVelocityRight(-500);
    // pros::delay(750);
    
    driveDisabled = false;
    driveMode = 1; // line up to touch pole
    // wings.extFrontWings();
    setTargetPos(5*24+14, 1*24+12);
    maxMoveSpeed = 200;
    untilTargetPos(10, 2000);

    setTargetPos(5*24+14, 3*24-11); // turn towards pole
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 500);

    maxMoveSpeed = 200; // move to pole
    wings.extFrontWings();
    untilTargetPos(3, 2000);
    pros::delay(500);
    setTargetPos(xPos, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(3, 2000, 500);
    wings.retFrontWings();
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    print_task.suspend();
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void closePreauton() {
    drive.hold();
    // maxTurnConstant = 20;
    drive.imu.set_heading(0);
    driveDisabled = false;
    setPos(5*24+6, 1*24+7.5);

    // driveMode = 1;
    // setTargetPos(5*24+10, 1*24+12);
    // maxMoveSpeed = 0;
    // untilTargetH(2, 3000);
    // pros::delay(1000);

    // maxMoveSpeed = 150;
    // untilTargetPos(3, 4000);

    // setTargetPos(3*24, 2*24);
    // maxMoveSpeed = 0;
    // untilTargetH(2, 3000);
    
    driveDisabled = true;
    driveMode = 0;
    // maxTurnConstant = 35;
    maxMoveSpeed = 450;
    drive.stop();

}

void closeAuton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-200); // deploy intake
    driveDisabled = true;
    pros::delay(500);
    wings.extBRWing(); // descore triball
    driveDisabled = false;
    driveMode = 1;

    setTargetPos(3*24+8, 2*24-2); // intake middle triball
    setChainPos(4*24-8, 2*24-4);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    intake.moveVelocity(200); 
    wings.retBackWings();
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(3*24+8, 2*24-2);
    // maxMoveSpeed = 450;
    // pros::delay(750);
    maxMoveSpeed = 300;
    untilTargetPos(7, 2000);

    driveDisabled = true;
    maxMoveSpeed = 0;
    pros::delay(20);
    drive.stop();
    driveDisabled = false;

    driveMode = 2; // move back
    setTargetPos(5*24+5, 1*24+2);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);

    driveDisabled = true;
    pros::delay(500);
    botMove(-10, 450);
    intake.moveVelocity(200);
    driveDisabled = false;

    // driveMode = 2; // deposit triball 1
    // setTargetPos(5*24-12, 1*24+8);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);

    // driveMode = 1;
    // setTargetPos(5*24+12, 2*24);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // intake.moveVelocity(-200);
    // pros::delay(500);

    // setTargetPos(4*24+8, 3*24-12); // intake triball 2
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // intake.moveVelocity(200);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    // setTargetPos(3*24+8, 3*24-4);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000, 250);
    // maxMoveSpeed = 300;
    // untilTargetPos(5, 2000);

    // driveDisabled = true;
    // maxMoveSpeed = 0;
    // pros::delay(20);
    // drive.stop();
    // pros::delay(500);
    // botMove(-10, 450);
    // intake.moveVelocity(150);
    // driveDisabled = false;

    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);

    driveMode = 1;
    setTargetPos(5*24+16, 2*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    intake.moveVelocity(-200);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);

    intake.moveVelocity(-200);
    setTargetPos(xPos, 3*24-10); // turn towards pole
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);

    maxMoveSpeed = 200; // move to pole
    wings.extFrontWings();
    untilTargetPos(3, 2000);
    setTargetPos(xPos, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(3, 2000, 500);
    wings.retFrontWings();
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    print_task.suspend();
    drive.stop();
    pros::delay(500);
    if (pros::millis() - start > 15000) controller.rumble("-");
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(4000);
    print_task.resume();
}

void closeElimAuton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-200); // deploy intake
    driveDisabled = true;
    pros::delay(500);
    wings.extBRWing(); // descore triball
    driveDisabled = false;
    driveMode = 1;

    setTargetPos(3*24+8, 2*24-4); // intake middle triball
    setChainPos(4*24-8, 2*24-6);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    intake.moveVelocity(200); 
    wings.retBackWings();
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setChainPos(3*24+8, 2*24-4);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    maxMoveSpeed = 0;
    pros::delay(20);
    drive.stop();
    pros::delay(500);
    botMove(-10, 450);
    intake.moveVelocity(150);
    driveDisabled = false;

    // driveMode = 2; // deposit triball 1
    // setTargetPos(5*24-12, 1*24+8);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);

    // driveMode = 1;
    // setTargetPos(5*24+12, 2*24);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // intake.moveVelocity(-200);
    // pros::delay(500);

    // setTargetPos(4*24+8, 3*24-12); // intake triball 2
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // intake.moveVelocity(200);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    // setTargetPos(3*24+8, 3*24-4);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000, 250);
    // maxMoveSpeed = 300;
    // untilTargetPos(5, 2000);

    // driveDisabled = true;
    // maxMoveSpeed = 0;
    // pros::delay(20);
    // drive.stop();
    // pros::delay(500);
    // botMove(-10, 450);
    // intake.moveVelocity(150);
    // driveDisabled = false;

    driveMode = 2; // move back
    setTargetPos(5*24+5, 1*24+2);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);

    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    intake.moveVelocity(0);

    driveMode = 1;
    setTargetPos(5*24+16, 2*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    intake.moveVelocity(-200);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);

    intake.moveVelocity(-200);
    setTargetPos(xPos, 3*24-10); // turn towards pole
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);

    maxMoveSpeed = 200; // move to pole
    wings.extFrontWings();
    untilTargetPos(3, 2000);
    setTargetPos(xPos, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(3, 2000, 500);
    wings.retFrontWings();

    driveMode = 2;
    setTargetPos(5*24, 1*24);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    print_task.suspend(); 
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void farPreauton() {
    drive.hold();
    // maxTurnConstant = 20;
    drive.imu.set_heading(180);
    driveDisabled = false;
    setPos(5*24+6, 5*24-7.5);

    // driveMode = 1;
    // setTargetPos(5*24+12, 5*24-6);
    // maxMoveSpeed = 0;
    // untilTargetH(2, 3000);
    // pros::delay(1000);

    // maxMoveSpeed = 150;
    // untilTargetPos(3, 4000);

    // setTargetPos(xPos-200, xPos+200);
    // maxMoveSpeed = 0;
    // untilTargetH(2, 3000);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    // maxTurnConstant = 35;
    drive.stop();
}

void farSafeAuton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-200); // deploy intake
    driveDisabled = true;
    botMove(-5, 450);
    pros::delay(200);
    intake.moveVelocity(200); // intake triball 1
    botMove(5, 450);
    botMove(-5, 450);
    driveDisabled = false;

    driveMode = 2;
    wings.extBRWing();
    setTargetPos(5*24+2, 5*24+8);
    setChainPos(5*24+11, 4*24+5);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);

    setChainPos(5*24+10, 5*24-4);
    maxMoveSpeed = 300;
    untilTargetPos(15, 2000);

    wings.extBLWing(); // descore triball 2
    intake.moveVelocity(0);
    setChainPos(5*24-4, 5*24+10);
    maxMoveSpeed = 300;
    untilTargetPos(15, 2000);
    wings.retBLWing();
    setChainPos(4*24, 5*24+14);
    maxMoveSpeed = 600;
    untilTargetPos(10, 2000);

    driveDisabled = true;
    botMove(10, 450);
    wings.retBackWings();
    drive.moveVoltageLeft(350);
    drive.moveVoltageRight(-350);
    pros::delay(250);
    driveDisabled = false;
    driveMode = 1;
    setTargetPos(4*24, 5*24+16);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);

    driveDisabled = true;
    intake.moveVelocity(-200);
    botMove(20, 450);
    botMove(-12, 450);
    driveDisabled = false;

    intake.moveVelocity(200); // intake triball 3
    setTargetPos(4*24-4, 3*24+9);
    setChainPos(4*24+4, 4*24-5);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(4*24-4, 3*24+9);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    botMove(-10, 450);
    intake.moveVelocity(0);
    driveDisabled = false;
    setTargetPos(3*24+12, 4*24-12);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    
    setTargetPos(3*24+4, 5*24); // score triball 3
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);

    driveDisabled = true;
    intake.moveVelocity(-200);
    wings.extFrontWings();
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    drive.stop();
    intake.moveVelocity(0);
    botMove(-10, 450);
    wings.retFrontWings();
    driveDisabled = false;

    driveMode = 2;
    setTargetPos(4*24+12, 3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    driveMode = 1;
    setTargetPos(xPos+12, yPos-8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);

    driveDisabled = true;
    intake.moveVelocity(200);
    drive.moveVelocityLeft(200);
    drive.moveVelocityRight(200);
    pros::delay(2000);
    drive.stop();
    driveDisabled = false;
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    print_task.suspend();
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void farSafe6Auton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-200); // deploy intake
    driveDisabled = true;
    botMove(-5, 450);
    pros::delay(200);
    intake.moveVelocity(200); // intake triball 1
    botMove(10, 450);
    pros::delay(100);
    botMove(-5, 450);
    driveDisabled = false;

    driveMode = 2;
    wings.extBRWing();
    setTargetPos(5*24-4, 5*24+8);
    setChainPos(5*24+11, 4*24+5);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);

    setChainPos(5*24+10, 5*24-4);
    maxMoveSpeed = 300;
    untilTargetPos(15, 2000);

    wings.extBLWing(); // descore triball 2
    intake.moveVelocity(0);
    setChainPos(5*24-4, 5*24+10);
    maxMoveSpeed = 300;
    untilTargetPos(15, 2000);
    setChainPos(5*24-4, 5*24+8);
    maxMoveSpeed = 300;
    untilTargetPos(5, 1000);
    // wings.retBLWing();
    wings.retBackWings();

    // setTargetPos(4*24, 5*24+20);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // driveDisabled = true;
    // drive.moveVelocityLeft(-600);
    // drive.moveVelocityRight(-600);
    // pros::delay(800);
    // untilTargetPos(5, 1500);
    // driveDisabled = false;

    driveDisabled = true;
    // botMove(10, 600);
    wings.retBackWings();
    drive.moveVoltageLeft(350);
    drive.moveVoltageRight(-350);
    pros::delay(500);
    driveDisabled = false;
    driveMode = 1;
    setTargetPos(4*24, 5*24+18);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);

    driveDisabled = true;
    intake.moveVelocity(-200);
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    botMove(-15, 600);
    driveDisabled = false;

    intake.moveVelocity(200); // intake triball 3
    setTargetPos(4*24+1, 3*24+9);
    setChainPos(4*24+3, 4*24-5);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(4*24+1, 3*24+9);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    botMove(-2, 450);
    intake.moveVelocity(0);
    driveDisabled = false;
    
    setTargetPos(3*24+12, 5*24-4); // deposit triball 3
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    intake.moveVelocity(-200);
    pros::delay(200);
    driveDisabled = true;
    botMove(5, 450);
    botMove(-5, 450);
    driveDisabled = false;
    
    intake.moveVelocity(200); // intake triball 4
    setTargetPos(3*24+5, 3*24+9);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 300;
    maxTurnSpeed = 0;
    untilTargetPos(5, 2000);
    
    intake.moveVelocity(0); // score triball 3,4,5
    setTargetPos(xPos, yPos+40);
    maxTurnSpeed = 350;
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    
    driveDisabled = true;
    wings.extFrontWings();
    intake.moveVelocity(-200);
    botMove(48, 450);
    intake.moveVelocity(0);
    botMove(-20, 450);
    wings.retFrontWings();
    driveDisabled = false;
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    print_task.suspend();
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void skillsPreauton() {
    drive.hold();
    drive.imu.set_heading(0);
    driveDisabled = false;
    setPos(5*24+6, 1*24+7.5);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    drive.stop();
}

void skillsSegA() {
    driveDisabled = false;
    intake.moveVelocity(-200); // move to shooting position
    kicker.target = 200;
    driveMode = 2;
    kicker.target = 170;
    kicker.velocity = 170;
    kicker.moveVelocity(170);
    setTargetPos(5*24, 10);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);

    driveMode = 1;
    setTargetPos(3*24, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    wings.extBRWing();
    while(true) {
        kicker.target = 170;
        kicker.velocity = 170;
        kicker.moveVelocity(170);
        intake.moveVelocity(-200);

        pros::delay(10);

        if (updateButtons()) {
            break;
        }
    }

    wings.retBackWings();
}

void skillsAuton() {
    double start = pros::millis();
    driveDisabled = false;

    
    intake.moveVelocity(-200); // move to shooting position
    kicker.target = 200;
    driveMode = 2;
    kicker.target = 170;
    kicker.velocity = 170;
    kicker.moveVelocity(170);
    setTargetPos(5*24, 10);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);

    driveMode = 1;
    setTargetPos(3*24, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    wings.extBRWing();
    int t = 0;
    // while(t < 21000) {
    while(t < 20000) {
        kicker.target = 150;
        kicker.velocity = 150;
        kicker.moveVelocity(150);
        intake.moveVelocity(-200);

        pros::delay(10);
        t += 10;
    }
    wings.retBRWing();
    kicker.target = 100;
    kicker.velocity = 100;
    kicker.moveVelocity(100);
    untilKeyPress();

    maxMoveSpeed = 0; // move to goal
    driveMode = 1;
    setTargetPos(5*24+10, 1*24+12);
    untilTargetH(5, 3000);
    wings.extFrontWings();
    maxMoveSpeed = 450;
    untilTargetPos(10, 3000);
    setTargetPos(5*24+12, 4*24+4);
    maxMoveSpeed = 450;
    untilTargetPos(10, 1500);
    // arcMovement = true;
    setTargetPos(5*24+6, 5*24-8);
    // pros::delay(500);
    // flaps.extendLeftFlap();
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    // arcMovement = false;
    setTargetPos(4*24, 5*24+8);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    maxMoveSpeed = 0;
    untilTargetH(5, 1500, 250);

    driveDisabled = true; // push 1
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    botMove(-15, 450);
    wings.retFrontWings();

    driveDisabled = false;
    // driveMode = 2;
    // setTargetPos(5*24+12, 5*24-8);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000, 250);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    // driveMode = 1;
    // setTargetPos(4*24, 5*24+12);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000, 250);

    // driveDisabled = true;
    // drive.moveVelocityLeft(600);
    // drive.moveVelocityRight(600);
    // pros::delay(1000);
    // // setPos(3*24+30, yPos);
    // // pros::delay(1500);
    // // flaps.retractLeftFlap();
    // botMove(-15, 450);
    // driveDisabled = false;

    driveMode = 1; // herd triballs
    arcMovement = false;
    setTargetPos(5*24-6, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 3000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 1500);
    driveMode = 1;
    arcMovement = false;
    setTargetPos(4*24+8, 4*24+10);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    wings.extFrontWings();
    // arcMovement = true;
    setTargetPos(4*24-6, 4*24+4);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);
    // arcMovement = false;
    // setTargetPos(xPos - 200, yPos);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);

    driveDisabled = true;
    // botMove(7, 300);
    wings.retFrontWings();
    botMove(-5, 450);

    driveMode = 1;
    driveDisabled = false;
    arcMovement = false;
    setTargetPos(4*24-8, 3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 1000);
    maxMoveSpeed = 0;
    driveMode = 2;
    setTargetPos(3*24+8, 5*24);
    untilTargetH(5, 2000);
    pros::delay(250);

    driveDisabled = true;
    wings.extBackWings();
    drive.moveVelocityLeft(-450);
    drive.moveVelocityRight(-600);
    pros::delay(1000);
    botMove(10, 450);

    driveDisabled = false;
    setTargetPos(xPos, yPos + 200);
    maxMoveSpeed = 0;
    untilTargetH(5, 500);

    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    pros::delay(1000);
    setPos(xPos, 6*24-33.5);
    botMove(8, 450);
    wings.retBackWings();
    driveDisabled = false;

    driveMode = 1;
    // arcMovement = true;
    driveDisabled = false;
    setTargetPos(xPos+12, 3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    driveMode = 2;
    setTargetPos(2*24, 3*24+8);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    wings.extBRWing();
    maxMoveSpeed = 450;
    untilTargetPos(10, 3000);

    // driveMode = 1;
    // setTargetPos(2*24+12, 4*24);
    // maxMoveSpeed = 450;
    // wings.extendLeftFlap();
    // untilTargetPos(10, 2000);
    driveMode = 2;
    setTargetPos(3*24-8, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    wings.extBackWings();
    pros::delay(250);

    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-450);
    pros::delay(1000);
    botMove(10, 450);

    driveDisabled = false;
    driveMode = 2;
    setTargetPos(xPos, yPos + 200);
    maxMoveSpeed = 0;
    untilTargetH(5, 500);

    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    pros::delay(1000);
    setPos(xPos, 6*24-33.5);
    botMove(-8, 450);
    wings.retBackWings();
    // flaps.extendFlaps();
    // flaps.retractFlaps();
    driveDisabled = false;

    driveDisabled = false; // herd triballs
    driveMode = 1;
    setTargetPos(xPos, 3*24+10);
    // arcMovement = true;
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);
    driveMode = 1;
    setTargetPos(2*24, 3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    wings.extFrontWings();
    setTargetPos(1*24+8, 5*24-12);
    untilTargetPos(5, 2000);
    setTargetPos(xPos+100, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(30, 2000);
    wings.retFrontWings();
    untilTargetH(15, 2000);


    driveMode = 1;
    setTargetPos(12, 5*24-8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    // flaps.extendFlaps();
    // flaps.retractFlaps();
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    driveMode = 1;
    // flaps.extendRightFlap();
    // arcMovement = true;
    setTargetPos(2*24, 5*24+18);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    pros::delay(250);
    wings.extFrontWings();

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    wings.retFrontWings();
    botMove(-5, 450);

    driveDisabled = false;
    driveMode = 2;
    setTargetPos(1*24-3, 5*24+10);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    driveMode = 1;
    setTargetPos(2*24, 5*24+18);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    pros::delay(250);

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(750);
    // flaps.retractFlaps();
    driveDisabled = false;
    driveMode = 2;
    setTargetPos(12, 5*24);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    driveDisabled = true;
    // flaps.extendFlaps();
    // flaps.retractFlaps();
    botMove(5, 450);

    driveDisabled = false;
    driveMode = 2;
    setTargetPos(12, 5*24-12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    driveMode = 1;
    climb.climbUp();
    setTargetPos(12, 3*24-4);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2500);
    driveDisabled = true;
    botMove(10, 300);
    botMove(-5, 300);
    climb.climbDown();
    kicker.target = 200;
    kicker.velocity = 200;
    kicker.moveVelocity(200);
    pros::delay(1000);
    kicker.target = 0;
    kicker.velocity = 0;
    kicker.moveVelocity(0);

    // maxMoveSpeed = 0; // push triballs over barrier
    // driveMode = 1;
    // setTargetPos(1*24+12, 2*24+12);
    // setChainPos(4*24+12, 1*24+12);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);
    // wings.extFrontWings();
    // setChainPos(3*24, 3*24-16);
    // // maxMoveSpeed = 0;
    // // untilTargetH(10, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);
    // setChainPos(2*24+12, 3*24-8);
    // // maxMoveSpeed = 0;
    // // untilTargetH(10, 2000);
    // maxMoveSpeed = 600;
    // untilTargetPos(15, 2000);
    // setChainPos(1*24+12, 2*24+12);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);

    // driveDisabled = true;
    // wings.retFrontWings();
    // botMove(-15, 450);
    // driveDisabled = false;

    // driveMode = 1; // align for alley push
    // setTargetPos(1*24+12, 12);
    // setChainPos(1*24+12, 1*24+4);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 2000);
    // setChainPos(1*24+12, 12);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 2000);

    // driveMode = 1;
    // setTargetPos(1*24+12, 5*24+18);
    // setChainPos(12, 1*24+18);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000, 250);
    // wings.extFrontWings();
    // maxMoveSpeed = 600;
    // untilTargetPos(15, 2000);
    // setChainPos(8, 3*24);
    // maxMoveSpeed = 600;
    // untilTargetPos(15, 2000);
    // setChainPos(12, 4*24);
    // maxMoveSpeed = 600;
    // kicker.target = 0;
    // kicker.velocity = 0;
    // kicker.moveVelocity(0);
    // untilTargetPos(15, 2000);
    // setChainPos(1*24+12, 5*24+18);
    // maxMoveSpeed = 600;
    // untilTargetPos(15, 2000);

    // setTargetPos(2*24-2, 5*24+18); // push 1
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 1500);
    // wings.retFrontWings();
    // if (positionError(targetX, targetY) > 5) { // extra pushes
    //     driveMode = 2;
    //     setTargetPos(12, 5*24-8);
    //     maxMoveSpeed = 300;
    //     untilTargetPos(5, 2000);
    //     driveMode = 1;
    //     setTargetPos(2*24-2, 5*24+18);
    //     maxMoveSpeed = 600;
    //     untilTargetPos(5, 750);
    //     // if (positionError(targetX, targetY) > 5) {
    //     //     driveMode = 2;
    //     //     setTargetPos(12, 5*24-4);
    //     //     maxMoveSpeed = 300;
    //     //     untilTargetPos(15, 2000);
    //     //     driveMode = 1;
    //     //     setTargetPos(2*24-2, 5*24+8);
    //     //     maxMoveSpeed = 600;
    //     //     untilTargetPos(5, 750);
    //     // }
    // }
    
    // driveDisabled = true;
    // botMove(-5, 450);
    // driveDisabled = false;
    // intake.moveVelocity(200);
    // driveMode = 2;
    // setTargetPos(1*24-8, 5*24-8); // align for herd 1
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 2000);
    // setTargetPos(2*24, 4*24+4);
    // setChainPos(1*24+12, 4*24+6);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // // wings.extBackWings(); // herd 1
    // wings.extBLWing(); // herd 1
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);
    // setChainPos(2*24, 4*24+2);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 2000);
    // wings.retBackWings();

    // driveMode = 1; // scoop corner 1
    // setTargetPos(1*24+12, 4*24-12);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 2000);
    // // setTargetPos(1*24+8, 3*24+12);
    // // maxMoveSpeed = 300;
    // // untilTargetPos(10, 2000);

    // setTargetPos(2*24+12, 5*24-8); // push 2
    // setChainPos(2*24+4, 4*24);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // intake.moveVelocity(-200);
    // wings.extFrontWings();
    // maxMoveSpeed = 600;
    // untilTargetPos(15, 2000);
    // setChainPos(2*24+12, 5*24-8);
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 1500);
    // if (positionError(targetX, targetY) > 5) { // extra pushes
    //     driveDisabled = true;
    //     botMove(-10, 300);
    //     driveDisabled = false;
    //     driveMode = 1;
    //     setTargetPos(2*24+12, 5*24-8);
    //     maxMoveSpeed = 600;
    //     untilTargetPos(5, 750);
    // }
    // wings.retFrontWings();

    // wings.extBLWing();
    // driveMode = 2;
    // setTargetPos(xPos, 3*24+12); // scoop barrier
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    // wings.extBackWings();
    // intake.moveVelocity(-200);

    // setTargetPos(3*24, 5*24-8); // push 3
    // setChainPos(3*24-6, 4*24);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // maxMoveSpeed = 600;
    // untilTargetPos(15, 2000);
    // setChainPos(3*24, 5*24-8);
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 1500);
    // if (positionError(targetX, targetY) > 5) { // extra pushes
    //     driveDisabled = true;
    //     botMove(5, 300);
    //     driveDisabled = false;
    //     driveMode = 2;
    //     setTargetPos(3*24, 5*24-8);
    //     maxMoveSpeed = 600;
    //     untilTargetPos(5, 750);
    // }
    // wings.retBackWings();

    // intake.moveVelocity(200);
    // driveMode = 1; // scoop corner 2
    // setTargetPos(5*24-24, 3*24+12);
    // setChainPos(3*24+4-12, 3*24+12);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);
    // setChainPos(4*24-12, 3*24+12);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);
    // setChainPos(5*24-12-12, 3*24+12);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    // setTargetPos(5*24-12-12, 5*24);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    
    // driveDisabled = true;
    // intake.moveVelocity(-200);
    // botMove(20, 600);
    // botMove(-15, 450);
    // driveDisabled = false;

    // driveMode = 2; // push 4
    // setTargetPos(3*24+6-6, 5*24-8);
    // setChainPos(3*24+18, 4*24);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // wings.extBackWings();
    // maxMoveSpeed = 600;
    // untilTargetPos(15, 2000);
    // setChainPos(3*24+12, 5*24-8);
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 2000);
    // if (positionError(targetX, targetY) > 5) { // extra pushes
    //     driveDisabled = true;
    //     botMove(5, 300);
    //     driveDisabled = false;
    //     driveMode = 2;
    //     setTargetPos(3*24+12, 5*24-8);
    //     maxMoveSpeed = 600;
    //     untilTargetPos(5, 750);
    // }
    // wings.retBackWings();
    
    // driveDisabled = true;
    // botMove(10, 600);
    // driveDisabled = false;

    // intake.moveVelocity(200);
    // driveMode = 1; // align for push 5
    // setTargetPos(5*24+12, 4*24+12);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    // setTargetPos(4*24+2, 5*24+8); 
    // setChainPos(4*24+12, 5*24+12);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // intake.moveVelocity(-200);
    // wings.extFrontWings();
    // setChainPos(4*24+12, 5*24+8);
    // maxMoveSpeed = 600;
    // untilTargetPos(15, 2000);

    // setTargetPos(4*24+2, 5*24+8); // push 5
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 1500);
    // wings.retFrontWings();
    // if (positionError(targetX, targetY) > 5) { // extra pushes
    //     driveMode = 2;
    //     setTargetPos(5*24+12, 5*24-4);
    //     maxMoveSpeed = 300;
    //     untilTargetPos(15, 2000);
    //     driveMode = 1;
    //     setTargetPos(4*24+2, 5*24+8);
    //     maxMoveSpeed = 600;
    //     untilTargetPos(5, 750);
    //     if (positionError(targetX, targetY) > 5) {
    //         driveMode = 2;
    //         setTargetPos(5*24+12, 5*24-4);
    //         maxMoveSpeed = 300;
    //         untilTargetPos(15, 2000);
    //         driveMode = 1;
    //         setTargetPos(4*24+2, 5*24+8);
    //         maxMoveSpeed = 600;
    //         untilTargetPos(5, 750);
    //     }
    // }

    // driveMode = 2; // climb
    // setTargetPos(5*24+12, 4*24+12);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 2000);
    // driveMode = 1;
    // climb.climbUp();
    // setTargetPos(5*24+10, 3*24-2);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    // driveDisabled = true;
    // botMove(-3, 450);
    // driveDisabled = false;
    // climb.climbDown();

    // kicker.target = 200;
    // kicker.velocity = 200;
    // kicker.moveVelocity(200);
    // wings.extBLWing();
    // pros::delay(500);
    // drive.odomPiston.set_value(true);
    // wings.retBLWing();
    // pros::delay(2000);
    // kicker.target = 0;
    // kicker.velocity = 0;
    // kicker.moveVelocity(0);


    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    print_task.suspend();
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void preautonomous(int curSelected) {
	odom_task.resume();
	kicker_task.resume();
	print_task.resume();
    drive.odomPiston.set_value(false);
    drive_auto_task.resume();
    // resumeAutoTasks();

    // bryan has a skill issue
	switch (curSelected) {
        case 1:
        closePreauton();
        break;

        case 2:
        closePreauton();
        break;

        case 3:
        closePreauton();
        break;

        case 4:
        farPreauton();
        break;

        case 5:
        farPreauton();
        break;

        case 6:
        skillsPreauton();
        break;
	}
}

#endif