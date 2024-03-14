#ifndef AUTONOMOUS_HPP
#define AUTONOMOUS_HPP

#include "setup.hpp"
#include "tasks.hpp"
#include "teleop.hpp"
#include "skills.hpp"

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

void closeStealAuton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-200); // deploy intake
    driveDisabled = true;
    pros::delay(250);
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
    drive.stop();
    pros::delay(250);
    botMove(xPos-(3*24+12), 450);
    driveDisabled = false;

    setTargetPos(xPos-50, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);

    driveDisabled = true;
    drive.moveVelocityLeft(450);
    drive.moveVelocityRight(450);
    pros::delay(100);
    wings.extFrontWings();
    while (fabs(drive.imu.get_roll()) < 5) {
        drive.moveVelocityLeft(450);
        drive.moveVelocityRight(450);
        pros::delay(10);
    }
    wings.retFrontWings();
    botMove(-5, 450);
    driveDisabled = false;
    driveMode = 2; // move back
    setTargetPos(5*24-4, 1*24-4);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
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

void closeStealAuton2() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    intake.moveVelocity(-200); // deploy intake
    driveDisabled = true;
    pros::delay(250);
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
    drive.stop();
    pros::delay(250);
    botMove(xPos-(3*24+12), 450);
    driveDisabled = false;

    setTargetPos(5*24, 1*24+12);
    setChainPos(3*24+8, 2*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(15, 2000);
    wings.extBLWing();
    setChainPos(3*24+16, 2*24+16);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);
    setChainPos(4*24+6, 2*24);
    maxMoveSpeed = 300;
    untilTargetPos(15, 2000);
    setChainPos(5*24, 1*24+6);
    maxMoveSpeed = 300;
    untilTargetPos(15, 2000);

    driveMode = 1;
    setTargetPos(5*24+16, 2*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(10, 2000);

    intake.moveVelocity(-200);
    setTargetPos(xPos, 3*24-10); // turn towards pole
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    botMove(-15, 450);
    wings.retBLWing();
    wings.extFrontWings();

    maxMoveSpeed = 200; // move to pole
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
void closeElimsPreauton() {
    drive.hold();
    // maxTurnConstant = 20;
    drive.imu.set_heading(0);
    driveDisabled = false;
    setPos(5*24+6, 1*24+7.5);
setTargetPos(3*24, 2*24);
maxMoveSpeed= 0;
untilTargetH(2,3000);
pros::delay(1000);
botMove(-3,400);
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
void closeElimAuton2() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    driveMode = 1;
    // setTargetPos(3*24+16, 1*24+12); // outtake alliance triball
    // intake.moveVelocity(-200);
    // maxMoveSpeed = 600;
    // untilTargetPos(30, 2000, true);
    // maxMoveSpeed = 450;
    // if (!untilTargetPos(10, 2000, true)) botMove(-5, 300);
    setTargetPos(3*24, 2*24); // intake triball 1
    // maxMoveSpeed = 0;
    // untilTargetH(10, 1500, 0, true);
    intake.moveVelocity(-200);
    wings.extFrontWings();
    maxMoveSpeed = 600;
    pros::delay(300);
    wings.retFrontWings();
    untilTargetPos(35, 2000, true);
    intake.moveVelocity(200);
    maxMoveSpeed = 200;
    untilTargetPos(12, 1500, true);
    // botMove(positionError(targetX, targetY) - 12, 200);
    driveDisabled = true;
    drive.stop();
    pros::delay(250);
    driveDisabled = false;
    // maxMoveSpeed = 300;
    // untilTargetPos(10, 2000, true);
    botMove(-fabs((3*24+16-xPos)/cos(headingError(-90))), 300);

    setTargetPos(xPos, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000, 0, true);

    intake.moveVelocity(-200); // push ball over barrier
    driveDisabled = true;
    while (fabs(drive.imu.get_roll()) < 8) {
        drive.moveVelocityLeft(300);
        drive.moveVelocityRight(300);
        pros::delay(10);
    }
    driveDisabled = false;
    botMove(-fmax(fabs(2*24+12-yPos), 8), 300);

    setTargetPos(3*24,3*24-5); // intake triball 2
    maxMoveSpeed = 0;
    untilTargetH(10, 2000, 0, true);
    intake.moveVelocity(200);
    botMove(positionError(targetX, targetY) - 12, 200);
    driveDisabled = true;
    pros::delay(250);
    driveDisabled = false;
    botMove(-fmax(10, fabs((3*24+12-xPos)/cos(headingError(-90)))), 300);

    driveMode = 2;
    setTargetPos(5*24+4,1*24); // move to descore triball
    setChainPos(4*24+12, 1*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000, 250);
    // pros::delay(500);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(5*24+8,1*24);
    maxMoveSpeed = 300;
    untilTargetPos(15, 2000);
    pros::delay(500);
    wings.extBLWing(); // descore triball
    untilTargetPos(5, 500);
    driveMode = 2;
    setTargetPos(xPos+50, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(5, 1500, 0, true);
    driveMode = 1;
    setTargetPos(xPos+150, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(5, 1500, 0, true);
    pros::delay(300);
    wings.retBLWing();
    setTargetPos(5*24+12,3*24-16)  ;
    setChainPos(5*24+12,3*24-36);
    maxMoveSpeed = 300;
    untilTargetPos(20, 1500, true);
    pros::delay(500);
    
    intake.moveVelocity(-200);
    // wings.extFrontWings();
    setChainPos(5*24+12,3*24-16);
    
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    botMove(3*24-14-yPos, 450);
    // maxMoveSpeed= 200;
    // untilTargetPos(10, 1500, true);
    // wings.retFrontWings();


    driveMode = 2;
    setTargetPos(5*24+5,12+8);
    maxMoveSpeed = 450;
    untilTargetPos(10, 1500, true);
    wings.extBRWing();
    
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
    maxTurnSpeed = 600;
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

    setTargetPos(4*24, 5*24+20);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-500);
    untilTargetPos(-1, 1500, true);
    driveDisabled = false;

    botMove(10, 600);
    driveDisabled = true;
    wings.retBackWings();
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(-600);
    pros::delay(250);
    driveDisabled = false;
    driveMode = 1;
    setTargetPos(4*24, 5*24+18);
    maxMoveSpeed = 0;
    untilTargetH(25, 1500);
    intake.moveVelocity(-200);
    untilTargetH(10, 500);

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    untilTargetPos(-1, 1500, true);
    botMove(-12, 450);
    driveDisabled = false;

    intake.moveVelocity(200); // intake triball 3
    setTargetPos(4*24, 3*24+12);
    setChainPos(4*24+1, 4*24-5);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(4*24, 3*24+12);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000, true);

    botMove(-2, 450);
    setTargetPos(3*24+6, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    
    driveDisabled = true; // score triball 3
    intake.moveVelocity(-200);
    wings.extFrontWings();
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    untilTargetPos(-1, 2000, true);
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
    setTargetPos(xPos+200, yPos-200);
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
    maxTurnSpeed = 600;
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

    setTargetPos(4*24, 5*24+20);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-500);
    untilTargetPos(-1, 1500, true);
    driveDisabled = false;

    botMove(10, 600);
    driveDisabled = true;
    wings.retBackWings();
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(-600);
    pros::delay(250);
    driveDisabled = false;
    driveMode = 1;
    setTargetPos(4*24, 5*24+18);
    maxMoveSpeed = 0;
    untilTargetH(25, 1500);
    intake.moveVelocity(-200);
    untilTargetH(10, 500);

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    untilTargetPos(-1, 1500, true);
    botMove(-12, 450);
    driveDisabled = false;

    intake.moveVelocity(200); // intake triball 3
    setTargetPos(4*24, 3*24+12);
    setChainPos(4*24+1, 4*24-5);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(4*24, 3*24+12);
    maxMoveSpeed = 300;
    int t = 2000;
    int stalledStates = 0;
    while (positionError(chainX, chainY) > 5 && fabs(drive.imu.get_roll()) < 15 && stalledStates < 10 && t > 0) {
        if (sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02993239667 && t < 1500) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 10) break;
        t -= 10;
        pros::delay(10);
    }
    // untilTargetPos(5, 2000, true);

    botMove(-2, 450);
    
    setTargetPos(3*24+12, 5*24-4); // deposit triball 3
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    intake.moveVelocity(-200);
    driveDisabled = true;
    botMove(5, 450);
    pros::delay(250);
    botMove(-5, 450);
    driveDisabled = false;
    
    intake.moveVelocity(200); // intake triball 4
    setTargetPos(3*24+2, 3*24+10);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 300;
    maxTurnSpeed = 0;
    t = 2000;
    stalledStates = 0;
    while (positionError(chainX, chainY) > 5 && fabs(drive.imu.get_roll()) < 15 && stalledStates < 10 && t > 0) {
        if (sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02993239667 && t < 1500) stalledStates++;
        else stalledStates = 0;
        t -= 10;
        pros::delay(10);
    }
    // untilTargetPos(5, 1500, true);
    pros::delay(250);
    // botMove(-10, 450);
    
    setTargetPos(xPos, yPos+40); // score triball 3,4,5
    maxTurnSpeed = 600;
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    
    driveDisabled = true;
    wings.extFrontWings();
    intake.moveVelocity(-200);
    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(500);
    untilTargetPos(-1, 2000, true);
    driveDisabled = false;
    intake.moveVelocity(0);
    botMove(-20, 450);
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
void testingTurning(){
    double start = pros::millis();
    
    driveDisabled  = false;
    drive.stop();
    drive.hold();
    setTargetPos(xPos+25, yPos + 10);
    untilTargetPos(5,2000);
}
void farElim6Auton2() {
    double start = pros::millis();
    driveDisabled  = false;
    drive.stop();
    drive.hold();
    maxTurnSpeed = 600;
    intake.moveVelocity(-200); 
    wings.extFrontWings();
    driveMode = 1;
    setTargetPos(3*24+7,3*24+4);
    // setChainPos(4*24-4,4*24);
    // setChainPos(4*24+12,4*24);
    // maxMoveSpeed = 600;
    // untilTargetPos(25,2000);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000, 250, true);
    setTargetPos(3*24+7,3*24+6);
    wings.retFrontWings();
    intake.moveVelocity(200);
    // setChainPos(3*24+6,3*24+8);
    maxMoveSpeed = 600;
    pros::delay(300);
    wings.retFrontWings();
    intake.moveVelocity(200);
    untilTargetPos(30,2000);
    maxMoveSpeed = 450;
    untilTargetPos(10,2000, true);
    botMove(-5, 200);
    driveMode = 2;
    setTargetPos(5*24+16,4*24+8);
    setChainPos(5*24-10,5*24-16);
    maxMoveSpeed = 0;
    untilTargetH(15,2000);
    maxMoveSpeed = 600;
    untilTargetPos(25,2000);
    setChainPos(5*24+16,4*24+8);
    maxMoveSpeed = 450;
    untilTargetPos(15,2000);
    maxMoveSpeed = 0;
    intake.moveVelocity(-200);
    
    driveMode = 1;
    setTargetPos(4*24+3,5*24+40);
    untilTargetH(15,1200);
    setTargetPos(5*24+12, 3*24+7);
    untilTargetH(5,1500);
    maxMoveSpeed = 600;
    intake.moveVelocity(200);
    untilTargetPos(25,2000);
    maxMoveSpeed = 450;
    untilTargetPos(15,2000);
    maxMoveSpeed = 300;
    untilTargetPos(5,2000);
    driveMode = 2;
    // maxMoveSpeed = 450;
    maxMoveSpeed = 450;
    setTargetPos(4*24+3,5*24+8);
    setChainPos(5*24+10,4*24+16);
    untilTargetPos(15,2000, true);
    intake.moveVelocity(0);
    wings.extBLWing();
    setChainPos(5*24-6,5*24+5);
    untilTargetPos(15,2000, true);

    setChainPos(4*24+3,5*24+8);
    
    // pros::delay(300);
    wings.retBLWing();
    untilTargetPos(5,2000, true);
    // setTargetPos(4*24+3,5*24+8);
    // untilTargetPos(5,2000, true);

    botMove(5, 450);
    
    driveMode = 1;
    setTargetPos(4*24,5*24+12);
    maxMoveSpeed=0;
    untilTargetH(30,1000);
    intake.moveVelocity(-200);
    untilTargetH(5,1000);
    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    untilTargetPos(-1, 1500, true);
    driveDisabled = false;
    botMove(-15, 450);
    // maxMoveSpeed = 450;
    // driveMode = 2;
    // setTargetPos(4*24+16,5*24+8);
    // untilTargetPos(6,2000);
    driveMode = 1;
    setTargetPos(4*24+3.5,3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10,2000, 250);
    maxMoveSpeed = 600;
    untilTargetPos(25,2000);
    intake.moveVelocity(200);
    maxMoveSpeed = 450;
    untilTargetPos(15,2000);
    maxMoveSpeed = 300;
    untilTargetPos(8,2000, true);
    setTargetPos(3*24+7,4*24+18);
    setChainPos(3*24+7,4*24);
    maxMoveSpeed=0;
    untilTargetH(10,2000);
    // maxMoveSpeed = 450;
    wings.extFrontWings();
    intake.moveVelocity(0);
    // pros::delay(200);
    setChainPos(xPos+40, yPos+200);
    maxMoveSpeed=450;
    intake.moveVelocity(-200);
    untilTargetH(10,2000);
    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    untilTargetPos(-5, 2000, true);
    driveDisabled = false;
    wings.retFrontWings();
    driveMode = 2;
    setTargetPos(xPos+24, 4*24);
    maxMoveSpeed = 300;
    untilTargetPos(15, 2000, true);
    // botMove(-25, 450);

    driveDisabled = true;
    print_task.suspend();
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void farElim6Auton() {
    double start = pros::millis();
    driveDisabled = false;
    drive.stop();
    drive.hold();

    // intake.moveVelocity(-200); // deploy intake
    // driveMode = 1;
    // wings.extFrontWings(); // launch alliance triball
    // setTargetPos(3*24+4, 4*24+2); // rush triball 1
    // setChainPos(4*24-4, 4*24+3);
    // // setChainPos(3*24+4, 4*24+2);
    // maxMoveSpeed = 600;
    // untilTargetPos(25, 2000);
    // wings.retFrontWings();
    // untilTargetPos(15, 2000);
    // intake.moveVelocity(200);
    // // untilTargetPos(50, 2000);
    // // wings.retFrontWings();
    // // untilTargetPos(35, 2000);
    // // intake.moveVelocity(200);
    // setChainPos(3*24+2, 4*24+1);
    // maxMoveSpeed = 600;
    // untilTargetPos(8, 2000);

    intake.moveVelocity(-200); 
    wings.extFrontWings();
    driveMode = 1;
    setTargetPos(3*24+6,3*24+8);
    // setChainPos(4*24-4,4*24);
    setChainPos(4*24+12,4*24);
    maxMoveSpeed = 600;
    untilTargetPos(25,2000);
    wings.retFrontWings();
    intake.moveVelocity(200);
    setChainPos(3*24+6,3*24+8);
    maxMoveSpeed = 450;
    untilTargetPos(8,2000);
    botMove(-5, 200);
    driveMode = 2;
    setTargetPos(5*24+12,4*24+12); // come back
    setChainPos(4*24+12,4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000, 0, true);
    maxMoveSpeed = 450;
    untilTargetPos(15,2000);
    setChainPos(5*24+12,4*24+16);
    maxMoveSpeed = 450;
    untilTargetPos(10,2000);
    maxMoveSpeed = 0;
    // intake.moveVelocity(-200);

    // driveMode = 2; // come back
    // setTargetPos(5*24+12, 4*24+16);
    // setChainPos(4*24+16, 4*24+12);
    // maxMoveSpeed = 0;
    // untilTargetH(15, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);
    // setChainPos(5*24+12, 4*24+12);
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 2000);

    driveMode = 2; // deposit triball
    setTargetPos(5*24+16, 3*24+20);
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
    untilTargetPos(13.5, 750, true);
    wings.retBLWing();
    setChainPos(4*24+2, 5*24+16);
    maxMoveSpeed = 600;
    untilTargetPos(5, 750, true);

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
    wings.extFrontWings();
    maxMoveSpeed = 450;
    untilTargetPos(5, 1250);
    wings.retFrontWings();

    // botMove(-15, 600); // intake triball 5
    // setTargetPos(3*24+1, 3*24+8);
    // maxMoveSpeed = 0;
    // untilTargetH(15, 2000);
    // intake.moveVelocity(200);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000);

    // setTargetPos(3*24+5, 5*24); // score triball 5
    // maxMoveSpeed = 0;
    // untilTargetH(15, 2000);
    // intake.moveVelocity(-200);
    // wings.extFrontWings();
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 1250);
    // wings.retFrontWings();

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
    drive.moveVelocityLeft(-400);
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
    untilTargetH(15, 2000);
    wings.extBRWing();
    untilTargetH(5, 2000);
    botMove(-4, 450);
    // wings.extBRWing();
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
    drive.hold();
    maxTurnSpeed = 600;
    driveDisabled = false;

    intake.moveVelocity(-200); // ram in triballs
    kicker.target = 170;
    driveDisabled = true;
    drive.moveVelocityLeft(-400);
    drive.moveVelocityRight(-600);
    untilTargetPos(0, 1500, true, 5);
    botMove(12, 450);
    driveDisabled = false;

    driveMode = 1; // move to shooting position
    kicker.target = 170;
    kicker.velocity = 170;
    kicker.moveVelocity(170);

    driveMode = 1;
    setTargetPos(3*24, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    wings.extBRWing();
    untilTargetH(5, 2000);
    botMove(-4, 450);
    int t = 0;
    // while(t < 2500) {
   while(t < 18000) {
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
    botMove(xPos-(1*24+10)+10, 450);
    intake.moveVelocity(200);
    botMove(-15, 300);
    driveDisabled = false;

    driveMode = 1; // align for alley push
    setTargetPos(fmin(xPos-14, 1*24+8), 1*24+6);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    pros::delay(200);
    intake.moveVelocity(0);
    maxMoveSpeed = 450;
    if(!untilTargetPos(15, 2000, true, 10)) botMove(-5, 450);
    driveMode = 1;
    maxTurnSpeed = 600;
    swerve(6, 3*24, swervePID2, 1500, 0, 15);
    maxTurnSpeed = 600;

    driveMode = 1; // alley push
    intake.moveVelocity(-200);
    setTargetPos(xPos-20, yPos+100);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    pros::delay(400);
    setTargetPos(12, 4*24);
    setChainPos(12, 2*24);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    maxMoveSpeed = 450;
    if(!untilTargetPos(15, 2000, true)) {
        botMove(-10, 450);
        setChainPos(xPos-200, yPos+200);
        maxMoveSpeed = 0;
        untilTargetH(15, 2000);
        setChainPos(8, 3*24);
        maxMoveSpeed = 600;
        if (!untilTargetPos(25, 2000, true)) {
            setChainPos(xPos-20, yPos+200);
            maxMoveSpeed = 0;
            untilTargetH(15, 2000);
        }
    } else {
        setChainPos(8, 3*24);
        maxMoveSpeed = 600;
        untilTargetPos(25, 2000);
        wings.extFrontWings();
    }
    kicker.target = 0;
    kicker.velocity = 0;
    kicker.moveVelocity(0);
    // setChainPos(12, 4*24+8);
    // setChainPos(12, 4*24+16);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);


    setChainPos(14, 4*24+18);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // botMove((115-yPos),300);
    // wings.retFrontWings();
    // botMove(-15, 450);
    // botMove(-5, 450);
    // setTargetPos(xPos,yPos+19);
    // untilTargetPos(15, 2000);
    maxTurnSpeed = 350;
    wings.extFrontWings();
    setTargetPos(xPos+160, yPos+200);
    maxMoveSpeed = 350;
    untilTargetH(10, 1500);
    setTargetPos(2*24+2, 5*24+12);
    // swerve(heading(xPos+100, yPos+160), swervePID2, 1500, 0, 15);
    maxTurnSpeed = 600;
    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(300);
    // untilTargetH(10, 1500);
    untilTargetPos(-1, 1500, true);
    wings.retFrontWings();
    botMove(-12, 600);
    driveDisabled = false;
    setTargetPos(xPos+200, yPos+50);
    maxMoveSpeed = 0;
    untilTargetH(10, 750);
    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    untilTargetPos(-1, 1500, true);
    // setPos(1*24+20, 6*24-10);
    // setPos(1*24+20, yPos); //don't reset position anymore
    setPos(xPos-9,yPos);
    driveDisabled = false;
    wings.retBackWings();
    botMove(1*24+13-xPos, 450);
   
    driveMode = 1; // scoop corner 1
    intake.moveVelocity(200);
    setTargetPos(1*24+12,3*24+15);
    setChainPos(1*24+13, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    if (!untilTargetPos(15, 2000, true)) {
        botMove(-10, 2000);
        setTargetPos(2*24+4, 3*24+12);
        maxMoveSpeed = 0;
        untilTargetH(10, 2000);
        maxMoveSpeed = 300;
        untilTargetPos(5, 2000, true);

        driveMode = 2;
        setTargetPos(2*24+16, 5*24);
        maxMoveSpeed = 0;
        untilTargetH(10, 2000);
    } else {
    // if(!untilTargetPos(15, 2000, true)) botMove(-5, 450);
        setChainPos(1*24+12, 3*24+15);
        maxMoveSpeed = 300;
        untilTargetPos(15,2000,true);
        setTargetPos(xPos+200, yPos-100);
        maxMoveSpeed = 250;
        if(!untilTargetH(15, 2000)) {
            driveMode = 2;
            setTargetPos(2*24+12, 5*24+6);
            maxMoveSpeed = 0;
            untilTargetH(10, 2000);
        }
        // setTargetPos(1*24+25,3*24+12);
        // untilTargetPos(10,2000,true);
        // maxMoveSpeed = 0;
        // setTargetPos(xPos -30, yPos -200);
        // untilTargetH(15,2000);
        // maxMoveSpeed = 300;
            // wings.retFrontWings();
        else {
            driveMode = 2;
            intake.moveVelocity(-200);
            botMove(10, 450);
            if (!swerve(2*24+16, 5*24, swervePID2, 1500, 0, 15)) {
                setTargetPos(2*24+16, 5*24);
                maxMoveSpeed = 0;
                untilTargetH(10, 2000);
            }
        }
    }
    intake.moveVelocity(-200);
    // botMove(-5, 450);

    driveMode = 2;
    // setTargetPos(xPos+200, yPos+125);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    arcMovement = true;
    wings.extBackWings();
    setTargetPos(2*24+12, 5*24+6); // push 2
    maxMoveSpeed = 600;
    int timer = 1500;
    while (positionError(targetX, targetY) > 15 && fabs(headingError(180)) > 10 && timer > 0) {
        timer -= 10;
        pros::delay(10);
    }
    arcMovement = false;
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(-1, 1000, true);
    driveDisabled = false;
    botMove(10, 450);
    setChainPos(xPos, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(10, 500);
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(-1, 1000, true);
    driveDisabled = false;
    setPos(xPos, 6*24-33.5);
    botMove(10, 450);
    wings.retBackWings();

    driveMode = 1; // scoop corner 2
    intake.moveVelocity(200);
    setTargetPos(3*24-16, 4*24-16);
    maxMoveSpeed = 0;
    untilTargetH(5, 1500);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    setTargetPos(4*24+4, 3*24+6);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000, true);
    setTargetPos(xPos+100, yPos+200);
    maxMoveSpeed = 250;
    if(!untilTargetH(15, 1500)) {
        botMove(-2, 450);
    }
    // setChainPos(4*24+8, 3*24+10);
    // maxMoveSpeed = 300;
    // untilTargetPos(10, 1000, true);
    setTargetPos(4*24+10, 4*24+16);
    maxMoveSpeed = 0;
    // wings.extFrontWings();
    untilTargetH(15, 1000);
    // wings.retFrontWings();
    intake.moveVelocity(-200);
    maxMoveSpeed = 450;
    untilTargetPos(15, 1000);
    driveMode = 2;
    setTargetPos(4*24-12-4,3*24+12);
    setChainPos(4*24+8, 3*24+16);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 1000);
    setTargetPos(4*24-12-4,3*24+12);
    maxMoveSpeed = 300;
    untilTargetPos(10, 1000);
    // botMove(-35, 450);
    // setTargetPos(4*24+12, 4*24-2);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 1500, true);
    setTargetPos(3*24+8-4,5*24-6);
    setChainPos(xPos-100, yPos+300);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    wings.extBackWings();
    arcMovement = true;
    setChainPos(3*24+8-4,5*24-6); // push 3
    maxMoveSpeed = 600;
    timer = 1500;
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
    botMove(10, 450);
    wings.retBackWings();

    // driveMode = 1;
    // setTargetPos(4*24, 4*24-12);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 1000);
    // maxMoveSpeed = 450;
    // untilTargetPos(5, 2000, true);
    // driveMode = 2;
    // setTargetPos(3*24-8, fmin(yPos-8, 3*24+8));
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 2000);
    // setTargetPos(3*24-8, 5*24-3); // push 4
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // wings.extBackWings();
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 1500, true);
    // botMove(10, 450);
    // driveDisabled = true;
    // drive.moveVelocityLeft(-600);
    // drive.moveVelocityRight(-600);
    // untilTargetPos(-1, 1500, true);
    // driveDisabled = false;
    // botMove(10, 450);
    // wings.retBackWings();

    intake.moveVelocity(0);
    driveMode = 1; // align for push 5
    setTargetPos(5*24+12, 4*24+10);
    setChainPos(4*24+12, 4*24+10);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // intake.moveVelocity(-200);
    setChainPos(5*24+12, 4*24+10);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000, true);
    driveMode = 2;
    setTargetPos(4*24+5, 5*24+12); 
    setChainPos(xPos-100, yPos+10);
    maxMoveSpeed = 0;
    untilTargetH(45,300);
    setChainPos(xPos-150, yPos+400);
    untilTargetH(10, 750);
    botMove(15, 450);
    wings.extBRWing();
    setChainPos(xPos+100, yPos+400);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    // wings.extBRWing();
    // setChainPos(5*24-2, 5*24-2);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 1000);
    // // untilTargetPos(15, 1000);
    // swerve(heading(xPos-200, yPos+160), swervePID2, 1500, 0, 15);
    setChainPos(5*24+12, 4*24+10);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // wings.retFrontWings();
    // botMove(-15, 450);
    // botMove(-5, 450);
    // setTargetPos(xPos,yPos+19);
    // untilTargetPos(15, 2000);
    setTargetPos(xPos-200, yPos+200);
    maxMoveSpeed = 250;
    untilTargetH(10, 1500);

    setTargetPos(4*24-2, 5*24+12);
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-300);
    untilTargetPos(-1, 1500, true);
    // setChainPos(4*24+4, 5*24+8); // push 5
    // maxMoveSpeed = 600;
    // untilTargetPos(5, 1000, true);
    botMove(10, 450);
    setTargetPos(xPos-200, yPos+50);
    maxMoveSpeed = 0;
    untilTargetH(10, 500);
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(-1, 1500, true);
    driveDisabled = false;
    setPos(3*24+31.5, yPos);
    botMove(5, 450);
    wings.retBRWing();

    driveMode = 1; // climb
    setTargetPos(5*24+14, 4*24+16);
    maxMoveSpeed = 0;
    untilTargetH(5, 1000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    climb.climbUp();
    // setTargetPos(xPos+3, 3*24-6);
    setTargetPos(xPos+30, yPos-200);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    // climb.climbUp();
    // setTargetPos(xPos+150, yPos-200);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    driveDisabled = true;
    drive.moveVelocityLeft(450);
    drive.moveVelocityRight(450);
    pros::delay(250);
    // std::cout << drive.imu.get_roll() << std::endl;
    while (fabs(drive.imu.get_roll()) < 15) {
        drive.moveVelocityLeft(450);
        drive.moveVelocityRight(450);
        pros::delay(10);
    }
    pros::delay(100);
    driveDisabled = true;
    climb.climbDown();
    botMove(-1, 450);
    driveDisabled = true;

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
        closeElimsPreauton();
        break;

        case 5:
        farPreauton();
        break;

        case 6:
        farPreauton();
        break;

        case 7:
        farElim6Preauton();
        break;

        case 8:
        skillsPreauton();
        break;
	}
}

#endif