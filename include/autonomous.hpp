#ifndef AUTONOMOUS_HPP
#define AUTONOMOUS_HPP

#include "setup.hpp"
#include "tasks.hpp"
#include "teleop.hpp"

void testAuton() {
    drive.hold();
    drive.imu.set_heading(180);
    setPos(0, 0);
    arcMovement = false;
    driveDisabled = false;
    driveMode = 1;

    maxMoveSpeed = 0;
    setTargetPos(xPos-24, yPos+48);
    driveMode = 1;
    untilTargetH(90, 2000);
    // pros::delay(1000);
    // untilTargetPos(1, 5000);
    // maxMoveSpeed = 0;
    print_task.suspend();
    pros::delay(2500);
    controller.print(0, 0, "%.0f                             ", (positionError(targetX, targetY)));
    pros::delay(2500);
    print_task.resume();
    driveDisabled = true;
    drive.stop();
}

void noAuton() {}

void closeSafePreauton() {
    // maxTurnConstant = 20;
    drive.hold();
    drive.imu.set_heading(0);
    driveDisabled = false;
    setPos(5*24+6, 1*24+7.5);

    // driveMode = 2;
    // setTargetPos(5*24+12, 1*24);
    // maxMoveSpeed = 0;
    // untilTargetH(2, 3000);
    // pros::delay(1000);

    // maxMoveSpeed = 150;
    // untilTargetPos(3, 4000);

    // driveMode = 1;
    // setTargetPos(xPos+200, xPos+200);
    // maxMoveSpeed = 0;
    // untilTargetH(2, 3000);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    // maxTurnConstant = 35;
    drive.stop();
}

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
    setTargetPos(5*24+12, 1*24+12);
    maxMoveSpeed = 200;
    untilTargetPos(10, 2000);

    setTargetPos(5*24+8, 3*24-11); // turn towards pole
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 500);

    maxMoveSpeed = 200; // move to pole
    wings.extFrontWings();
    untilTargetPos(3, 2000);
    pros::delay(500);
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
    wings.extBRWing(); // descore triball
    driveMode = 1;
    // setTargetPos(5*24+12, 1*24+10);
    // maxMoveSpeed = 300;
    // untilTargetPos(5, 2000);
    setTargetPos(xPos, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    wings.retBackWings();

    intake.moveVelocity(200); // intake middle triball
    setTargetPos(3*24+8, 2*24-4);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 600;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    botMove(-10, 450);
    driveDisabled = false;

    driveMode = 2;
    setTargetPos(4*24, 2*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    intake.moveVelocity(0);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);

    driveMode = 1;
    setTargetPos(5*24-2, yPos+2);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 500);
    intake.moveVelocity(-200); // push triballs over barrier
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    maxMoveSpeed = 200;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    botMove(-10, 450);
    driveDisabled = false;

    setTargetPos(3*24+8, 2*24+16); // intake second triball
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    intake.moveVelocity(200);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    botMove(-10, 300);
    driveDisabled = false;

    driveMode = 2; // move back
    setTargetPos(5*24+5, 1*24+2);
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

    setTargetPos(xPos, 3*24-11); // turn towards pole
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
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void closeElimPreauton() {
    drive.hold();
    // maxTurnConstant = 20;
    drive.imu.set_heading(-90);
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
    // maxTurnConstant = 35;
    driveMode = 0;
    maxMoveSpeed = 450;
    drive.stop();

}

void closeElimAuton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-200); // deploy intake
    wings.extFrontWings(); // launch alliance triball
    driveMode = 1; // rush middle triball
    setTargetPos(3*24+10, 2*24-2);
    pros::delay(500);
    intake.moveVelocity(200);
    wings.retFrontWings();
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    botMove(-7, 450);
    pros::delay(500);
    driveDisabled = false;
    
    setTargetPos(xPos, yPos + 100);
    wings.extFrontWings();
    maxMoveSpeed = 0;
    // intake.moveVelocity(0);
    untilTargetH(5, 2000);
    // intake.moveVelocity(-200);
    pros::delay(500);

    driveDisabled = true;
    botMove(20, 300);
    pros::delay(500);
    driveDisabled = false;
    // setTargetPos(xPos, 3*24-12);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    wings.retFrontWings();
    // intake.moveVelocity(-200);
    // setTargetPos(5*24, 2*24+12); // outtake triball
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000, 250);

    // intake.moveVelocity(200);
    // setTargetPos(3*24-6, 3*24-6); // turn to other triball
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000, 500);

    // driveDisabled = true;
    // botMove(positionError(targetX, targetY), 300);
    // botMove(-7, 450);
    // driveDisabled = false;
    // // maxMoveSpeed = 300; // intake other triball
    // // untilTargetPos(3, 2000);
    
    // setTargetPos(5*24-10, 2*24+12); // turn to barrier
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000, 250);
    // intake.moveVelocity(-200);
    // wings.extFrontWings();
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    // wings.retFrontWings();

    setTargetPos(4*24+14, 1*24+12); // move to descore triball
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    driveMode = 2;
    setTargetPos(5*24-6, 15);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 200;
    untilTargetPos(5, 2000);

    driveMode = 1;
    setTargetPos(5*24+12, 1*24); // align robot
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);

    wings.extBRWing(); // descore triball
    setTargetPos(5*24+12, 1*24);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    setTargetPos(5*24+12, 1*24+8);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    setTargetPos(xPos, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    intake.moveVelocity(-200);
    wings.retBackWings();
    
    driveMode = 2; // score alliance triball
    setTargetPos(5*24, 24);
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
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);

    setTargetPos(5*24+14, 3*24-12); // turn towards pole
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 500);

    maxMoveSpeed = 300; // move to pole
    untilTargetPos(8.5, 2000);

    driveMode = 2; // align for loading
    setTargetPos(5*24+4, 20);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    drive.stop();
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
    setChainPos(5*24+2, 5*24+8);
    maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // // driveDisabled = true;
    // // drive.moveVelocityLeft(-600);
    // // drive.moveVelocityRight(-600);
    // // pros::delay(1000);
    // // // untilTargetPos(5, 1500);
    // // driveDisabled = false;

    driveDisabled = true;
    botMove(5, 450);
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
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1500);
    botMove(-15, 450);
    driveDisabled = false;

    intake.moveVelocity(200); // intake triball 3
    setTargetPos(4*24-4, 3*24+9);
    setChainPos(4*24, 4*24-5);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(4*24-4, 3*24+9);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    botMove(-5, 450);
    intake.moveVelocity(0);
    driveDisabled = false;
    
    setTargetPos(3*24+12, 5*24-4); // deposit triball 3
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    intake.moveVelocity(-200);
    pros::delay(500);
    
    intake.moveVelocity(200); // intake triball 4
    setTargetPos(3*24+3, 3*24+8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);
    
    intake.moveVelocity(0); // score triball 3,4,5
    setTargetPos(xPos, yPos+40);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    
    driveDisabled = true;
    wings.extFrontWings();
    intake.moveVelocity(-200);
    botMove(48, 450);
    intake.moveVelocity(0);
    botMove(-20, 450);
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
    double start = pros::millis();
    driveDisabled = true;
    intake.moveVelocity(600);
    drive.moveVelocityLeft(-500);
    drive.moveVelocityRight(-500);
    pros::delay(800);
    driveDisabled = false;

    maxMoveSpeed = 0;
    driveMode = 1;
    setTargetPos(5*24-7, 1*24-8);
    untilTargetH(15, 3000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 3000);
    maxMoveSpeed = 0;
    driveMode = 1;
    setTargetPos(3*24+18, 5*24);
    untilTargetH(5, 3000);
    pros::delay(250);
    drive.stop();
    driveMode = 0;
    maxMoveSpeed = 450;

    driveDisabled = true;
    botMove(-3, 200);
    kickerMode = 1;
}

void skillsAuton() {
    double start = pros::millis();
    driveDisabled = false;

    intake.moveVelocity(-200); // move to shooting position
    kicker.target = 200;
    driveMode = 2;
    setTargetPos(5*24-3, 8);
    wings.extBRWing();
    arcMovement = true;
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    arcMovement = false;

    driveMode = 1;
    setTargetPos(3*24, 5*24);
    maxMoveSpeed = 0;
    drive.stop();
    int t = 0;
    while(t < 2500) {
        kicker.target = 180;
        kicker.velocity = 180;
        kicker.moveVelocity(180);
        intake.moveVelocity(-200);

        pros::delay(10);
        t += 10;
    }
    wings.retBRWing();
    kicker.target = 40;
    kicker.velocity = 40;
    kicker.moveVelocity(40);
    untilKeyPress();

    maxMoveSpeed = 0; // push triballs over barrier
    driveMode = 1;
    setTargetPos(4*24+12, 1*24+12);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    wings.extFrontWings();
    setTargetPos(3*24+12, 3*24-12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setTargetPos(2*24+12, 3*24-8);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setTargetPos(1*24+12, yPos);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    wings.retFrontWings();
    botMove(-10, 450);
    untilKeyPress();
    botMove(10, 450);
    untilKeyPress();
    botMove(-10, 450);
    untilKeyPress();
    driveDisabled = false;

    driveMode = 2; // align for alley push
    setTargetPos(1*24+12, 12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);

    driveMode = 1;
    setTargetPos(12, 1*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    wings.extFrontWings();
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setTargetPos(8, 3*24);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    kicker.target = 0;
    kicker.velocity = 0;
    kicker.moveVelocity(0);
    setTargetPos(12, 4*24+12);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setTargetPos(1*24+12, 5*24+8);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);

    setTargetPos(2*24-2, 5*24+8); // push 1
    maxMoveSpeed = 600;
    untilTargetPos(5, 750);
    wings.retFrontWings();
    if (positionError(targetX, targetY) > 5) { // extra pushes
        driveMode = 2;
        setTargetPos(12, 5*24-4);
        maxMoveSpeed = 300;
        untilTargetPos(15, 2000);
        driveMode = 1;
        setTargetPos(2*24-2, 5*24+8);
        maxMoveSpeed = 600;
        untilTargetPos(5, 750);
        // if (positionError(targetX, targetY) > 5) {
        //     driveMode = 2;
        //     setTargetPos(12, 5*24-4);
        //     maxMoveSpeed = 300;
        //     untilTargetPos(15, 2000);
        //     driveMode = 1;
        //     setTargetPos(2*24-2, 5*24+8);
        //     maxMoveSpeed = 600;
        //     untilTargetPos(5, 750);
        // }
    }
    
    intake.moveVelocity(200);
    setTargetPos(1*24, 5*24); // align for herd 1
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    driveMode = 2;
    setTargetPos(1*24+12, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    wings.extBackWings(); // herd 1
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setTargetPos(2*24, 4*24+4);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    wings.retBackWings();

    driveMode = 1; // scoop corner 1
    setTargetPos(1*24+12, 4*24);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setTargetPos(1*24+8, 3*24+12);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);

    setTargetPos(2*24+6, 4*24); // push 2
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    intake.moveVelocity(-200);
    wings.extFrontWings();
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setTargetPos(2*24+12, 5*24);
    maxMoveSpeed = 600;
    untilTargetPos(5, 1000);
    if (positionError(targetX, targetY) > 5) { // extra pushes
        driveDisabled = true;
        botMove(-5, 300);
        driveDisabled = false;
        driveMode = 1;
        setTargetPos(2*24+12, 5*24);
        maxMoveSpeed = 600;
        untilTargetPos(5, 750);
    }
    wings.retFrontWings();

    wings.extBLWing();
    driveMode = 2;
    setTargetPos(2*24+8, 3*24+12); // scoop barrier
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    intake.moveVelocity(200);

    setTargetPos(3*24, 4*24); // push 3
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    wings.extBackWings();
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setTargetPos(3*24, 5*24);
    maxMoveSpeed = 600;
    untilTargetPos(5, 1000);
    if (positionError(targetX, targetY) > 5) { // extra pushes
        driveDisabled = true;
        botMove(5, 300);
        driveDisabled = false;
        driveMode = 2;
        setTargetPos(2*24+12, 5*24);
        maxMoveSpeed = 600;
        untilTargetPos(5, 750);
    }
    wings.retBackWings();

    driveMode = 1; // scoop corner 2
    setTargetPos(3*24+4, 3*24+12);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setTargetPos(4*24, 3*24+8);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setTargetPos(5*24-6, 3*24+8);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    setTargetPos(5*24-12, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    
    driveDisabled = true;
    intake.moveVelocity(-200);
    botMove(20, 600);
    botMove(-15, 450);
    driveDisabled = false;

    driveMode = 2; // push 4
    setTargetPos(3*24+12, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    wings.extBackWings();
    maxMoveSpeed = 600;
    untilTargetPos(5, 2000);
    if (positionError(targetX, targetY) > 5) { // extra pushes
        driveDisabled = true;
        botMove(5, 300);
        driveDisabled = false;
        driveMode = 2;
        setTargetPos(2*24+12, 5*24);
        maxMoveSpeed = 600;
        untilTargetPos(5, 750);
    }
    wings.retBackWings();

    intake.moveVelocity(200);
    driveMode = 1; // align for push 5
    setTargetPos(4*24+12, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    setTargetPos(4*24+12, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setTargetPos(5*24+12, 4*24+12);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    setTargetPos(4*24+12, 5*24+8);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    wings.extFrontWings();
    maxMoveSpeed = 600;
    untilTargetH(15, 2000);

    setTargetPos(4*24+2, 5*24+8); // push 5
    maxMoveSpeed = 600;
    untilTargetPos(5, 750);
    wings.retFrontWings();
    if (positionError(targetX, targetY) > 5) { // extra pushes
        driveMode = 2;
        setTargetPos(5*24+12, 5*24-4);
        maxMoveSpeed = 300;
        untilTargetPos(15, 2000);
        driveMode = 1;
        setTargetPos(4*24+2, 5*24+8);
        maxMoveSpeed = 600;
        untilTargetPos(5, 750);
        if (positionError(targetX, targetY) > 5) {
            driveMode = 2;
            setTargetPos(5*24+12, 5*24-4);
            maxMoveSpeed = 300;
            untilTargetPos(15, 2000);
            driveMode = 1;
            setTargetPos(4*24+2, 5*24+8);
            maxMoveSpeed = 600;
            untilTargetPos(5, 750);
        }
    }

    driveMode = 2; // climb
    setTargetPos(5*24+12, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    driveMode = 1;
    climb.climbUp();
    setTargetPos(5*24+10, 3*24-2);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    driveDisabled = true;
    botMove(-3, 450);
    driveDisabled = false;
    climb.climbDown();

    wings.extBLWing();
    pros::delay(500);
    wings.retBLWing();


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

	switch (curSelected) {
        case 1:
        closeSafePreauton();
        break;

        case 2:
        closePreauton();
        break;

        case 3:
        closeElimPreauton();
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