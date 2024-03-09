#ifndef SKILLS_HPP
#define SKILLS_HPP

#include "setup.hpp"
#include "tasks.hpp"
#include "teleop.hpp"

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
    botMove(xPos-(1*24+10)+10, 450);
    intake.moveVelocity(200);
    botMove(-15, 450);
    driveDisabled = false;

    driveMode = 1; // align for alley push
    setTargetPos(xPos-14, 1*24+6);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    intake.moveVelocity(0);
    maxMoveSpeed = 450;
    if(!untilTargetPos(15, 2000, true, 10)) botMove(-5, 450);
    driveMode = 1;
    maxTurnSpeed = 600;
    swerve(12, 2*24+12, swervePID2, 1500, 0, 15);
    maxTurnSpeed = 600;

    driveMode = 1; // alley push
    intake.moveVelocity(-200);
    setTargetPos(xPos-20, yPos+100);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    setTargetPos(12, 4*24);
    setChainPos(12, 2*24);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(8, 3*24);
    maxMoveSpeed = 600;
    untilTargetPos(25, 2000);
    wings.extFrontWings();
    kicker.target = 0;
    kicker.velocity = 0;
    kicker.moveVelocity(0);
    // setChainPos(12, 4*24+8);
    // setChainPos(12, 4*24+16);
    // maxMoveSpeed = 450;
    // untilTargetPos(15, 2000);


    setChainPos(12, 4*24+16);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // wings.retFrontWings();
    // botMove(-15, 450);
    // botMove(-5, 450);
    // setTargetPos(xPos,yPos+19);
    // untilTargetPos(15, 2000);
    setTargetPos(xPos+160, yPos+200);
    maxMoveSpeed = 250;
    untilTargetH(10, 1500);
    setTargetPos(2*24+2, 5*24+12);
    // swerve(heading(xPos+100, yPos+160), swervePID2, 1500, 0, 15);
    setTargetPos(2*24+2, 5*24+12);
    driveDisabled = true;
    drive.moveVelocityLeft(600);
    drive.moveVelocityRight(300);
    untilTargetH(10, 1500);
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
    setPos(3*24-30.5, 6*24-10);
    driveDisabled = false;
    wings.retBackWings();
    botMove(-15, 450);
   
    driveMode = 1; // scoop corner 1
    setTargetPos(1*24+8,3*24+12);
    setChainPos(1*24+10, 4*24+12);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    intake.moveVelocity(-200);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000, true);
    // if(!untilTargetPos(15, 2000, true)) botMove(-5, 450);
    wings.extFrontWings();
    setChainPos(1*24+8, 3*24+12);
    untilTargetPos(15,2000,true);
    maxMoveSpeed = 300;
    setTargetPos(1*24+25,3*24+12);
    untilTargetPos(10,2000,true);
    maxMoveSpeed = 0;
    setTargetPos(xPos -30, yPos -200);
    untilTargetH(15,2000);
    maxMoveSpeed = 300;
        wings.retFrontWings();
    driveMode = 2;
    if (!swerve(2*24+12, 5*24+6, swervePID2, 1500, 0, 15)) {
        setTargetPos(2*24+12, 5*24+6);
        maxMoveSpeed = 0;
        untilTargetH(10, 2000);
    }
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
    setTargetPos(3*24-16, 4*24-12);
    maxMoveSpeed = 0;
    untilTargetH(15, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(5, 2000);
    intake.moveVelocity(0);
    setTargetPos(4*24, 3*24+4);
    setChainPos(3*24+12, 3*24+4);
    maxMoveSpeed = 0;
    untilTargetH(10, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    setChainPos(4*24+8, 3*24+10);
    maxMoveSpeed = 300;
    untilTargetPos(10, 1000, true);
    setTargetPos(4*24+10, 4*24+16);
    maxMoveSpeed = 0;
    wings.extFrontWings();
    untilTargetH(10, 1000);
    wings.retFrontWings();
    intake.moveVelocity(-200);
    maxMoveSpeed = 450;
    untilTargetPos(10, 1000);
    botMove(-35, 450);
    driveMode = 2;
    // setTargetPos(4*24+12, 4*24-2);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 1500, true);
    setTargetPos(3*24+12, 5*24-6);
    setChainPos(xPos-200, yPos+10);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    wings.extBackWings();
    arcMovement = true;
    setChainPos(3*24+16, 5*24-6); // push 3
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
    setTargetPos(5*24+8, 4*24+12);
    setChainPos(4*24+12, 4*24+10);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // intake.moveVelocity(-200);
    setChainPos(5*24+12, 4*24+12);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    driveMode = 2;
    setTargetPos(4*24+5, 5*24+12); 
    setChainPos(xPos-150, yPos+400);
    maxMoveSpeed = 0;
    untilTargetH(10, 1000);
    botMove(15, 450);
    wings.extBRWing();
    // setChainPos(xPos, yPos+400);
    // maxMoveSpeed = 0;
    // untilTargetH(10, 1000);
    // wings.extBRWing();
    // setChainPos(5*24-2, 5*24-2);
    // maxMoveSpeed = 450;
    // untilTargetPos(10, 1000);
    // // untilTargetPos(15, 1000);
    // swerve(heading(xPos-200, yPos+160), swervePID2, 1500, 0, 15);
    setChainPos(5*24+12, 4*24+14);
    maxMoveSpeed = 450;
    untilTargetPos(15, 2000);
    // wings.retFrontWings();
    // botMove(-15, 450);
    // botMove(-5, 450);
    // setTargetPos(xPos,yPos+19);
    // untilTargetPos(15, 2000);
    setTargetPos(xPos-160, yPos+200);
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
    botMove(12, 450);
    setTargetPos(xPos-200, yPos+50);
    maxMoveSpeed = 0;
    untilTargetH(10, 1500);
    driveDisabled = true;
    drive.moveVelocityLeft(-600);
    drive.moveVelocityRight(-600);
    untilTargetPos(-1, 1500, true);
    driveDisabled = false;
    setPos(3*24+31.5, yPos);
    botMove(12, 450);
    wings.retBRWing();

    driveMode = 1; // climb
    setTargetPos(5*24+12, 4*24+16);
    maxMoveSpeed = 0;
    untilTargetH(5, 1500);
    maxMoveSpeed = 450;
    untilTargetPos(10, 2000);
    climb.climbUp();
    setTargetPos(xPos+3, 3*24-6);
    maxMoveSpeed = 0;
    untilTargetH(5, 2000, 250);
    maxMoveSpeed = 450;
    untilTargetPos(20, 2000);
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
    botMove(-1, 450);
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

#endif