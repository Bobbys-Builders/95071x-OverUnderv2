#ifndef TELEOP_HPP
#define TELEOP_HPP

/**
 * Functions to be run during teleop
 * 
 * Includes functions for drivetrain movement and intake/kicker
 * 
 * Buttons:
 * Joysticks - Drive
 * L1(Press) - Intake
 * L2(Press) - Outtake
 * R1(Hold) - Pistons up
 * R2(Press) - Flaps toggle
*/

#include "setup.hpp"
#include "tasks.hpp"

bool R1Mode = false;
bool R2Mode = false;
bool L1Mode = false;
bool L2Mode = false;
bool XMode = false;
bool BMode = false;
void updateButtons() {
    R1Mode = controller.get_digital(DIGITAL_R1);
    R2Mode = controller.get_digital(DIGITAL_R2);
    L1Mode = controller.get_digital(DIGITAL_L1);
    L2Mode = controller.get_digital(DIGITAL_L2);
    XMode = controller.get_digital(DIGITAL_X);
    BMode = controller.get_digital(DIGITAL_B);

	if (R1Mode || R2Mode || L1Mode || L2Mode || XMode || BMode || fabs(controller.get_analog(ANALOG_LEFT_Y)) > 20 || fabs(controller.get_analog(ANALOG_RIGHT_X)) > 20) {
		drive.odomPiston.set_value(true);
	}
}

bool frontWingsDown = false;
bool backWingsDown = false;
void moveWings() {
	if (controller.get_digital(DIGITAL_L1) && !L1Mode) {
		frontWingsDown = !frontWingsDown;
		if (frontWingsDown) {
			wings.extFrontWings();
		} else {
			wings.retFrontWings();
		}
	}
	if (controller.get_digital(DIGITAL_L2) && !L2Mode) {
		backWingsDown = !backWingsDown;
		if (backWingsDown) {
			wings.extBackWings();
		} else {
			wings.retBackWings();
		}
	}
}

bool climbUp = false;
void moveClimb() {
    if (controller.get_digital(DIGITAL_B) && !BMode) {
        
        climbUp = !climbUp;
        if (climbUp) {
            climb.climbUp();
        } else {
            climb.climbDown();
        }
    }
}

double leftVelocity = 0;
double rightVelocity = 0;
double powerVelocity = 0;
double turnVelocity = 0;
bool holdDrive = false;
// void weightedDrive() {
// 	if (controller.get_digital_new_press(DIGITAL_DOWN)) holdDrive = !holdDrive;
// 	double powerMult = 1;
// 	double turnMult = 0.4;
// 	double radiusMult = 15;
// 	double power = (powerMult*controller.get_analog(ANALOG_LEFT_Y))/127*600;
// 	double radius = (radiusMult/controller.get_analog(ANALOG_RIGHT_X)*127);
// 	double turn = (turnMult*controller.get_analog(ANALOG_RIGHT_X))/127*600;
// 	// double radius = (radiusMult/(controller.get_analog(ANALOG_RIGHT_X)/127));
// 	// radius = 100;
// 	power = fmax(fabs(power) - 15, 0) * sign(power);
// 	turn = fmax(fabs(turn) - 5, 0) * sign(turn);
// 	if(fabs(turn)<5){
// 		leftVelocity = power;
// 		rightVelocity = power;
// 	} else if(fabs(power)<5){
// 		leftVelocity = turn;
// 		rightVelocity = -turn;
// 	} else {
// 		leftVelocity = power * (radius + DRIVE_WIDTH / 2) / radius;
// 		rightVelocity = power * (radius - DRIVE_WIDTH / 2) / radius;
// 	}
// 	if (holdDrive) drive.hold();
// 	else drive.coast();
// 	if (controller.get_digital(DIGITAL_B) && controller.get_digital(DIGITAL_Y)) drive.climb();
// 	drive.moveVelocityLeft(leftVelocity);
// 	drive.moveVelocityRight(rightVelocity);
// }
void moveDrive() {
	double power1 = controller.get_analog(ANALOG_LEFT_Y);
	double turn2 = controller.get_analog(ANALOG_RIGHT_X);

	power1 = fmax(fabs(power1) - 10, 0) * sign(power1);
	turn2 = fmax(fabs(turn2) - 5, 0) * sign(turn2);
	double p = 1; // constants
	double t = 4.5;
	power1 = (pow(M_E, -p/10) + pow(M_E, (fabs(power1)-127)/10) * (1-pow(M_E, -p/10))) * power1; // just the pilons drive curves
	turn2 = (pow(M_E, -t/10) + pow(M_E, (fabs(turn2)-127)/10) * (1-pow(M_E, -t/10))) * turn2; 

	double turn = turn2;
	double power = power1;

	leftVelocity = (0.925 * power1 + 0.8 * turn2) * 600 / 127;
	rightVelocity = (0.925 * power1 - 0.8 * turn2) * 600 / 127;
  
	if (controller.get_digital(DIGITAL_X) && !XMode) holdDrive = !holdDrive;
	if (holdDrive) drive.hold();
	else drive.coast();

	drive.moveVelocityLeft(leftVelocity);
	drive.moveVelocityRight(rightVelocity);
}

void moveTankDrive() {
	double powerLeft = controller.get_analog(ANALOG_LEFT_Y);
	double powerRight = controller.get_analog(ANALOG_RIGHT_Y);
	drive.moveVelocityLeft(powerLeft * 600/127);
	drive.moveVelocityRight(powerRight * 600/127);
}

/**
 * Intake Function
 * 
 * Controls intake and kicker. Kicker only moves when intake moves backward
 * 
 * More basic controls for now, due to there being no sensors to detect things
 * 
 * Uses modes to determine acceleration
 * 
 * intakeMode:
 * 0 - stop
 * 1 - intake 600rpm
 * 2 - outake/shoot -450rpm
*/

int intakeMode = 0;
void moveIntake() {
	if (controller.get_digital(DIGITAL_R1) && !R1Mode) {
		if (intakeMode == 1) intakeMode = 0;
		else intakeMode = 1;
	} else if (!controller.get_digital(DIGITAL_DOWN) && controller.get_digital(DIGITAL_R2) && !R2Mode) {
		if (intakeMode == 2) intakeMode = 0;
		else intakeMode = 2;
	}

	switch (intakeMode) {
		case 0:
			intake.moveVelocity(0);
			break;
		case 1:
			intake.moveVelocity(200);
			break;
		case 2:
			intake.moveVelocity(-200);
			break;
	}
}

int kickerMode = 0;
void moveKicker() {
    if (controller.get_digital(DIGITAL_DOWN) && controller.get_digital(DIGITAL_R2) && !R2Mode) {
		if (kickerMode == 1) kickerMode = 2;
		else if (kickerMode == 2) kickerMode = 0;
		else kickerMode = 1;
	}

	switch (kickerMode) {
		case 0:
			kicker.target = 0;
			break;
		case 1:
			kicker.target = 180;
			break;
		case 2:
			kicker.target = 100;
			break;
	}
}

#endif