#ifndef AUTONOMOUS_HPP
#define AUTONOMOUS_HPP

#include "setup.hpp"
#include "tasks.hpp"

void testAuton() {
    drive.hold();
    drive.imu.set_heading(0);
    setPos(0, 0);
    arcMovement = false;
    driveDisabled = false;
    driveMode = 1;

    maxMoveSpeed = 300;
    setTargetPos(xPos, yPos+12);
    maxTurnSpeed = 0;
    driveMode = 2;
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

    intake.moveVelocity(200); // deploy intake
    wings.extBRWing(); // descore triball
    driveMode = 1;
    setTargetPos(5*24+12, 1*24+8);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    setTargetPos(xPos, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    intake.moveVelocity(-200);
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
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);

    setTargetPos(5*24+12, 3*24-13); // turn towards pole
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 500);

    maxMoveSpeed = 200; // move to pole
    untilTargetPos(3, 2000);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    drive.stop();
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4500);
}

void closePreauton() {
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
    setTargetPos(5*24-7, 13);
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

    maxMoveSpeed = 200; // move to pole
    untilTargetPos(3, 2000);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    drive.stop();
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4500);
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
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void farSafePreauton() {
    drive.hold();
    // maxTurnConstant = 20;
    drive.imu.set_heading(-90);
    driveDisabled = false;
    setPos(5*24+6, 5*24-7.5);

    driveMode = 1;
    setTargetPos(5*24+12, 5*24-6);
    maxMoveSpeed = 0;
    untilTargetH(2, 3000);
    pros::delay(1000);

    maxMoveSpeed = 150;
    untilTargetPos(3, 4000);

    setTargetPos(xPos-200, xPos+200);
    maxMoveSpeed = 0;
    untilTargetH(2, 3000);
    
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

    intake.moveVelocity(200); // deploy intake
    driveMode = 1; // score alliance triball
    setTargetPos(4*24+8, 5*24+16);
    pros::delay(500);
    intake.moveVelocity(-200);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    
    driveMode = 2; // move to pole
    setTargetPos(5*24+12, 5*24-12);
    maxMoveSpeed = 450;
    untilTargetPos(10, 1000);
    driveMode = 1;
    setTargetPos(5*24+12, 3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 500);
    maxMoveSpeed = 200;
    untilTargetPos(3, 2000);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    drive.stop();
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4500);
}



void skillsPreauton() {
    drive.hold();
    // maxTurnConstant = 20;
    drive.imu.set_heading(-90);
    driveDisabled = false;
    setPos(5*24+6, 1*24+7.5);
    // botMove(5, 100);

    // driveDisabled = false;
    // maxTurnConstant = 20;
    // maxTurnSpeed = 150;
    // // setTargetPos(xPos + 200, yPos+200);
    // setTargetPos(4*24, 10);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // pros::delay(500);

    // driveDisabled = true;
    // botMove(-3, 100);
    driveMode = 0;
    maxMoveSpeed = 450;
    maxTurnSpeed = 350;
    // maxTurnConstant = 35;
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
    // double start = pros::millis();
    // driveDisabled = true;
    // intake.target = 600;

    // flaps.extendLeftFlap();
    // botMove(-15, 550);
    // flaps.retractLeftFlap();

    // driveDisabled = false;
    // setTargetPos(3*24+18, 5*24);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // pros::delay(250);



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
    setTargetPos(3*24+12, 5*24);
    untilTargetH(5, 3000);
    pros::delay(250);
    drive.stop();
    driveMode = 0;
    maxMoveSpeed = 450;

    driveDisabled = true;
    botMove(-3, 200);

    driveDisabled = true;
    drive.stop();
    kicker.target = -180;
    wings.extBRWing();
    int t = 0;
    while(t < 20500) {
        kicker.target = 180;
        kicker.velocity = 180;
        kicker.moveVelocity(180);
        intake.moveVelocity(-600);
        drive.moveVoltageRight(-1000);
        if (headingError(3*24+15, 5*24) > 0.5) {
            drive.moveVoltageLeft(1000);
        }
        if (headingError(3*24+15, 5*24) < -0.5) {
            drive.moveVoltageLeft(-1000);
        }
        pros::delay(10);
        t += 10;
    }
    kicker.target = 0;
    kicker.velocity = 0;
    kicker.moveVelocity(0);
    wings.retBRWing();
    botMove(3, 200);
    kicker.target = 0;
    kicker.velocity = 0;
    kicker.moveVelocity(0);
    driveDisabled = false;

    maxMoveSpeed = 0; // move to goal
    driveMode = 1;
    setTargetPos(5*24+10, 1*24+12);
    untilTargetH(5, 3000);
    maxMoveSpeed = 550;
    wings.extFrontWings();
    untilTargetPos(10, 3000);
    setTargetPos(5*24+12, 4*24+4);
    maxMoveSpeed = 450;
    untilTargetPos(10, 1500);
    arcMovement = true;
    setTargetPos(5*24, 5*24+14);
    // pros::delay(500);
    // flaps.extendLeftFlap();
    maxMoveSpeed = 350;
    untilTargetPos(10, 2000);
    arcMovement = false;
    setTargetPos(xPos - 24, yPos+8);
    maxMoveSpeed = 0;
    untilTargetH(5, 1500);
    pros::delay(250);

    driveDisabled = true; // push 1
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);

    driveDisabled = false;
    wings.retFrontWings();
    driveMode = 2;
    setTargetPos(5*24, 5*24+16);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    driveMode = 1;
    setTargetPos(xPos - 24, yPos+8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    pros::delay(250);

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    setPos(3*24+30, yPos);
    // pros::delay(1500);
    // flaps.retractLeftFlap();
    botMove(-8, 450);
    driveDisabled = false;

    driveMode = 2; // herd triballs
    arcMovement = false;
    setTargetPos(5*24-6, 5*24);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 3000);
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

    driveMode = 2;
    driveDisabled = false;
    arcMovement = false;
    setTargetPos(4*24-8, 3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 1000);
    maxMoveSpeed = 0;
    driveMode = 1;
    setTargetPos(xPos-16, yPos+36);
    untilTargetH(5, 2000);
    pros::delay(250);

    driveDisabled = true;
    wings.extFrontWings();
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(450);
    pros::delay(1000);
    botMove(-10, 450);

    driveDisabled = false;
    setTargetPos(xPos, yPos + 200);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    setPos(xPos, 6*24-30);
    wings.retFrontWings();
    botMove(-8, 450);
    driveDisabled = false;

    driveMode = 2;
    // arcMovement = true;
    driveDisabled = false;
    setTargetPos(xPos+12, 3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    driveMode = 1;
    setTargetPos(2*24+12, 3*24+8);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    // flaps.extendLeftFlap();
    maxMoveSpeed = 450;
    untilTargetPos(10, 3000);

    // driveMode = 1;
    // setTargetPos(2*24+12, 4*24);
    // maxMoveSpeed = 450;
    // flaps.extendLeftFlap();
    // untilTargetPos(10, 2000);
    driveMode = 1;
    setTargetPos(xPos+18, yPos+36);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    wings.extFrontWings();
    pros::delay(250);

    driveDisabled = true;
    botMove(-5, 450);
    drive.moveVelocityLeft(450);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    botMove(-10, 450);

    driveDisabled = false;
    driveMode = 1;
    setTargetPos(xPos, yPos + 200);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    setPos(xPos, 6*24-30);
    wings.retFrontWings();
    botMove(-8, 450);
    driveDisabled = false;

    driveDisabled = false; // herd triballs
    driveMode = 2;
    setTargetPos(3*24, 3*24+12);
    // arcMovement = true;
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    driveMode = 1;
    setTargetPos(2*24, 3*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    wings.extFrontWings();
    setTargetPos(1*24+10, 5*24-12);
    untilTargetPos(5, 2000);
    setTargetPos(xPos+100, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);

    driveMode = 1;
    setTargetPos(12, 5*24-8);
    wings.retFrontWings();
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    // flaps.extendFlaps();
    // flaps.retractFlaps();
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    driveMode = 1;
    setTargetPos(1*24, 5*24+12);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 350;
    // arcMovement = true;
    wings.extFrontWings();
    untilTargetPos(10, 2000);
    setTargetPos(xPos + 24, yPos+8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    pros::delay(250);

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);
    wings.retFrontWings();

    driveDisabled = false;
    driveMode = 2;
    setTargetPos(1*24-3, 5*24+10);
    maxMoveSpeed = 450;
    // flaps.retractFlaps();
    // flaps.extendFlaps();
    // flaps.retractFlaps();
    untilTargetPos(5, 2000);
    driveMode = 1;
    setTargetPos(xPos+24, yPos+8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    pros::delay(250);

    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(750);
    driveDisabled = false;
    driveMode = 2;
    setTargetPos(12, 5*24);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    driveDisabled = true;
    botMove(5, 450);

    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    drive.stop();
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start));
    pros::delay(7500);
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
        farSafePreauton();
        break;

        case 5:
        skillsPreauton();
        break;
	}
}

#endif