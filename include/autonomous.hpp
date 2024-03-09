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

    // move(6, movePID, turnPID, 0, 250);
    // swerve(90, turnPID, 0, 250);
    // swerve(180, turnPID, 0, 250);
    // driveMode = 2;
    // swerve(90, turnPID, 0, 250);
    // driveMode = 1;
    
    // maxTurnSpeed = 600;
    // turn(90, turnPID, 0);
    driveDisabled = true;
    drive.moveVelocityLeft(-200);
    drive.moveVelocityRight(-200);
    if (!untilTargetPos(-1, 5000, true)) botMove(15, 200);
    pros::delay(500);
    drive.coast();
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
    controller.print(1, 0, "X:%.1f Y:%.1f H:%.1f          ", xPos, yPos, drive.imu.get_heading());
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

    driveMode = 1;
    setTargetPos(3*24+7, 2*24-2); // intake middle triball
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    intake.moveVelocity(-200);
    wings.extFrontWings();
    maxMoveSpeed = 600;
    pros::delay(500);
    wings.retFrontWings();
    intake.moveVelocity(200); 
    pros::delay(250);
    maxMoveSpeed = 300;
    untilTargetPos(7, 1000);

    driveMode = 2;
    setTargetPos(5*24+12, 1*24+6);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);

    setTargetPos(5*24+6, 1*24-6);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);
    intake.moveVelocity(-200);

    driveMode = 1;
    setTargetPos(xPos+200, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
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
    maxMoveSpeed = 300;
    untilTargetPos(5, 1000);
    
    driveMode = 1; // line up to touch pole
    // wings.extFrontWings();
    setTargetPos(5*24+14, 1*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);

    setTargetPos(5*24+14, 3*24-11); // turn towards pole
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 500);

    maxMoveSpeed = 300; // move to pole
    wings.extFrontWings();
    untilTargetPos(3, 2000);
    wings.retFrontWings();

    driveMode = 2;
    setTargetPos(5*24+6, 1*24-6);
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

/*
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
*/

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
    maxTurnSpeed = 600;
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
    setChainPos(5*24-4, 5*24+10);
    maxMoveSpeed = 300;
    untilTargetPos(30, 2000);
    intake.moveVelocity(0);
    untilTargetPos(15, 2000);
    setChainPos(5*24-4, 5*24+8);
    maxMoveSpeed = 300;
    untilTargetPos(5, 1000);
    // wings.retBLWing();
    wings.retBackWings();
    driveDisabled = true;
    pros::delay(250);
    driveDisabled = false;

    // setTargetPos(4*24, 5*24+18);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // driveDisabled = true;
    // drive.moveVelocityLeft(-600);
    // drive.moveVelocityRight(-600);
    // pros::delay(800);
    // // untilTargetPos(5, 1500);
    // driveDisabled = false;

    driveDisabled = true;
    // botMove(14, 600);
    wings.retBackWings();
    drive.moveVelocityLeft(450);
    drive.moveVelocityRight(-450);
    pros::delay(250);
    driveDisabled = false;
    driveMode = 1;
    setTargetPos(4*24, 5*24+18);
    maxMoveSpeed = 0;
    untilTargetH(25, 2000);
    intake.moveVelocity(-200);
    untilTargetH(5, 2000, 250);

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    botMove(-12, 450);
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
    setTargetPos(3*24+2, 3*24+8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 300;
    maxTurnSpeed = 0;
    untilTargetPos(5, 2000);
    
    setTargetPos(xPos, yPos+40); // score triball 3,4,5
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

void farElim6Preauton() {
    drive.hold();
    // maxTurnConstant = 20;
    drive.imu.set_heading(180);
    driveDisabled = false;
    setPos(5*24+6, 5*24-7.5);

    botMove(-3, 200);
    driveMode = 1;
    turn(heading(3*24, 4*24), turnPID, 0, 500);
    botMove(-1.5, 200);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    maxTurnSpeed = 600;
    // maxTurnConstant = 35;
    drive.stop();
}

void farElim6Auton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-200); // deploy intake
    driveMode = 1;
    wings.extFrontWings(); // launch alliance triball
    setTargetPos(3*24+4, 4*24+2); // rush triball 1
    setChainPos(4*24-4, 4*24+3);
    // setChainPos(3*24+4, 4*24+2);
    maxMoveSpeed = 600;
    untilTargetPos(25, 2000);
    wings.retFrontWings();
    untilTargetPos(15, 2000);
    intake.moveVelocity(200);
    // untilTargetPos(50, 2000);
    // wings.retFrontWings();
    // untilTargetPos(35, 2000);
    // intake.moveVelocity(200);
    setChainPos(3*24+2, 4*24+1);
    maxMoveSpeed = 600;
    untilTargetPos(8, 2000);

    // driveDisabled = true;
    // drive.stop();
    // pros::delay(500);
    // driveDisabled = false;
    // botMove(-10, 600);

    driveMode = 2; // come back
    setTargetPos(5*24+12, 4*24+16);
    setChainPos(4*24+16, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(5*24+12, 4*24+12);
    maxMoveSpeed = 600;
    untilTargetPos(5, 2000);

    driveMode = 2; // deposit triball
    setTargetPos(5*24+12, 3*24+20);
    maxMoveSpeed = 0;
    untilTargetH(30, 2000);
    intake.moveVelocity(-200);
    untilTargetH(15, 1000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(600);
    pros::delay(250);
    driveDisabled = false;
    intake.moveVelocity(200);
    driveMode = 1;
    setTargetPos(5*24+12, 3*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);

    botMove(yPos-3*24 - 8, 450); // intake triball 2
    wings.extBRWing();

    driveMode = 2; // move to goal, score alliance triball and triball 1+3
    setTargetPos(4*24, 5*24+16);
    setChainPos(5*24+12, 4*24+4);
    maxMoveSpeed = 600;
    untilTargetPos(15, 1000);
    setChainPos(5*24+10, 5*24-4);
    maxMoveSpeed = 450;
    untilTargetPos(15, 1000);
    wings.extBLWing(); // descore triball 3
    setChainPos(5*24-5, 5*24+7);
    maxMoveSpeed = 450;
    untilTargetPos(13.5, 750);
    wings.retBLWing();
    setChainPos(4*24+2, 5*24+16);
    maxMoveSpeed = 600;
    untilTargetPos(5, 750);

    botMove(10, 600);
    wings.retBRWing();
    driveMode = 1;
    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(-600);
    pros::delay(250);
    driveDisabled = false;
    setTargetPos(xPos-20, yPos+7); // turn around
    maxMoveSpeed = 0;
    untilTargetH(30, 2000);
    intake.moveVelocity(-200);
    untilTargetH(10, 2000);
    botMove(positionError(4*24+2, 5*24+16), 600);
    botMove(-15, 2000);

    setTargetPos(4*24+2, 3*24+8); // aim for and intake triball 4
    setChainPos(4*24+10, 4*24+8);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    intake.moveVelocity(200);
    maxMoveSpeed = 600;
    untilTargetPos(25, 2000);
    setChainPos(4*24+2, 3*24+8);
    maxMoveSpeed = 600;
    untilTargetPos(5, 1000);

    setTargetPos(3*24+16, 5*24); // score triball 4
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    intake.moveVelocity(-200);
    // wings.extFrontWings();
    maxMoveSpeed = 450;
    untilTargetPos(5, 1250);
    // wings.retFrontWings();

    botMove(-15, 600); // intake triball 5
    setTargetPos(3*24+1, 3*24+8);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    intake.moveVelocity(200);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);

    setTargetPos(3*24+5, 5*24); // score triball 5
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    intake.moveVelocity(-200);
    wings.extFrontWings();
    maxMoveSpeed = 600;
    untilTargetPos(5, 1250);
    wings.retFrontWings();

    botMove(-20, 600);
    
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

    // driveMode = 2;
    // swerve(109.7, 11, turnPID, 0, 500);
    // botMove(5, 300);

    driveMode = 2;
    maxTurnSpeed = 600;
    swerve(4*24, 12, swervePID2, 0, 500);
    botMove(4, 300);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    drive.stop();
}

void skillsSegA() {
    maxTurnSpeed = 600;
    driveDisabled = false;

    intake.moveVelocity(-200); // ram in triballs
    // wings.extBLWing();
    kicker.target = 170;
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(0, 1500, true, 5);
    botMove(12, 450);
    // wings.retBLWing();
    driveDisabled = false;

    driveMode = 1; // move to shooting position
    kicker.target = 170;
    kicker.velocity = 170;
    kicker.moveVelocity(170);
    // setTargetPos(105.7, 17);
    // // maxMoveSpeed = 0;
    // // untilTargetH(10, 2000);
    // maxMoveSpeed = 300;
    // untilTargetPos(3, 2000);

    driveMode = 1;
    setTargetPos(3*24, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    botMove(-4, 450);
    wings.extBRWing();
    while(!updateButtons()) {
        kicker.target = 170;
        kicker.velocity = 170;
        kicker.moveVelocity(170);
        intake.moveVelocity(-200);

        pros::delay(10);
    }

    wings.retBackWings();
}

void skillsAuton() {
    double start = pros::millis();
    maxTurnSpeed = 600;
    driveDisabled = false;

    intake.moveVelocity(-200); // ram in triballs
    // wings.extBLWing();
    kicker.target = 170;
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(0, 1500, true, 5);
    botMove(12, 450);
    // wings.retBLWing();
    driveDisabled = false;

    driveMode = 1; // move to shooting position
    kicker.target = 170;
    kicker.velocity = 170;
    kicker.moveVelocity(170);
    // setTargetPos(105.7, 17);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // maxMoveSpeed = 300;
    // untilTargetPos(3, 2000);

    driveMode = 1;
    setTargetPos(3*24, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    botMove(-4, 450);
    wings.extBRWing();
    int t = 0;
    while(t < 2500) {
    // while(t < 18000) {
        kicker.target = 170;
        kicker.velocity = 170;
        kicker.moveVelocity(170);
        intake.moveVelocity(-200);
        if (t == 10000) setTargetPos(3*24-0.5, 5*24);

        pros::delay(10);
        t += 10;
    }
    wings.retBRWing();
    untilKeyPress();

    maxMoveSpeed = 0; // push triballs over barrier
    driveMode = 1;
    setTargetPos(1*24+10, 3*24-8);
    setChainPos(4*24+10, 1*24+12);
    maxMoveSpeed = 450;
    untilTargetPos(25, 2000);
    setChainPos(3*24+8, 2*24+4);
    maxMoveSpeed = 450;
    untilTargetPos(30, 2000);
    wings.extFrontWings();
    untilTargetPos(15, 2000);
    setChainPos(2*24+12, 3*24-8);
    maxMoveSpeed = 600;
    untilTargetPos(25, 2000);
    setChainPos(1*24+12, 3*24-8);
    maxMoveSpeed = 450;
    untilTargetPos(5, 1500, true);

    driveDisabled = true;
    wings.retFrontWings();
    botMove(-15, 450);
    // setTargetPos(xPos-200, yPos);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    botMove(xPos-(1*24+10)+10, 450);
    intake.moveVelocity(200);
    botMove(-15, 450);
    driveDisabled = false;

    driveMode = 1; // align for alley push
    // setTargetPos(xPos-12, 24);
    setTargetPos(xPos-12, 1*24+10);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    intake.moveVelocity(0);
    maxMoveSpeed = 300;
    // untilTargetPos(15, 2000);
    // driveMode = 0;
    // setChainPos(xPos-12, 24);
    // maxMoveSpeed = 450;
    if(!untilTargetPos(15, 2000, true, 10)) botMove(-5, 450);
    // setTargetPos(xPos-200, yPos-50);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    driveMode = 1;
    maxTurnSpeed = 400;
    swerve(12, 2*24+12, swervePID2, 1500, 0, 15);
    maxTurnSpeed = 600;

    driveMode = 1; // alley push
    intake.moveVelocity(-200);
    setTargetPos(xPos-20, yPos+100);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    setTargetPos(12, 4*24);
    setChainPos(12, 2*24);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(8, 3*24);
    maxMoveSpeed = 600;
    untilTargetPos(25, 2000);
    wings.extFrontWings();
    kicker.target = 0;
    kicker.velocity = 0;
    kicker.moveVelocity(0);
    setChainPos(12, 4*24+8);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // wings.retFrontWings();
    // botMove(-15, 450);
    // botMove(-5, 450);
    // setTargetPos(xPos,yPos+19);
    // untilTargetPos(15, 2000);

    // odomTPID.setTo(turnPID3);
    // driveMode = 2;
    // // driveDisabled = true;
    // // drive.moveVelocityLeft(600);
    // // drive.moveVelocityRight(-600);
    // // pros::delay(250);
    // // driveDisabled = false;
    // setTargetPos(2*24+2, 5*24+12);
    // setChainPos(xPos-200, yPos);
    // maxMoveSpeed = 0;
    // untilTargetH(60, 2000);
    // setChainPos(xPos+20, yPos+200);
    // maxMoveSpeed = 0;
    // untilTargetH(15, 2000);
    // odomTPID.setTo(turnPID);
    // setChainPos(1*24+15, 5*24+8);
    setTargetPos(xPos+160, yPos+200);
    maxMoveSpeed = 250;
    untilTargetH(10, 1500);
    setTargetPos(2*24+2, 5*24+12);
    // wings.extBLWing();
    // maxMoveSpeed = 250;
    // untilTargetPos(25, 2000);
    // setChainPos(2*24+2, 5*24+12); // push 1
    // maxMoveSpeed = 600;
    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(500);
    untilTargetPos(5, 1500, true);
    wings.retFrontWings();
    // if (xPos < 2*24-4) { // extra pushes
        botMove(-10, 600);
        // untilTargetPos(10, 2000);
        // driveMode = 2;
        // setTargetPos(2*24, 5*24+16);
        // maxMoveSpeed = 0;
        // untilTargetH(10, 1000);
        drive.moveVelocityLeft(600);
        drive.moveVelocityRight(600);
        untilTargetPos(-1, 1500, true);
        setPos(3*24-30.5, 6*24-10);
    driveDisabled = false;
    // }
    wings.retBackWings();
    botMove(-5, 450);
   
    driveMode = 2;
    setTargetPos(24, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);

    intake.moveVelocity(-200);
    driveMode = 1;
    setTargetPos(2*24+12, 5*24-4); // align for herd 1
    setChainPos(1+24+12,4*24+10);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(25, 2000);
    setChainPos(2*24-4,4*24-8);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    setTargetPos(xPos+250, yPos+450);
    maxMoveSpeed = 0;
    untilTargetH(30, 2000);
    setChainPos(2*24+16, 5*24-6);
    // maxMoveSpeed = 0;
    // untilTargetH(15, 2000);
    wings.extFrontWings();
    // setChainPos(2*24+16, 5*24-6);
    maxMoveSpeed = 600;
    untilTargetPos(5, 1500, true);
    // if (targetY-yPos > 5) { // extra pushes
        botMove(-10, 450);
        setChainPos(xPos, yPos+200);
        maxMoveSpeed = 0;
        untilTargetH(10, 500);
        driveDisabled = true;
        drive.moveVelocityLeft(600);
        drive.moveVelocityRight(600);
        untilTargetPos(-1, 1500, true);
        driveDisabled = false;
    // }
    wings.retFrontWings();
    botMove(-10, 450);

    driveMode = 1; // scoop corner 1
    // setTargetPos(1*24+12, 4*24-8);
    setTargetPos(2*24, 4*24-8);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000, true);
    // setTargetPos(xPos, yPos+200);
    // maxMoveSpeed = 0;
    // untilTargetH(15, 1000);
    // wings.extBLWing();
    driveMode = 2;
    setTargetPos(3*24+12, fmin(yPos-8, 3*24+8));
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    setTargetPos(3*24+4, 5*24-3); // push 4
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    wings.extBackWings();
    maxMoveSpeed = 600;
    untilTargetPos(5, 1500, true);
    // if (targetY-yPos > 5) { // extra pushes
        botMove(10, 450);
        // setChainPos(xPos, yPos+200);
        // maxMoveSpeed = 0;
        // untilTargetH(10, 500);
        driveDisabled = true;
        drive.moveVelocityLeft(-600);
        drive.moveVelocityRight(-600);
        untilTargetPos(-1, 1500, true);
        driveDisabled = false;
        // setPos(xPos, 6*24-33.5);
    // }
    botMove(10, 450);
    wings.retBackWings();

    driveMode = 1;
    setTargetPos(3*24, 4*24-12);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    // wings.extBLWing();
    // untilTargetH(5, 2000);
    // driveMode = 2;
    driveMode = 1;
    intake.moveVelocity(0);
    setTargetPos(4*24, 3*24+4); // scoop corner 2
    setChainPos(3*24+12, 3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(4*24+8, 3*24+10);
    maxMoveSpeed = 300;
    untilTargetPos(10, 1000, true);
    setTargetPos(4*24+12, 4*24+8);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    intake.moveVelocity(-200);
    maxMoveSpeed = 450;
    untilTargetPos(10, 1000);
    botMove(-10, 450);
    driveMode = 2;
    setTargetPos(3*24+12, 5*24-6);
    setChainPos(4*24, 4*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    // wings.retBLWing();
    wings.extBackWings();
    // maxMoveSpeed = 450;
    // untilTargetPos(25, 2000);
    // setChainPos(4*24, 4*24+12);
    // maxMoveSpeed = 350;
    // untilTargetPos(10, 2000);
    arcMovement = true;
    setChainPos(3*24+16, 5*24-6); // push 3
    maxMoveSpeed = 600;
    int timer = 1500;
    while (positionError(targetX, targetY) > 5 && fabs(headingError(180)) > 10 && timer > 0) {
        timer -= 10;
        pros::delay(10);
    }
    arcMovement = false;
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(-1, 1500, true);
    driveDisabled = false;
    // if (targetY-(5*24-6) > 5) { // extra pushes
        botMove(10, 450);
        setChainPos(xPos, yPos+200);
        maxMoveSpeed = 0;
        untilTargetH(10, 500);
        driveDisabled = true;
        drive.moveVelocityLeft(-600);
        drive.moveVelocityRight(-600);
        untilTargetPos(-1, 1500, true);
        driveDisabled = false;
        setPos(xPos, 6*24-33.5);
    // }
    botMove(10, 450);
    wings.retBackWings();

    intake.moveVelocity(0);
    driveMode = 2; // align for push 5
    setTargetPos(5*24+12, 4*24+12);
    setChainPos(4*24+12, 4*24+10);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // wings.extFrontWings();
    intake.moveVelocity(-200);
    // setChainPos(xPos, yPos+200);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // // wings.retFrontWings();
    // driveMode = 2;
    setChainPos(5*24+12, 4*24+12);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // setTargetPos(5*24+8, 5*24+);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // botMove(positionError(targetX, targetY), 300);
    setTargetPos(4*24+5, 5*24+12); 
    setChainPos(xPos, yPos+400);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    // intake.moveVelocity(-200);
    botMove(15, 450);
    setChainPos(xPos-150, yPos+400);
    maxMoveSpeed = 0;
    untilTargetH(15, 1000);
    driveMode = 2;
    wings.extBRWing();
    setChainPos(5*24-2, 5*24);
    maxMoveSpeed = 450;
    untilTargetPos(15, 1000);

    setChainPos(4*24+4, 5*24+12); // push 5
    maxMoveSpeed = 600;
    untilTargetPos(5, 1000, true);
    // if (xPos-targetX > 5 && (pros::millis() - start) > 5000) { // extra pushes
        botMove(10, 450);
        // setChainPos(4*24+4, 5*24+16);
        // maxMoveSpeed = 0;
        // untilTargetH(10, 1000);
        driveDisabled = true;
        drive.moveVelocityLeft(-600);
        drive.moveVelocityRight(-600);
        untilTargetPos(-1, 1500, true);
        driveDisabled = false;
        setPos(3*24+33.5, yPos);
        // botMove(10, 450);
        // botMove(-30, 600);
    // }

    driveMode = 1; // climb
    setTargetPos(5*24+12, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    wings.retBRWing();
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    climb.climbUp();
    setTargetPos(xPos, 3*24-6);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 450;
    untilTargetPos(20, 2000);
    driveDisabled = true;
    drive.moveVelocityLeft(450);
    drive.moveVelocityRight(450);
    pros::delay(250);
    std::cout << drive.imu.get_roll() << std::endl;
    while (fabs(drive.imu.get_roll()) < 15) {
        drive.moveVelocityLeft(450);
        drive.moveVelocityRight(450);
        pros::delay(10);
    }
    pros::delay(100);
    // maxMoveSpeed = 300;
    // untilTargetPos(5, 1000, true, 10);
    driveDisabled = true;
    botMove(-3, 450);
    // driveDisabled = false;
    climb.climbDown();

    kicker.target = 200;
    kicker.velocity = 200;
    kicker.moveVelocity(200);
    pros::delay(500);
    drive.stop();
    drive.odomPiston.set_value(true);
    pros::delay(2000);
    kicker.target = 0;
    kicker.velocity = 0;
    kicker.moveVelocity(0);

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

/*

    double start = pros::millis();
    driveDisabled = false;

    intake.moveVelocity(-200); // move to shooting position
    kicker.target = 170;
    driveMode = 2;
    kicker.target = 170;
    kicker.velocity = 170;
    kicker.moveVelocity(170);
    setTargetPos(109.7, 11);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);

    driveMode = 1;
    setTargetPos(3*24, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    botMove(-3, 450);
    wings.extBRWing();
    int t = 0;
    while(t < 21000) {
        kicker.target = 170;
        kicker.velocity = 170;
        kicker.moveVelocity(170);
        intake.moveVelocity(-200);

        pros::delay(10);
        t += 10; 
    }
    wings.retBRWing();
    untilKeyPress();

    maxMoveSpeed = 0; // push triballs over barrier
    driveMode = 1;
    setTargetPos(1*24+10, 3*24-8);
    setChainPos(4*24+10, 1*24+12);
    maxMoveSpeed = 450;
    untilTargetPos(25, 2000);
    setChainPos(3*24+8, 2*24);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    wings.extFrontWings();
    setChainPos(2*24+12, 3*24-12);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setChainPos(1*24+10, 3*24-8);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);

    driveDisabled = true;
    wings.retFrontWings();
    botMove(-15, 450);
    botMove(xPos-(1*24+10)+10, 450);
    intake.moveVelocity(200);
    botMove(-15, 450);
    driveDisabled = false;

    driveMode = 1; // align for alley push
    // setTargetPos(1*24+12, 1*24);
    // setChainPos(1*24+14, 1*24+16);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);
    // setChainPos(1*24+12, 1*24);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    setTargetPos(1*24+12, 1*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    setTargetPos(xPos-400, yPos-200);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);

    maxTurnSpeed = 275;
    swerve(12, 3*24+8, turnPID, 2000, 0, 10);
    maxTurnSpeed = 350;
    // setTargetPos(12, 1*24+12);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);

    driveMode = 1; // alley push
    wings.extFrontWings();
    intake.moveVelocity(-200);
    setTargetPos(2*24-2, 5*24+14);
    setChainPos(12, 2*24);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setChainPos(8, 3*24);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    kicker.target = 0;
    kicker.velocity = 0;
    kicker.moveVelocity(0);
    setChainPos(12, 4*24);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setChainPos(1*24+12, 5*24+8);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setChainPos(2*24, 5*24+12); // push 1
    maxMoveSpeed = 600;
    untilTargetPos(5, 1000);
    wings.retFrontWings();
    if (targetX-xPos > 5) { // extra pushes
        botMove(-10, 450);
        setTargetPos(2*24, 5*24+16);
        maxMoveSpeed = 0;
        untilTargetH(10, 1000);
        botMove(20, 600);
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
    botMove(-5, 450);
   
    driveMode = 2;
    setTargetPos(24, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);

    intake.moveVelocity(-200);
    driveMode = 1;
    setTargetPos(2*24+12, 5*24-4); // align for herd 1
    setChainPos(1+24+12, 4*24+10);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(25, 2000);
    setChainPos(2*24, 4*24-8);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);
    setTargetPos(xPos+400, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    maxTurnSpeed = 350;
    swerve(2*24+16, 5*24-2, turnPID, 2000, 0, 10);
    wings.extFrontWings();
    setChainPos(2*24+16, 5*24-6);
    maxMoveSpeed = 600;
    // maxTurnSpeed = 500;
    untilTargetPos(5, 1500);
    // maxTurnSpeed = 350;
    if (targetY-yPos > 5) { // extra pushes
        botMove(-10, 450);
        setChainPos(xPos, yPos+200);
        maxMoveSpeed = 0;
        untilTargetH(10, 500);
        botMove(25, 600);
    }
    wings.retFrontWings();
    botMove(-5, 450);

    driveMode = 2; // scoop corner 1
    setTargetPos(1*24+12, 4*24-8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    wings.extBLWing();
    setTargetPos(4*24, 3*24+4); // scoop corner 2
    setChainPos(2*24+12, 3*24+8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(4*24, 3*24+8);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    setTargetPos(4*24+16, 4*24-8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    setTargetPos(3*24+12, 5*24-6);
    setChainPos(4*24, 4*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    wings.retBLWing();
    wings.extBRWing();
    maxMoveSpeed = 450;
    untilTargetPos(25, 2000);
    setChainPos(4*24, 4*24+12);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    setChainPos(3*24+16, 5*24-6); // push 3
    maxMoveSpeed = 600;
    untilTargetPos(5, 1500);
    if (targetY-(5*24-6) > 5) { // extra pushes
        botMove(10, 450);
        setChainPos(xPos, yPos+200);
        maxMoveSpeed = 0;
        untilTargetH(10, 500);
        botMove(-25, 600);
    }
    botMove(10, 450);
    wings.retBackWings();

    // driveMode = 1;
    // setTargetPos(4*24, 3*24+12);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 2000);
    // setTargetPos(3*24, 3*24+8);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);

    // // swerve(3*24, 5*24-2, turnPID, 2000, 0, 10);
    // setTargetPos(3*24, 5*24-6); // push 4
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // wings.extFrontWings();
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 1500);
    // setTargetPos(xPos, yPos+200);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 500);
    // if (targetY-(5*24-6) > 5) { // extra pushes
    //     driveDisabled = true;
    //     botMove(-10, 450);
    //     driveDisabled = false;
    //     driveMode = 1;
    //     setTargetPos(3*24, 5*24-6);
    //     maxMoveSpeed = 600;
    //     untilTargetPos(5, 1000);
    // }
    // botMove(-10, 450);
    // wings.retBackWings();

    intake.moveVelocity(200);
    driveMode = 1; // align for push 5
    setTargetPos(5*24+12, 4*24+16);
    setChainPos(4*24+12, 4*24+16);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(5*24+12, 4*24+16);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // setTargetPos(5*24+8, 5*24+);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // botMove(positionError(targetX, targetY), 300);
    setTargetPos(4*24+5, 5*24+12); 
    setChainPos(xPos-200, yPos+400);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    intake.moveVelocity(-200);
    wings.extFrontWings();
    setChainPos(4*24+2, 5*24+12);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);

    setChainPos(4*24+4, 5*24+12); // push 5
    maxMoveSpeed = 600;
    untilTargetPos(5, 1500);
    wings.retFrontWings();
    if (xPos-targetX > 5) { // extra pushes
        botMove(-10, 450);
        setChainPos(4*24+4, 5*24+16);
        maxMoveSpeed = 0;
        untilTargetH(10, 1000);
        botMove(20, 600);
    }

    driveMode = 1; // climb
    setTargetPos(xPos+400, yPos-200);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    wings.extBRWing();
    botMove(-8, 600);
    // setTargetPos(5*24+12, 4*24+12);
    setTargetPos(xPos+400, yPos-200);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    pros::delay(500);
    wings.retBRWing();
    untilTargetPos(10, 2000);
    // climb.climbUp();
    // setTargetPos(xPos+2, 3*24-6);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000, 250);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);
    // driveDisabled = true;
    botMove(-3, 450);
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
*/

/*
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
    kicker.moveVelocity(0);*/

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
        farElim6Preauton();
        break;

        case 7:
        skillsPreauton();
        break;
	}
}

#endif