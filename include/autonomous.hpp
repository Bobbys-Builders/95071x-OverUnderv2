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
    boomerAng = false;
    driveDisabled = false;
    driveMode = 1;
    maxTurnSpeed = 600;

    setTargetPos(24, 48, 90);
    boomerAng = true;
    maxMoveSpeed = 600;
    maxTurnSpeed = 600;
    untilTargetPos(3, 5000);
    // pros::delay(1000);
    // turn(10, turnPID, 0, 5000);
    // driveDisabled = true;
    // maxMoveSpeed = 600;
    // move(24, movePID, turnPID, 0, 5000);

    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    print_task.suspend(); 
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start-500));
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
    setPos(5*24+6, 1*24+7);

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

    wings.extBRWing();
    intake.moveVelocity(-200); // deploy intake
    driveDisabled = true;
    pros::delay(500);
    driveDisabled = false;
    driveMode = 1;

    setTargetPos(3*24+8, 2*24-2); // intake middle triball
    setChainPos(4*24-8, 2*24-4);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250); // descore triball
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
    boomerAng = false;
    drive.imu.set_heading(0);
    driveDisabled = false;
    setPos(5*24+6, 1*24+7.5);
    botMove(4, 200);
    driveDisabled = true;
    drive.stop();
    pros::delay(1000);
    driveDisabled = false;
    driveMode = 1;
    setTargetPos(3*24, 2*24+1);
    maxMoveSpeed= 0;
    untilTargetH(2,3000);
    pros::delay(1000);
    // botMove(-3,400);
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
    boomerAng = false;
    drive.stop();
    drive.hold();

    driveMode = 1;
    setTargetPos(3*24+8, 2*24-1); // intake triball 1
    intake.moveVelocity(200);
    wings.extBLWing();
    maxMoveSpeed = 600;
    untilTargetPos(24, 2000, true);
    maxMoveSpeed = 300;
    wings.retBLWing();
    untilTargetPos(6, 1500, true);
    driveDisabled = true;
    drive.stop();
    pros::delay(250);
    driveDisabled = false;
    botMove(-8, 600);
    driveMode = 2;
    maxTurnSpeed = 300;
    turn(90, turnPID, 2000, 0, 15);
    maxTurnSpeed = 600;

    intake.moveVelocity(-200);
    driveDisabled = true;
    drive.stop();
    pros::delay(500);
    driveDisabled = false;

    driveMode = 1;
    boomerAng = true;
    setTargetPos(4*24, 2*24+12, -45);
    untilTargetPos(6, 2000);
    intake.moveVelocity(200);
    boomerAng = false;
    setTargetPos(3*24+8, 3*24-3);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 300;
    untilTargetPos(6, 2000, true);

    driveMode = 2; // turn to come back
    swerve(5*24, 24, turnPID, 2000, 0, 15);

    driveMode = 2; // come back
    setTargetPos(5*24-8, 12);
    setChainPos(5*24-12, 1*24+12);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setChainPos(5*24-8, 12);
    maxMoveSpeed = 300;
    untilTargetPos(5, 2000);

    driveMode = 2; // descore triball
    boomerAng = false;
    setTargetPos(5*24+8, 1*24+3);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    wings.extBLWing();
    maxMoveSpeed = 300;
    untilTargetPos(3, 2000);
    maxMoveSpeed = 600;
    setTargetPos(xPos-50, yPos+200);
    maxMoveSpeed = 0;
    untilTargetH(5, 1500, 0, true);
    wings.retBLWing();
    driveMode = 1;

    // if (!untilTargetPos(3, 2000, true)) {
    //     botMove(3, 200);
    // }
    // wings.retBLWing();
    setTargetPos(5*24+16, 3*24-8);
    setChainPos(5*24+16, 1*24+16);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, true);
    intake.moveVelocity(-200);
    wings.extFLWing();
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000, true);
    setChainPos(5*24+16, 3*24-8);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000, true);
    wings.retFLWing();

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
    setPos(5*24+6, 5*24-7);

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

    intake.moveVelocity(200); // deploy intake
    botMove(-5, 450);
    driveDisabled = true;
    pros::delay(200);
    intake.moveVelocity(200); // intake triball 1
    botMove(8, 450);
    driveDisabled = true;
    pros::delay(100);
    botMove(-5, 450);
    driveDisabled = false;


    driveMode = 2; // alley triball 2 + alliance
    boomerAng = false;
    wings.extBRWing();
    setTargetPos(4*24, 5*24+12, 90);
    setChainPos(5*24+12, 4*24+11);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000, true, 5);
    setChainPos(5*24, 5*24+10);
    wings.extBLWing();
    maxMoveSpeed = 600;
    untilTargetPos(10, 2000, true);
    boomerAng = true;
    wings.retBLWing();
    setTargetPos(4*24, 5*24+16, 90);
    maxMoveSpeed = 600;
    minMoveSpeed = 600;
    untilTargetPos(8, 2500, true, 2, targetX, targetY);
    wings.retBRWing();
    minMoveSpeed = 0;
    botMove(10, 600);

    driveMode = 1;
    boomerAng = false;
    setTargetPos(4*24-3, 5*24+16); // turn around and score triball 1
    maxMoveSpeed = 0;
    untilTargetH(10, 1500, 0, true, 5);
    intake.moveVelocity(-100);
    maxMoveSpeed = 600;
    minMoveSpeed = 600;
    int t = 1500;
    int stalledStates = 0;
    while (t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || drive.imu.get_roll() > 7.5) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        t -= 10;
        pros::delay(10);
    }
    // untilTargetPos(-1, 1500, true, 2);
    minMoveSpeed = 0;
    botMove(-10, 600);

    driveMode = 2; // intake triball 3
    boomerAng = true;
    setTargetPos(4*24+4, 4*24+4, 45);
    maxMoveSpeed = 600;
    untilTargetPos(8, 2500, true, 5, targetX, targetY);
    driveMode = 1;
    boomerAng = false;
    intake.moveVelocity(200);
    setTargetPos(4*24+1, 3*24+3);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000, 0, true, 5);
    setTargetPos(4*24, 3*24+8);
    maxMoveSpeed = 600;
    t = 1500;
    stalledStates = 0;
    while (positionError(targetX, targetY) > 5 && t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || fabs(drive.imu.get_roll()) > 15) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        if (intake.hasTriball()) break;
        t -= 10;
        pros::delay(10);
    }
    botMove(-5, 450);

    driveMode = 1; // score triball 3
    setTargetPos(3*24, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000, true);
    boomerAng = true;
    setTargetPos(3*24+12, 5*24+3, 0);
    intake.moveVelocity(-100);
    maxMoveSpeed = 600;
    minMoveSpeed = 600;
    t = 1500;
    stalledStates = 0;
    while (t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || drive.imu.get_roll() > 7.5) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        t -= 10;
        pros::delay(10);
    }
    minMoveSpeed = 0;
    intake.moveVelocity(0);

    driveMode = 2;
    boomerAng = false;
    setTargetPos(4*24, 3*24+14);
    maxMoveSpeed = 600;
    untilTargetPos(5, 2000);

    driveMode = 1; // intake ball 4
    boomerAng = false;
    intake.moveVelocity(200);
    setTargetPos(3*24+3, 3*24+6);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, true, 5);
    wings.retBRWing();
    maxMoveSpeed = 600;
    t = 1500;
    stalledStates = 0;
    while (positionError(targetX, targetY) > 5 && t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || fabs(drive.imu.get_roll()) > 15) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        if (intake.hasTriball()) break;
        t -= 10;
        pros::delay(10);
    }
    botMove(-5, 450);

    driveMode = 1; // push balls in
    boomerAng = false;
    setTargetPos(3*24+6, 5*24+3, 0);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000, true);
    boomerAng = true;
    intake.moveVelocity(-100);
    wings.extFrontWings();
    maxMoveSpeed = 600;
    minMoveSpeed = 600;
    t = 1500;
    stalledStates = 0;
    while (t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || drive.imu.get_roll() > 7.5) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        t -= 10;
        pros::delay(10);
    }
    minMoveSpeed = 0;
    wings.retFrontWings();
    intake.moveVelocity(-50);
    botMove(-5, 450);

    driveMode = 2; // touch pole
    boomerAng = false;
    setTargetPos(3*24+12, 3*24+8);
    maxMoveSpeed = 600;
    untilTargetPos(30, 2000);
    boomerAng = true;
    setTargetPos(4*24+18, 3*24+6, 300);
    maxMoveSpeed = 600;
    untilTargetPos(30, 2000, false, 5, targetX, targetY);
    driveMode = 0;
    wings.extBLWing();
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000, true, 5, targetX, targetY);

    driveMode = 1;
    boomerAng = false;
    setTargetPos(xPos-200, yPos-70);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, true);

    // driveMode = 2;
    // wings.extBRWing();
    // setTargetPos(5*24-4, 5*24+8);
    // setChainPos(5*24+11, 4*24+5);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);

    // setChainPos(5*24+10, 5*24-4);
    // maxMoveSpeed = 300;
    // untilTargetPos(15, 2000);

    // wings.extBLWing(); // descore triball 2
    // setChainPos(5*24-4, 5*24+10);
    // maxMoveSpeed = 300;
    // untilTargetPos(30, 2000);
    // intake.moveVelocity(0);
    // untilTargetPos(15, 2000);
    // setChainPos(5*24-4, 5*24+8);
    // maxMoveSpeed = 300;
    // untilTargetPos(5, 1000);
    // // wings.retBLWing();
    // wings.retBackWings();

    // setTargetPos(4*24, 5*24+20);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // driveDisabled = true;
    // drive.moveVelocityLeft(-600);
    // drive.moveVelocityRight(-500);
    // untilTargetPos(-1, 1500, true);
    // driveDisabled = false;

    // botMove(10, 600);
    // driveDisabled = true;
    // wings.retBackWings();
    // drive.moveVelocityLeft(600);
    // drive.moveVelocityRight(-600);
    // pros::delay(250);
    // driveDisabled = false;
    // driveMode = 1;
    // setTargetPos(4*24, 5*24+18);
    // maxMoveSpeed = 0;
    // untilTargetH(25, 1500);
    // intake.moveVelocity(-200);
    // untilTargetH(10, 500);

    // driveDisabled = true;
    // drive.moveVelocityLeft(600);
    // drive.moveVelocityRight(600);
    // untilTargetPos(-1, 1500, true);
    // botMove(-12, 450);
    // driveDisabled = false;

    // intake.moveVelocity(200); // intake triball 3
    // setTargetPos(4*24, 3*24+12);
    // setChainPos(4*24+1, 4*24-5);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);
    // setChainPos(4*24, 3*24+12);
    // maxMoveSpeed = 300;
    // int t = 2000;
    // int stalledStates = 0;
    // while (positionError(chainX, chainY) > 5 && fabs(drive.imu.get_roll()) < 15 && stalledStates < 10 && t > 0) {
    //     if (sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02993239667 && t < 1500) stalledStates++;
    //     else stalledStates = 0;
    //     if (stalledStates > 10) break;
    //     t -= 10;
    //     pros::delay(10);
    // }
    // // untilTargetPos(5, 2000, true);

    // botMove(-2, 450);
    
    // setTargetPos(3*24+12, 5*24-4); // deposit triball 3
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // intake.moveVelocity(-200);
    // driveDisabled = true;
    // botMove(5, 450);
    // pros::delay(250);
    // botMove(-5, 450);
    // driveDisabled = false;
    
    // intake.moveVelocity(200); // intake triball 4
    // setTargetPos(3*24+2, 3*24+10);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000);
    // maxMoveSpeed = 300;
    // maxTurnSpeed = 0;
    // t = 2000;
    // stalledStates = 0;
    // while (positionError(chainX, chainY) > 5 && fabs(drive.imu.get_roll()) < 15 && stalledStates < 10 && t > 0) {
    //     if (sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02993239667 && t < 1500) stalledStates++;
    //     else stalledStates = 0;
    //     t -= 10;
    //     pros::delay(10);
    // }
    // // untilTargetPos(5, 1500, true);
    // pros::delay(250);
    // // botMove(-10, 450);
    
    // setTargetPos(xPos, yPos+40); // score triball 3,4,5
    // maxTurnSpeed = 600;
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    
    // driveDisabled = true;
    // wings.extFrontWings();
    // intake.moveVelocity(-200);
    // driveDisabled = true;
    // drive.moveVelocityLeft(600);
    // drive.moveVelocityRight(500);
    // untilTargetPos(-1, 2000, true);
    // driveDisabled = false;
    // intake.moveVelocity(0);
    // botMove(-20, 450);
    // wings.retFrontWings();
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    print_task.suspend();
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start-500));
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
    boomerAng = false;
    setPos(5*24+6, 5*24-7);

    // botMove(-1, 200);
    // driveDisabled = true;
    // pros::delay(500);
    // driveDisabled = false;
    driveMode = 2;
    // setTargetPos(3*24, 4*24);
    setTargetPos(4*24-6, 4*24-2);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 500);
    // turn(heading(3*24, 4*24), turnPID, 0, 500);
    botMove(2, 200);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    maxTurnSpeed = 600;
    // maxTurnConstant = 35;
    drive.stop();
}
// void testingTurning(){
//     double start = pros::millis();
    
//     driveDisabled  = false;
//     drive.stop();
//     drive.hold();
//     setTargetPos(xPos+25, yPos + 10);
//     untilTargetPos(5,2000);
// }
void farElim6Auton2() {
    double start = pros::millis();
    driveDisabled = false;
    boomerAng = false;
    drive.stop();
    drive.hold();
    maxMoveSpeed = 600;
    maxTurnSpeed = 600;

    driveMode = 2; // rush center
    wings.extFLWing();
    setTargetPos(3*24+10, 4*24+7, 224);
    setTargetPos(4*24-6, 4*24-2);
    intake.moveVelocity(200);
    maxMoveSpeed = 600;
    untilTargetPos(24, 2000);
    wings.retFLWing();
    untilTargetPos(10, 2000); // knock ball 1
    wings.extBRWing();
    // boomerAng = true;
    // setTargetPos(3*24+10, 4*24+7, 224);
    // untilTargetPos(5, 1500, true, 5, targetX, targetY);
    // wings.retBRWing();

    driveMode = 1; // intake ball 2
    boomerAng = false;
    setTargetPos(3*24+3, 3*24+6);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, true);
    wings.retBRWing();
    maxMoveSpeed = 600;
    int t = 1500;
    int stalledStates = 0;
    while (positionError(targetX, targetY) > 5 && t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || fabs(drive.imu.get_roll()) > 15) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 5) break;
        if (intake.hasTriball()) break;
        t -= 10;
        pros::delay(10);
    }
    // untilTargetPos(3, 2000, true);
    botMove(-5, 600);

    driveMode = 1; // push balls in
    boomerAng = true;
    setTargetPos(3*24+12, 5*24+3, 0);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000, true);
    intake.moveVelocity(-200);
    wings.extFLWing();
    maxMoveSpeed = 600;
    minMoveSpeed = 600;
    // driveDisabled = true;
    // drive.moveVelocityLeft(600);
    // drive.moveVelocityRight(600);
    untilTargetPos(-1, 1500, true, 5);
    minMoveSpeed = 0;
    // driveDisabled = false;
    // maxMoveSpeed = 600;
    // untilTargetPos(3, 1500, true, 5, targetX, targetY);
    wings.retFLWing();
    intake.moveVelocity(-50);

    driveMode = 2; // come back
    boomerAng = true;
    setTargetPos(5*24+11, 4*24+11, 270);
    maxMoveSpeed = 600;
    untilTargetPos(5, 2500, true, 5, targetX, targetY);

    driveMode = 2; // alley triball 3 + alliance
    boomerAng = false;
    setTargetPos(4*24, 5*24+12, 90);
    setChainPos(5*24, 5*24+10);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 0, true);
    // wings.extBackWings();
    wings.extBLWing();
    maxMoveSpeed = 600;
    untilTargetPos(10, 2000, true);
    // botMove(3, 450);
    boomerAng = true;
    wings.retBLWing();
    setTargetPos(4*24, 5*24+12, 90);
    maxMoveSpeed = 600;
    untilTargetPos(8, 2500, true, 5, targetX, targetY);
    // botMove(10, 600);

    driveMode = 1; // intake triball 4
    // boomerAng = false;
    // setTargetPos(4*24, 3*24+16, 180);
    // setChainPos(4*24+8, 3*24+12);
    // pros::delay(300);
    // wings.retBackWings();
    // maxMoveSpeed = 600;
    // untilTargetPos(8, 2000);
    boomerAng = true;
    setTargetPos(4*24, 3*24+16, 190);
    maxMoveSpeed = 600;
    pros::delay(300);
    wings.retBackWings();
    untilTargetPos(20, 2500, true, 5, targetX, targetY);
    boomerAng = false;
    intake.moveVelocity(200);
    setTargetPos(4*24-4, 3*24+8);
    // maxMoveSpeed = 0;
    // untilTargetH(15, 1000, true);
    maxMoveSpeed = 600;
    t = 1500;
    stalledStates = 0;
    while (positionError(targetX, targetY) > 5 && t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || fabs(drive.imu.get_roll()) > 15) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 5) break;
        if (intake.hasTriball()) break;
        t -= 10;
        pros::delay(10);
    }

    driveMode = 1; // move to alley position
    setTargetPos(yPos+200, yPos-35);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, true);

    // pros::delay(fmax(0, 10000+start-pros::millis()));

    driveDisabled = true; // cross barrier(sus)
    while (drive.imu.get_roll() < 15) {
        drive.moveVelocityLeft(600);
        drive.moveVelocityRight(600);
        pros::delay(10);
    }
    while (drive.imu.get_roll() > -5) {
        drive.moveVelocityLeft(600);
        drive.moveVelocityRight(600);
        pros::delay(10);
    }
    pros::delay(100);
    intake.moveVelocity(-50);
    driveDisabled = false;
    
    driveMode = 1; // alley
    setTargetPos(xPos, yPos+50);
    maxMoveSpeed = 450;
    if (!untilTargetH(30, 500, true)) driveMode = 0;
    maxMoveSpeed = 600;
    untilTargetPos(20, 2000, true);
    driveMode = 1;
    boomerAng = true;
    wings.extFLWing();
    setTargetPos(xPos-40, yPos+40, 300);
    maxMoveSpeed = 600;
    untilTargetPos(30, 2500, true, 5, targetX, targetY);
    intake.moveVelocity(-200);
    minMoveSpeed = 600;
    untilTargetPos(3, 2500, true, 2, targetX, targetY);
    minMoveSpeed = 0;

    botMove(-10, 450); // back up and spin around
    intake.moveVelocity(0);
    wings.retFLWing();
    driveMode = 2;
    boomerAng = false;
    setTargetPos(xPos-200, yPos+100);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    // wings.extBRWing();
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(0, 1500, true, 5);
    setPos(4*24+7.5, 5*24+12);
    driveDisabled = false;
    // wings.retBRWing();

    driveMode = 1;
    boomerAng = true;
    setTargetPos(4*24-8, 4*24+8, 235);
    maxMoveSpeed = 600;
    untilTargetPos(3, 2500, true, 5, targetX, targetY);

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

/*
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
*/

void farElim6Auton() {
    double start = pros::millis();
    driveDisabled = false;
    boomerAng = false;
    drive.stop();
    drive.hold();
    maxMoveSpeed = 600;
    maxTurnSpeed = 600;

    driveMode = 2; // rush center
    wings.extFLWing();
    setTargetPos(3*24+10, 4*24+7, 224);
    setTargetPos(4*24-6, 4*24-2);
    intake.moveVelocity(200);
    maxMoveSpeed = 600;
    untilTargetPos(24, 2000);
    wings.retFLWing();
    untilTargetPos(10, 2000); // knock ball 1
    wings.extBRWing();
    // boomerAng = true;
    // setTargetPos(3*24+10, 4*24+7, 224);
    // untilTargetPos(5, 1500, true, 5, targetX, targetY);
    // wings.retBRWing();

    driveMode = 1; // intake ball 2
    boomerAng = false;
    setTargetPos(3*24+3, 3*24+6);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, true);
    wings.retBRWing();
    maxMoveSpeed = 600;
    int t = 1500;
    int stalledStates = 0;
    while (positionError(targetX, targetY) > 5 && t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || fabs(drive.imu.get_roll()) > 15) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        if (intake.hasTriball()) break;
        t -= 10;
        pros::delay(10);
    }
    // untilTargetPos(3, 2000, true);
    botMove(-10, 600);

    driveMode = 1; // push balls in
    boomerAng = false;
    setTargetPos(3*24+12, 5*24+3, 0);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000, true);
    boomerAng = true;
    intake.moveVelocity(-200);
    wings.extFLWing();
    maxMoveSpeed = 600;
    minMoveSpeed = 600;
    t = 1500;
    stalledStates = 0;
    while (t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || drive.imu.get_roll() > 7.5) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        t -= 10;
        pros::delay(10);
    }
    minMoveSpeed = 0;
    // driveDisabled = true;
    // drive.moveVelocityLeft(600);
    // drive.moveVelocityRight(600);
    // untilTargetPos(-1, 1500, true, 2);
    // driveDisabled = false;
    wings.retFLWing();
    intake.moveVelocity(-50);
    botMove(-5, 450);

    driveMode = 2; // come back
    boomerAng = true;
    setTargetPos(5*24+8, 4*24+11, 250);
    maxMoveSpeed = 600;
    untilTargetPos(8, 2500, true, 5, targetX, targetY);

    driveMode = 1; // intake triball 3(alley)
    boomerAng = true;
    setTargetPos(5*24+10, 3*24+10, 180);
    maxMoveSpeed = 0;
    untilTargetH(15, 1500, 0, true, 5, targetX, targetY);
    intake.moveVelocity(200);
    maxMoveSpeed = 600;
    untilTargetPos(5, 2000, true, 5, targetX, targetY);

    driveMode = 2; // alley triball 4 + alliance
    boomerAng = false;
    wings.extBRWing();
    setTargetPos(4*24, 5*24+12, 90);
    setChainPos(5*24+12, 4*24+11);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000, true, 5);
    setChainPos(5*24, 5*24+10);
    // maxMoveSpeed = 0;
    // untilTargetH(5, 2000, 0, true);
    wings.extBLWing();
    maxMoveSpeed = 600;
    untilTargetPos(10, 2000, true);
    boomerAng = true;
    wings.retBLWing();
    setTargetPos(4*24, 5*24+12, 90);
    maxMoveSpeed = 600;
    minMoveSpeed = 600;
    untilTargetPos(8, 2500, true, 2, targetX, targetY);
    wings.retBRWing();
    minMoveSpeed = 0;
    botMove(10, 600);

    driveMode = 1;
    boomerAng = false;
    setTargetPos(4*24-3, 5*24+16); // turn around and score triball 3
    maxMoveSpeed = 0;
    untilTargetH(10, 1500, 0, true, 5);
    intake.moveVelocity(-200);
    maxMoveSpeed = 600;
    minMoveSpeed = 600;
    t = 1500;
    stalledStates = 0;
    while (t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || drive.imu.get_roll() > 7.5) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        t -= 10;
        pros::delay(10);
    }
    // untilTargetPos(-1, 1500, true, 2);
    minMoveSpeed = 0;
    botMove(-5, 600);

    driveMode = 2; // intake triball 5
    boomerAng = true;
    setTargetPos(4*24, 4*24+4, 45);
    maxMoveSpeed = 600;
    untilTargetPos(8, 2500, true, 5, targetX, targetY);
    driveMode = 1;
    boomerAng = false;
    intake.moveVelocity(200);
    setTargetPos(4*24+1, 3*24+3);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000, 0, true, 5);
    setTargetPos(4*24, 3*24+8);
    maxMoveSpeed = 600;
    t = 1500;
    stalledStates = 0;
    while (positionError(targetX, targetY) > 5 && t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || fabs(drive.imu.get_roll()) > 15) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        if (intake.hasTriball()) break;
        t -= 10;
        pros::delay(10);
    }
    botMove(-5, 450);

    driveMode = 1; // score triball 5
    setTargetPos(3*24, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000, true);
    boomerAng = true;
    setTargetPos(3*24+12, 5*24+3, 0);
    intake.moveVelocity(-200);
    wings.extFLWing();
    maxMoveSpeed = 600;
    minMoveSpeed = 600;
    // untilTargetPos(-1, 1500, true, 2);
    t = 1500;
    stalledStates = 0;
    while (t > 0) {
        if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || drive.imu.get_roll() > 7.5) && t < 1000) stalledStates++;
        else stalledStates = 0;
        if (stalledStates > 2) break;
        t -= 10;
        pros::delay(10);
    }
    minMoveSpeed = 0;
    wings.retFLWing();
    intake.moveVelocity(0);

    driveMode = 2; // move into blocking position
    boomerAng = false;
    setTargetPos(3*24+12, 3*24+12);
    maxMoveSpeed = 600;
    untilTargetPos(10, 2000, true, 5);
    driveMode = 1;
    setTargetPos(xPos-200, yPos);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250, true, 5);
    driveMode = 1;

    driveDisabled = true;
    print_task.suspend();
    drive.stop();
    pros::delay(500);
    controller.print(0, 0, "%.0f                             ", (pros::millis() - start-500));
    pros::delay(500);
    controller.print(1, 0, "X: %.1f Y: %.1f H: %.1f          ", xPos, yPos, drive.imu.get_heading());
    pros::delay(4000);
    print_task.resume();
}

void skillsPreauton() {
    drive.hold();
    drive.imu.set_heading(0);
    driveDisabled = false;
    boomerAng = false;
    setPos(5*24+6, 1*24+7);

    // driveMode = 2;
    // swerve(109.7, 11, turnPID, 0, 500);
    // botMove(5, 300);

    driveMode = 2;
    maxTurnSpeed = 600;
    swerve(4*24, 12, turnPID, 2000, 500);
    botMove(4, 300);
    
    driveDisabled = true;
    driveMode = 0;
    maxMoveSpeed = 450;
    drive.stop();
}

void skillsSegA() {
    double start = pros::millis();
    drive.hold();
    maxTurnSpeed = 600;
    driveDisabled = false;
    boomerAng = false;

    intake.moveVelocity(-200); // ram in triballs
    // kicker.target = 170;
    driveDisabled = true;
    drive.moveVelocityLeft(-400);
    drive.moveVelocityRight(-600);
    untilTargetPos(0, 1500, true, 5);
    // botMove(12, 450);
    driveDisabled = false;

    setTargetPos(4*24+16, 14);
    maxMoveSpeed = 450;
    untilTargetPos(3, 1000);

    driveMode = 1; // move to shooting position
    kicker.target = 170;
    kicker.velocity = 170;
    kicker.moveVelocity(170);

    driveMode = 1;
    setTargetPos(3*24-6, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    wings.extBRWing();
    untilTargetH(5, 2000);
    botMove(-5, 450);
    int t = 0;
    while(fabs(controller.get_analog(ANALOG_LEFT_Y)) < 20) {
        if (fabs(controller.get_analog(ANALOG_RIGHT_X)) > 20) driveDisabled = false;
        if (!driveDisabled) moveDrive();
        kicker.target = 170;
        kicker.velocity = 170;
        kicker.moveVelocity(170);
        intake.moveVelocity(-200);

        pros::delay(10);
        t += 10;
    }
    wings.retBRWing();
}

void skillsAuton() {
    double start = pros::millis();
    drive.hold();
    maxTurnSpeed = 600;
    driveDisabled = false;
    boomerAng = false;

    intake.moveVelocity(-200); // ram in triballs
    // kicker.target = 170;
    driveDisabled = true;
    drive.moveVelocityLeft(-400);
    drive.moveVelocityRight(-600);
    untilTargetPos(0, 1500, true, 5);
    // botMove(12, 450);
    driveDisabled = false;

    setTargetPos(4*24+16, 14);
    maxMoveSpeed = 450;
    untilTargetPos(3, 1000);

    driveMode = 1; // move to shooting position
    kicker.target = 150;
    kicker.velocity = 150;
    kicker.moveVelocity(150);

    driveMode = 1;
    setTargetPos(3*24-6, 5*24);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    wings.extBRWing();
    untilTargetH(5, 2000);
    botMove(-5, 450);
    int t = 0;
    // while(t < 2500) {
    while(t < 22000) {
        kicker.target = 150;
        kicker.velocity = 150;
        kicker.moveVelocity(150);
        intake.moveVelocity(-200);
        // if (t == 10000) setTargetPos(3*24-0.5, 5*24);

        pros::delay(10);
        t += 10;
    }
    wings.retBRWing();
    untilKeyPress();

    driveDisabled = false;
    boomerAng = false;// push triballs over barrier
    driveMode = 1;
    setTargetPos(1*24+6, 3*24-12, 270);
    setChainPos(4*24+10, 1*24+16);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    wings.extFrontWings();
    boomerAng = true;
    setChainPos(1*24+10, 3*24-12);
    maxMoveSpeed = 600;
    untilTargetPos(3, 3000, true, 5, targetX, targetY);
    // untilTargetH(15, 3000, 0, true, 5, targetX, targetY);
    // botMove(positionError(targetX, targetY)*cos(headingError(targetX, targetY)*RADIANS_DEGREE), 600, false, true);
    // driveDisabled = true;
    // pros::delay(200);
    // driveDisabled = false;

    driveDisabled = true;
    botMove(-11, 450);
    botMove(xPos-(1*24+8)+10, 600);
    // botMove(positionError(targetX, targetY)*cos(headingError(targetX, targetY)*RADIANS_DEGREE), 600);
    intake.moveVelocity(200);
    botMove(-10, 300);
    wings.retFrontWings();
    driveDisabled = false;

    boomerAng = false;
    driveMode = 1; // align for alley push
    setTargetPos(1*24, 1*24);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    intake.moveVelocity(0);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    boomerAng = true;
    intake.moveVelocity(-200);
    wings.extFRWing();
    setTargetPos(8, 2*24+12, 10);
    maxMoveSpeed = 600;
    untilTargetPos(15, 3000, true, 10, targetX, targetY);
    // setTargetPos(fmin(xPos-14, 1*24+8), 1*24+6);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 2000);
    // pros::delay(200);
    // intake.moveVelocity(0);
    // maxMoveSpeed = 450;
    // if(!untilTargetPos(15, 2000, true, 10)) botMove(-5, 450);
    // driveMode = 1;
    // maxTurnSpeed = 600;
    // swerve(6, 3*24, swervePID2, 1500, 0, 15);
    // maxTurnSpeed = 600;

    boomerAng = false;
    driveMode = 1; // alley push
    setTargetPos(2*24, 5*24+12, 90);
    setChainPos(14, 4*24+12);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000);
    setTargetPos(2*24, 5*24+12, 90); //push #1
    boomerAng = true;
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000, true, 5, targetX, targetY);
    maxMoveSpeed = 600;
    untilTargetPos(3, 1000, true, 5, targetX, targetY);

    botMove(-15, 450); // back up and spin around
    intake.moveVelocity(200);
    wings.retFRWing();
    driveMode = 2;
    boomerAng = false;
    setTargetPos(2*24, 5*24+16);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    wings.extBLWing();
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(0, 1500, true, 5);
    setPos(2*24-7.5, yPos);
    driveDisabled = false;
    wings.retBLWing();
    botMove(10, 450);

    driveMode = 1; // herd triballs
    boomerAng = false;
    setTargetPos(2*24, 4*24+8, 90);
    // setChainPos(1*24, 5*24);
    // maxMoveSpeed = 0;
    // untilTargetH(30, 2000, true);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 2000, true);
    boomerAng = true;
    wings.extFrontWings();
    intake.moveVelocity(-200);
    setTargetPos(2*24+6, 4*24+8, 90);
    maxMoveSpeed = 600;
    untilTargetPos(3, 2000, true, 5, targetX, targetY);
    wings.retFrontWings();
    botMove(-5, 450);
    
    boomerAng = false; // sweep corner 1
    setTargetPos(2*24+8, 3*24+12, 90);
    setChainPos(2*24-8, 4*24-8);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, true);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000, true);
    boomerAng = true;
    wings.extFRWing();
    intake.moveVelocity(-200);
    setTargetPos(2*24+8, 3*24+12, 90);
    maxMoveSpeed = 600;
    // untilTargetPos(15, 1000, true, 5, targetX, targetY);
    // wings.extFrontWings();
    untilTargetPos(5, 1000, true, 5, targetX, targetY);

    swerve(2*24+20, 5*24, turnPID, 3000, 250, 5);

    wings.extFrontWings();
    setTargetPos(2*24+16, 5*24, 0); // push #2
    maxMoveSpeed = 600;
    untilTargetPos(3, 1000, true, 5, targetX, targetY);
    botMove(-8, 450);
    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    untilTargetPos(0, 1500, true, 5);
    setPos(xPos, 5*24-4);
    driveDisabled = false;
    wings.retFrontWings();
    
    driveMode = 2;
    boomerAng = false; // sweep corner 2
    setTargetPos(4*24+4, 3*24+12);
    setChainPos(3*24+8, 3*24+16);
    maxMoveSpeed = 600;
    untilTargetPos(15, 2000, true);
    setChainPos(4*24+4, 3*24+12);
    maxMoveSpeed = 600;
    untilTargetPos(5, 2000, true);
    wings.extBLWing();

    setTargetPos(3*24+4, 4*24); // align for push #3
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    wings.extBackWings();
    boomerAng = true;
    setTargetPos(3*24+12, 5*24, 0);
    maxMoveSpeed = 600;
    untilTargetPos(5, 2000, true, 5, targetX, targetY);
    botMove(8, 450);
    boomerAng = false;
    setTargetPos(xPos, yPos+200);
    maxMoveSpeed = 600;
    untilTargetH(5, 1000);
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(0, 1500, true, 5);
    setPos(xPos, 5*24-7.5);
    driveDisabled = false;

    driveMode = 1; // herd triballs
    boomerAng = true;
    setTargetPos(4*24+12, 4*24+16, 0);
    maxMoveSpeed = 600;
    pros::delay(200);
    wings.retBackWings();
    wings.extFRWing();
    untilTargetPos(24, 1000, true, 5, targetX, targetY);
    wings.extFrontWings();
    untilTargetPos(5, 1000, true, 5, targetX, targetY);
    wings.retFrontWings();

    boomerAng = false; // align for push #4
    setTargetPos(5*24+6, 4*24+14);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    intake.moveVelocity(200);
    maxMoveSpeed = 600;
    untilTargetPos(5, 2000, true);
    setTargetPos(xPos, yPos + 200);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    intake.moveVelocity(-200);
    wings.extFLWing();
    setTargetPos(4*24, 5*24+12, 270); //push #4
    boomerAng = true;
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000, true, 5, targetX, targetY);
    maxMoveSpeed = 600;
    untilTargetPos(3, 1000, true, 5, targetX, targetY);

    botMove(-15, 450); // back up and spin around
    intake.moveVelocity(0);
    wings.retFLWing();
    driveMode = 2;
    boomerAng = false;
    setTargetPos(4*24, 5*24+16);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    wings.extBRWing();
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(0, 1500, true, 5);
    setPos(4*24+7.5, yPos);
    driveDisabled = false;
    wings.retBRWing();
    climb.climbUp();
    botMove(10, 450);

    boomerAng = true;
    driveMode = 1; // climb
    setTargetPos(5*24+12, 4*24, 200);
    maxMoveSpeed = 600;
    untilTargetPos(5, 3000, true, 5, targetX, targetY);
    setTargetPos(xPos-20, yPos-200);
    maxMoveSpeed = 0;
    untilTargetH(15, 3000, 0, true);
    driveDisabled = true;
    drive.moveVelocityLeft(300);
    drive.moveVelocityRight(300);
    pros::delay(250);
    // std::cout << drive.imu.get_roll() << std::endl;
    while (fabs(drive.imu.get_roll()) < 15) {
        drive.moveVelocityLeft(300);
        drive.moveVelocityRight(300);
        pros::delay(10);
    }
    botMove(-1, 450);
    driveDisabled = true;
    climb.climbDown();
    climb.PTOEngage();
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(600);
    pros::delay(1000);

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