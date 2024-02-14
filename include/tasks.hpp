#ifndef TASKFUNCTIONS_HPP
#define TASKFUNCTIONS_HPP

#include "main.h"
#include "setup.hpp"
double sign(double input) {
	if (input == 0) return 1;
	return fabs(input) / input;
}

double modabs(double value, double mod) {
  return fmod(fmod(value, mod) + mod, mod);
}

std::vector<std::string> autons{"None", "Close Safe (1+2+Pole)", "Close (1+4+Pole)", "Close Elim", "Far Safe", "Far Safe 6", "Skills"};
int curSelected = 0;
void autonSelector() {
	while (true) {
		intake.moveVelocity(0);
		controller.print(0, 0, "%s                             ", autons[curSelected].c_str());

		if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
			curSelected = (curSelected + 1) % autons.size();
		} else if (controller.get_digital_new_press(DIGITAL_LEFT)) {
			curSelected = (curSelected - 1 + autons.size()) % autons.size();
		} else if (controller.get_digital(DIGITAL_A)) {
			// if (curSelected == 0) break;
			pros::delay(500);
			if (!controller.get_digital_new_press(DIGITAL_A) && controller.get_digital(DIGITAL_A)) {
				break;
			}
		}

		pros::delay(100);
	}

	controller.rumble("-");
	pros::delay(500);
	controller.clear();
	pros::delay(500);
}

void getAverageTemperature() {
	controller.print(0, 0, "DR %.0f IN %.0f KC %.0f                            ", drive.getAvgTemps(), intake.INTMotor.get_temperature(), kicker.getAvgTemp());
}

void getMaxTemperature() {
	std::vector<double> temps;
	std::vector<std::string> motor{"FL", "ML", "BL", "FR", "MR", "BR", "IN", "KL", "KR"};
	temps.push_back(drive.FLMotor.get_temperature());
	temps.push_back(drive.MLMotor.get_temperature());
	temps.push_back(drive.BLMotor.get_temperature());
	temps.push_back(drive.FRMotor.get_temperature());
	temps.push_back(drive.MRMotor.get_temperature());
	temps.push_back(drive.BRMotor.get_temperature());
	temps.push_back(intake.INTMotor.get_temperature());
	temps.push_back(kicker.KCKLMotor.get_temperature());
	temps.push_back(kicker.KCKRMotor.get_temperature());

	int max = 0;
	for (int i = 1; i < temps.size(); i++) {
		if ((temps[i] > temps[max] && temps[i] <= 200) || temps[max] > 200) {
			max = i;
		}
	}

	controller.print(1, 0, "Max: %s %.0f                            ", motor[max], temps[max]);
}

void getIntakeSpeed() {
	controller.print(2, 0, "INT%.1f rpm                         ", intake.getRealVelocity());
}

// void getAuton() {
// 	controller.print(2, 0, "%s                             ", autons[curSelected].c_str());
// }

void getPosition() {
  controller.print(2, 0, "X%.1f Y%.1f H%.1f                 ", xPos, yPos, drive.imu.get_heading());
  // master.print(0, 0, "X %.1f H %.1f                 ", xPosition, (drivetrain.getLeftPosition() + drivetrain.getRightPosition()) / 2 / ticksPerInch);
}

void getKCKSpeed() {
//   controller.print(1, 0, "KC Vel %0f, %.2f KPS                 ", kicker.getRealVelocity(), kicker.getRealVelocity() / 60);
  controller.print(2, 0, "KC V %0f, %.2fKPS                 ", kicker.getPosition(), 0);
}

void printTask() {
	int printNum = 0;
	while (true) {
		if (printNum == 0) {
			getAverageTemperature();
		}
		if (printNum == 1) {
			getMaxTemperature();
		}
		if (printNum == 2) {
			getPosition();
		}
		
		pros::delay(300);
		printNum = (printNum + 1) % 3;
	}
}

//CONSTANTS
static int MAP_CENTER_X = 0;
static int MAP_CENTER_Y = 0;
static int CIRCLE_RADIUS = 15;
static lv_style_t style;
static lv_style_t headingStyle;

//MUTABLE OBJECTS
lv_obj_t * headingIndicator;
lv_obj_t * arc;

void initVisualizer(){
  //BG
  lv_obj_t * bar1 = lv_bar_create(lv_scr_act(), NULL);
lv_obj_set_size(bar1, MAP_CENTER_X*2, MAP_CENTER_Y*2);
lv_obj_align(bar1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
lv_bar_set_value(bar1, 0);

static lv_style_t style_bar;
lv_style_copy(&style_bar, &lv_style_pretty);
style_bar.body.main_color = LV_COLOR_BLACK;
style_bar.body.grad_color = LV_COLOR_BLACK;
style_bar.body.radius = 0;
style_bar.body.border.color = LV_COLOR_BLACK;

lv_bar_set_style(bar1, LV_BAR_STYLE_BG, &style_bar);


//ARC SETUP
lv_style_copy(&style, &lv_style_plain);
style.line.color = LV_COLOR_RED;           /*Arc color*/
style.line.width = 2;         
              /*Arc width*/
 arc= lv_arc_create(lv_scr_act(), NULL);
lv_arc_set_style(arc, LV_ARC_STYLE_MAIN, &style);          /*Use the new style*/
lv_arc_set_angles(arc, 0, 360);
lv_obj_set_size(arc, CIRCLE_RADIUS*2, CIRCLE_RADIUS*2);

//LINE SETUP

lv_style_copy(&headingStyle, &lv_style_plain);
headingStyle.line.color = LV_COLOR_RED;
headingStyle.line.width = 3;

headingIndicator = lv_line_create(lv_scr_act(), NULL);

}

// keeps track of the position of the robot in inches(imagines the field as a cartesian plane, with (0, 0) being a corner)
double lastHeading;
void updateVisualizer(double heading){
  
 //UPDATE ROBOT POSITION VISUALIZATION
  double BOT_POS_X = MAP_CENTER_X+(yPos*(1.6666));
  double BOT_POS_Y = MAP_CENTER_Y+(xPos*(1.6666));

  //SHOW ROBOT POSITION CIRCLE
lv_obj_align(arc, NULL, LV_ALIGN_IN_TOP_LEFT, BOT_POS_X-CIRCLE_RADIUS, BOT_POS_Y-CIRCLE_RADIUS);

//SETUP ARRAY FOR HEADING VISUALIZER
 lv_point_t line_points[] = { {BOT_POS_X,BOT_POS_Y},{BOT_POS_X+(CIRCLE_RADIUS-1)*cos(heading),BOT_POS_Y-(CIRCLE_RADIUS-1)*sin(heading)} };
lv_line_set_points(headingIndicator, line_points, 2); 
lv_obj_align(headingIndicator, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
lv_line_set_style(headingIndicator,&headingStyle);
}

void kickerTask() {
	while (true) {
		// if (modabs(kicker.getPosition()+7500, 36000)-7500 < 23000 && kicker.target == 0) {
		// 	kicker.moveVelocity((25000-kicker.getPosition())/150);
		// } else if (modabs(kicker.getPosition()+6000, 36000)-6000 > 26000 && kicker.target == 0) {
		// 	kicker.KCKLMotor.move_voltage(0);
		// 	kicker.KCKRMotor.move_voltage(0);
		// } else if (kicker.target > 0) {
			kicker.updateVelocity();
			kicker.moveVelocity(kicker.velocity);
		// }

		pros::delay(10);
	}
}

// returns target - current
double headingError(double targetHeading) {
  if (modabs(targetHeading - drive.imu.get_heading(), 360) < 180) return modabs(targetHeading - drive.imu.get_heading(), 360);
  return modabs(targetHeading - drive.imu.get_heading(), 360) - 360;
}

double heading(double x, double y) {
  if (x-xPos == 0 && y-yPos == 0) return drive.imu.get_heading();
  if (x - xPos > 0) return 90 - atan((y - yPos) / (x - xPos)) / RADIANS_DEGREE;
  else if (x - xPos < 0) return 270 - atan((y - yPos) / (x - xPos)) / RADIANS_DEGREE;
  else if (y - yPos >= 0) return 0;
  return 180;
}

// returns difference in heading from a point in imu degrees
double headingError(double x, double y) {
  return headingError(heading(x, y));
}

// returns the absolute distance to a point
double positionError(double x, double y) {
  return pow(pow(x - xPos, 2) + pow(y - yPos, 2), 0.5);
}

void odometryTask() {
	lastHeading = (90-(drive.imu.get_heading()+90)) * RADIANS_DEGREE; // all angles are in radians, with 0 degrees being the wall closest to the drive team
	while (true) {

		pros::delay(10);

		double heading = (90-(drive.imu.get_heading()+90)) * RADIANS_DEGREE; // new inputs
		double VChange = drive.getPositionV()/360 * 2*M_PI;
		double HChange = drive.getPositionH()/360 * 2*M_PI;

		double localXPos;
		double localYPos;
		if (fabs(heading-lastHeading) <= 0.0001) { // if the change in heading is small enough, assume the robot traveled in a straight line
			localXPos = HChange;
			localYPos = VChange;
		} else { // imagines the movement as an arc
			localXPos = (2*sin((heading-lastHeading)/2))*((HChange/(heading-lastHeading))-6.25); 
			localYPos = (2*sin((heading-lastHeading)/2))*((VChange/(heading-lastHeading))+2);
		}

		float localHeading;
		float localLength;

		if (localXPos == 0 && localYPos == 0){
			localHeading = 0;
			localLength = 0;
		} else {
			localHeading = atan2(localYPos, localXPos); 
			localLength = sqrt(pow(localXPos, 2) + pow(localYPos, 2)); 
		}

		float global_polar_angle = localHeading - (heading + lastHeading)/2;

		xPos+=localLength*cos(global_polar_angle); // adds the relative changes to the actual positions
		yPos-=localLength*sin(global_polar_angle);

		lastHeading = heading; // all angles are in radians, with 0 degrees being the wall closest to the drive team
	//	updateVisualizer(lastHeading);
	}
}

void botMove(double dist, double vel, bool brake = true, bool block = true) {
  drive.hold();
  drive.moveRelativeLeft(TICKS_INCH * dist, vel);
  drive.moveRelativeRight(TICKS_INCH * dist, vel);

  if (block) pros::delay(fabs(dist) * TICKS_INCH / vel / 300 * 60 * 1000 + 80);
  // if (block) delay(fabs(dist) * ticksPerInch / vel / driveTicksPerRev * 60 * 1000);
  
  if (block && brake) drive.stop();
}

double maxMoveSpeed = 550;
double maxTurnSpeed = 350;
bool driveDisabled = true;
bool arcMovement = false;
int driveMode = 0; // 0-both, 1-forwards, 2-backwards
int chainMode = 0; // 0-regular chain, 1-turn chain
double targetX = 0;
double targetY = 0;
double chainX = 0;
double chainY = 0;
void setTargetPos(double x, double y) {
  targetX = x;
  targetY = y;
  chainX = x;
  chainY = y;
  movePID.resetID();
  turnPID.resetID();
  pros::delay(30);
}
void setChainPos(double x, double y) {
  chainX = x;
  chainY = y;
  turnPID.resetID();
  pros::delay(30);
}
void driveAutoTask() {
  while (true) {
    if (!arcMovement && positionError(targetX, targetY) > 0.5) {
      if ((fabs(headingError(chainX, chainY)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) {
        turnPID.update(headingError(chainX, chainY));
      } else {
        turnPID.update(headingError(heading(chainX, chainY) + 180));
      }
      movePID.update(positionError(targetX, targetY) * cos(headingError(chainX, chainY) * RADIANS_DEGREE));
    } else if (arcMovement  && positionError(targetX, targetY) > 0.5) {
      double radius = positionError(targetX, targetY)/2 / sin(headingError(targetX, targetY) * RADIANS_DEGREE);
      movePID.update(sqrt(fabs(radius * 2*headingError(targetX, targetY) * RADIANS_DEGREE)) * sign(cos(headingError(targetX, targetY) * RADIANS_DEGREE)));
    } else {
      movePID.update(0);
      turnPID.update(0);
    }

    movePID.maxLim = maxMoveSpeed;
    turnPID.maxLim = maxTurnSpeed;
    if (!driveDisabled && !arcMovement) {    
      drive.moveVelocityLeft(movePID.calculateOut() + turnPID.calculateOut());
      drive.moveVelocityRight(movePID.calculateOut() - turnPID.calculateOut());
    } else if (!driveDisabled && arcMovement) {
      double radius = positionError(targetX, targetY)/2 / sin(headingError(targetX, targetY) * RADIANS_DEGREE);
      drive.moveVelocityLeft(movePID.calculateOut() * (radius + 10 / 2)/radius);
      drive.moveVelocityRight(movePID.calculateOut() * (radius - 10 / 2)/radius);
    }

    pros::delay(10);

    // controller.print(0, 0, "%.1f %.1f %.1f", xPos, yPos, drive.imu.get_heading());
    // std::cout << xPosition << " "
    //  << yPosition << " "
    //  << -headingError(0) << " "
    //  << moveVelocity << " " 
    //  << turnVelocity << std::endl;
  }
}

pros::Task kicker_task(kickerTask);
pros::Task odom_task(odometryTask);
pros::Task drive_auto_task(driveAutoTask);
pros::Task print_task(printTask);

void setPos(double x, double y, double heading = drive.imu.get_heading()) {
  odom_task.suspend();
  pros::delay(20);
  xPos = x;
  yPos = y;
  drive.imu.set_heading(heading);
  pros::delay(20);
  drive.lastHOdom = drive.hOdom.get_position();
  drive.lastVOdom = drive.vOdom.get_position();
  lastHeading = (90-(drive.imu.get_heading()+90))*RADIANS_DEGREE;
  odom_task.resume();
}

void untilKeyPress() {
	drive_auto_task.suspend();
	drive.stop();
	while (!controller.get_digital_new_press(DIGITAL_A)) {
		pros::delay(10);
	}
	drive_auto_task.resume();
}

void untilTargetPos(double tolerance, int timeout, double extraTime = 0, double tX = chainX, double tY = chainY) {
  while (positionError(tX, tY) > tolerance && timeout > 0) {
    timeout -= 10;
    pros::delay(10);
  }
  pros::delay(extraTime);
	// untilKeyPress();
}

void untilTargetH(double tolerance, int timeout, double extraTime = 0, double tX = chainX, double tY = chainY) {
  if (driveMode == 0) {
    while (fmin(fabs(headingError(tX, tY)), fabs(headingError(heading(tX, tY) + 180))) > tolerance && timeout > 0) {
      timeout -= 10;
      pros::delay(10);
    }
  } else if (driveMode == 1) {
    while (fabs(headingError(tX, tY)) > tolerance && timeout > 0) {
      timeout -= 10;
      pros::delay(10);
    }
  } else if (driveMode == 2) {
    while (fabs(headingError(heading(tX, tY) + 180)) > tolerance && timeout > 0) {
      timeout -= 10;
      pros::delay(10);
    }
  }
  pros::delay(extraTime);

    // untilKeyPress();
}

// void setPos(double x, double y) {
//   odom_task.suspend();
//   pros::delay(20);
//   xPos = x;
//   yPos = y;
//   pros::delay(20);
//   drive.lastHOdom = drive.hOdom.get_position();
//   drive.lastVOdom = drive.vOdom.get_position();
//   odom_task.resume();
// }

#endif