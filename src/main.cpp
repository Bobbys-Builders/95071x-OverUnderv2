#include "main.h"
#include "setup.hpp"
#include "tasks.hpp"
#include "teleop.hpp"
#include "autonomous.hpp"
// #include "printFunctions.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// initVisualizer();
	kicker_task.suspend();
	kicker.moveVelocity(0);
	odom_task.suspend();
	print_task.suspend();
	drive_auto_task.suspend();
	autonSelector();
	if (!controller.get_digital(DIGITAL_A)) {
		controller.print(1, 7, "Reseting");
		drive.imu.reset(true);
		drive.imu.set_heading(0);
		setPos(0, 0);
	}
	odom_task.resume();
	kicker_task.resume();
	print_task.resume();
	drive_auto_task.resume();
	// resumeAutoTasks();
	preautonomous(curSelected);
	// autoHeading = drive.imu.get_heading();
	odom_task.suspend();
	kicker_task.suspend();
	print_task.suspend();
	drive_auto_task.suspend();
	// suspendAutoTasks();
	controller.clear();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	odom_task.suspend();
	kicker_task.suspend();
	print_task.suspend();
	drive_auto_task.suspend();
	// suspendAutoTasks();
	pros::delay(300);
	controller.clear();
	pros::delay(300);
	controller.print(1, 0, "Hope you lost the match >;)");
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	odom_task.suspend();
	kicker_task.suspend();
	print_task.suspend();
	drive_auto_task.suspend();
	// suspendAutoTasks();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	odom_task.resume();
	kicker_task.resume();
	print_task.resume();
	drive_auto_task.resume();
	// resumeAutoTasks();
	drive.odomPiston.set_value(false);

	// drive.imu.set_heading(autoHeading);
	switch (curSelected) {
		case 0:
		noAuton();
		break;

		case 1:
		closeSafeAuton();
		break;

		case 2:
		closeAuton();
		break;

		case 3:
		closeStealAuton();
		break;

		case 4:
		closeElimAuton2();
		break;

		case 5:
		farSafeAuton();
		break;

		case 6:
		farSafe6Auton();
		break;

		case 7:
		farElim6AutonDouble();
		break;

		case 8:
		skillsAuton();
		break;
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	odom_task.resume();
	kicker_task.resume();
	print_task.resume();
	drive_auto_task.suspend();

	while (true) {
		moveDrive();
		// weightedDrive();
		moveIntake();
		moveKicker();
		moveClimb();
		moveWings();
		// updateDisplay();
		updateButtons();

		if (controller.get_digital(DIGITAL_UP)) { // for testing auton
			if (controller.get_digital(DIGITAL_LEFT) && controller.get_digital(DIGITAL_RIGHT) && curSelected == 8) {
				drive_auto_task.resume();
				drive.odomPiston.set_value(false);
				skillsSegA();
				drive_auto_task.suspend();
			} else {
				pros::delay(500);

				if (controller.get_digital(DIGITAL_UP) && !controller.get_digital_new_press(DIGITAL_UP)) {
					controller.rumble(". . .");
					pros::delay(1500);
					drive_auto_task.resume();
					drive.odomPiston.set_value(false);
					// resumeAutoTasks();
					// drive.imu.set_heading(autoHeading);
					switch (curSelected) {
						case 0:
						testAuton();
						break;

						case 1:
						closeSafeAuton();
						break;

						case 2:
						closeAuton();
						break;

						case 3:
						closeStealAuton();
						break;

						case 4:
						closeElimAuton2();
						break;

						case 5:
						farSafeAuton();
						break;

						case 6:
						farSafe6Auton();
						break;

						case 7:
						farElim6Auton();
						break;

						case 8:
						skillsAuton();
						break;
					}
					pros::delay(50);
					drive_auto_task.suspend();
					// suspendAutoTasks();
				}
			}
		}
		
		pros::delay(10);

		timer = (timer + 10) % 1000;
	}
}
