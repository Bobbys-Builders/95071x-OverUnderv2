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

std::vector<std::string> autons{"None", "Close Safe (1+2+Pole)", "Close (1+4+Pole)", "Close Steal", "Close Elim", "Far Safe", "Far Safe 6", "Far Elim 6", "Skills"};
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
	controller.print(0, 0, "DR %.0f IN %.0f KC %.0f                            ", drive.getAvgTemps(), intake.getTemperature(), kicker.getAvgTemp());
}

void getMaxTemperature() {
	std::vector<double> temps;
	std::vector<std::string> motor{"FL", "ML", "BL", "FR", "MR", "BR", "INL", "INR", "KL", "KR"};
	temps.push_back(drive.FLMotor.get_temperature());
	temps.push_back(drive.MLMotor.get_temperature());
	temps.push_back(drive.BLMotor.get_temperature());
	temps.push_back(drive.FRMotor.get_temperature());
	temps.push_back(drive.MRMotor.get_temperature());
	temps.push_back(drive.BRMotor.get_temperature());
	temps.push_back(intake.INTLMotor.get_temperature());
	temps.push_back(intake.INTRMotor.get_temperature());
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
  // controller.print(2, 0, "X%.1f Y%.1f H%.1f                 ", xPos, yPos, drive.imu.get_heading());
  controller.print(2, 0, "X%.1f Y%.1f H%.1f                 ", xPos, yPos, drive.imu.get_heading());
  // master.print(0, 0, "X %.1f H %.1f                 ", xPosition, (drivetrain.getLeftPosition() + drivetrain.getRightPosition()) / 2 / ticksPerInch);
}

void getKCKSpeed() {
  controller.print(2, 0, "KC V%0f, %.2fKPS                 ", kicker.getRealVelocity(), kicker.getRealVelocity() / 60);
  // controller.print(2, 0, "KC V %0f, %.2fKPS                 ", kicker.getPosition(), 0);
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
			// getKCKSpeed();
			getPosition();
		}
		
		pros::delay(100);
		printNum = (printNum + 1) % 3;
    // std::cout << "X: " << xPos << ", Y: " << yPos << ", H: " << drive.imu.get_heading() << std::endl;
	}
}

//CONSTANTS
static int MAP_CENTER_X = 0;
static int MAP_CENTER_Y = 0;
static int CIRCLE_RADIUS = 15;
static lv_style_t style;
static lv_style_t headingStyle;
static lv_style_t historyStyle;

//MUTABLE OBJECTS
lv_obj_t * headingIndicator;
lv_obj_t * arc;
lv_obj_t * posHistory;

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
lv_line_set_style(headingIndicator, &headingStyle);

//HISTORY SETUP 
lv_style_copy(&historyStyle, &lv_style_plain);
historyStyle.line.color = LV_COLOR_GREEN;
historyStyle.line.width = 3;

posHistory =  lv_arc_create(lv_scr_act(),NULL);
lv_arc_set_style(posHistory, LV_ARC_STYLE_MAIN, &historyStyle);
lv_arc_set_angles(posHistory,0,360);
lv_obj_set_size(posHistory, 5,5);

}

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
//CREATE HISTORY DRAG FOR POSITION MAPPING

// posHistory = lv_arc_create(lv_scr_act(), posHistory);
// lv_obj_align(posHistory, NULL,LV_ALIGN_IN_TOP_LEFT, BOT_POS_X-2,BOT_POS_Y-2);

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

// keeps track of the position of the robot in inches(imagines the field as a cartesian plane, with (0, 0) being a corner)
double lastHeading;
double deltaX = 0;
double deltaY = 0;
double deltaH = 0;
void odometryTask() {
	lastHeading = (90-(drive.imu.get_heading()+90)) * RADIANS_DEGREE; // all angles are in radians, with 0 degrees being the wall closest to the drive team
	while (true) {

		pros::delay(10);

		double heading = (90-(drive.imu.get_heading()+90)) * RADIANS_DEGREE; // new inputs
		double VChange = drive.getPositionV()/360 * 2.75*M_PI;
		double HChange = drive.getPositionH()/360 * 2.75*M_PI;

		double localXPos;
		double localYPos;
		if (fabs(heading-lastHeading) <= 0.0000001) { // if the change in heading is small enough, assume the robot traveled in a straight line
			localXPos = HChange;
			localYPos = VChange;
		} else { // imagines the movement as an arc
			localXPos = (2*sin((heading-lastHeading)/2))*((HChange/(heading-lastHeading))-5.25); 
			localYPos = (2*sin((heading-lastHeading)/2))*((VChange/(heading-lastHeading))-1);
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

		// xPos+=localLength*cos(global_polar_angle); // adds the relative changes to the actual positions
		// yPos-=localLength*sin(global_polar_angle);
		xPos+=fmax(-1, fmin(1, localLength*cos(global_polar_angle))); // adds the relative changes to the actual positions
		yPos-=fmax(-1, fmin(1, localLength*sin(global_polar_angle)));
		deltaX=localLength*cos(global_polar_angle); // adds the relative changes to the actual positions
		deltaY=-localLength*sin(global_polar_angle);
    deltaH = heading - lastHeading;


    // if (fabs(heading-lastHeading) > 10*RADIANS_DEGREE || sqrt(localLength*sin(global_polar_angle) + localLength*cos(global_polar_angle))) controller.rumble("----------");

		lastHeading = heading; // all angles are in radians, with 0 degrees being the wall closest to the drive team
		// updateVisualizer(lastHeading);
	}
}

// keeps track of the position of the robot in inches(imagines the field as a cartesian plane, with (0, 0) being a corner)
/*
double lastLPosition = 0;
double lastRPosition = 0;
double lastH = 0;
void driveOdometryTask() {

  lastLPosition = drive.getPositionLeft(); // keeping track of the previous positions because resetting encoders is hard to coordinate with multiple threads
  lastRPosition = drive.getPositionRight();
  lastH = (90-drive.imu.get_heading()) * RADIANS_DEGREE; // all angles are in radians, with 0 degrees being the wall closest to the drive team
  while (true) {

    pros::delay(10);

    double heading = (90-drive.imu.get_heading()) * RADIANS_DEGREE; // new inputs
    double LChange = drive.getPositionLeft() - lastLPosition;
    double RChange = drive.getPositionRight() - lastRPosition;
    if ((RChange == 0 && LChange == 0) || (RChange / LChange > 0.995 && RChange / LChange < 1.005) || fabs(lastH - heading) <= 0.005) { // if the change in left and right is close enough, assume the robot traveled in a straight line
      xPos += (LChange + RChange) / 2 * cos((heading + lastH) / 2) / TICKS_INCH;
      yPos += (LChange + RChange) / 2 * sin((heading + lastH) / 2) / TICKS_INCH;
    } else { // imagines the movement as an arc
      double radius = ((LChange + RChange) / (LChange - RChange) * 10 / 2 * TICKS_INCH
       + LChange / (lastH - heading)
       + RChange / (lastH - heading))/3;
      double relativeX = radius * sin(lastH - heading);
      double relativeY = radius * (1 - cos(lastH - heading)); // calculates the change in x if the last position was (0, 0) and the last heading was 0 degrees

      xPos += (relativeX * cos(lastH) + relativeY * cos(lastH - M_PI / 2)) / TICKS_INCH; // adds the relative changes to the actual positions
      yPos += (relativeX * sin(lastH) + relativeY * sin(lastH - M_PI / 2)) / TICKS_INCH;
    }

    lastLPosition += LChange; // keeping track of the previous positions because resetting encoders is hard to coordinate with multiple threads
    lastRPosition += RChange;
    lastH = heading; // all angles are in radians, with 0 degrees being the wall closest to the drive team
  }
}
*/

double maxMoveSpeed = 600;
double maxTurnSpeed = 600;
double maxMotorSpeed = 600;
bool driveDisabled = true;
bool boomerAng = false;
int driveMode = 0; // 0-both, 1-forwards, 2-backwards
Pid odomMPID = movePID;
Pid odomTPID = turnPID;
double targetX = 0;
double targetY = 0;
double targetH = 0;
double chainX = 0;
double chainY = 0;
void setTargetPos(double x, double y, double h = targetH) {
  targetX = x;
  targetY = y;
  targetH = M_PI/2-h*RADIANS_DEGREE;
  chainX = x;
  chainY = y;
  odomMPID.resetID();
  odomTPID.resetID();
  pros::delay(10);
}
void setChainPos(double x, double y) {
  chainX = x;
  chainY = y;
  odomTPID.resetID();
  pros::delay(10);
}

void driveAutoTask() {
  double close = false;
  while (true) {
    double power, turn;
    odomMPID.maxLim = maxMoveSpeed;
    odomTPID.maxLim = maxTurnSpeed;
    // halve speed when close to target
    if (positionError(targetX, targetY) < 7.5) close = true;
    else close = false;

    if (!boomerAng) {
      if ((fabs(headingError(chainX, chainY)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) odomTPID.update(headingError(chainX, chainY));
      else odomTPID.update(headingError(heading(chainX, chainY) + 180));

      turn = odomTPID.calculateOut();
      // odomMPID.update(positionError(targetX, targetY));
      if (close) odomMPID.update(positionError(chainX, chainY) * cos(headingError(chainX, chainY) * RADIANS_DEGREE));
      else odomMPID.update(positionError(chainX, chainY) * sign(cos(headingError(chainX, chainY) * RADIANS_DEGREE)));
      // odomMPID.update(positionError(chainX, chainY) * cos(headingError(chainX, chainY) * RADIANS_DEGREE));
      power = odomMPID.calculateOut();
    } else { // boomerAng
      // calculate the carrot point
      chainX = targetX - cos(targetH) * 0.6 * fmax(positionError(targetX, targetY)-7.5, 0);
      chainY = targetY - sin(targetH) * 0.6 * fmax(positionError(targetX, targetY)-7.5, 0);
      if (close) { // settling behavior
        chainX = targetX;
        chainY = targetY;
      }

      // calculate error
      if (close) {
        if ((fabs(headingError(targetX, targetY)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) odomTPID.update(headingError((M_PI/2-targetH)/RADIANS_DEGREE));
        else odomTPID.update(headingError((M_PI/2-targetH)/RADIANS_DEGREE) + 180);
      } else {
        if ((fabs(headingError(chainX, chainY)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) odomTPID.update(headingError(chainX, chainY));
        else odomTPID.update(headingError(heading(chainX, chainY) + 180));
      }
      turn = odomTPID.calculateOut();
      odomMPID.update(positionError(chainX, chainY));
      if (close) odomMPID.update(positionError(chainX, chainY) * cos(headingError(chainX, chainY) * RADIANS_DEGREE));
      else odomMPID.update(positionError(chainX, chainY) * sign(cos(headingError(chainX, chainY) * RADIANS_DEGREE)));
      power = odomMPID.calculateOut();
    }

    double radius = fabs(positionError(chainX, chainY)/2 / sin(headingError(chainX, chainY) * RADIANS_DEGREE));
    double maxSlipSpeed = (sqrt(0.19778781931 * radius*9.81*39.3701))*60/(3.25*M_PI)*600/450;
    // double maxSlipSpeed = (sqrt(4000 * radius));
    power = fmin(fmax(power, -maxSlipSpeed), maxSlipSpeed);
    // prioritize angular movement over lateral movement
    // double overturn = fabs(turn) + fabs(power) - maxMotorSpeed;
    // if (overturn > 0) power -= (power > 0 ? overturn : -overturn);

    double leftVelocity = power + turn;
    double rightVelocity = power - turn;
    double ratio = fmax(fabs(leftVelocity), fabs(rightVelocity)) / maxMotorSpeed;
    if (ratio > 1) {
      leftVelocity /= ratio;
      rightVelocity /= ratio;
    }
    if (!driveDisabled) {
      drive.moveVoltageLeft(leftVelocity*20);
      drive.moveVoltageRight(rightVelocity*20);
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

// void driveAutoTask() {
//   while (true) {
//     // double power, turn;
//     // movePID.maxLim = fmin(maxMoveSpeed, 450); // set limits
//     odomMPID.maxLim = maxMoveSpeed;
//     odomTPID.maxLim = maxTurnSpeed;

//     if (!arcMovement && positionError(targetX, targetY) > 0.5) {
//       if ((fabs(headingError(chainX, chainY)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) {
//         odomTPID.update(headingError(chainX, chainY));
//         // turn = odomTPID.calculateOut();
//       } else {
//         odomTPID.update(headingError(heading(chainX, chainY) + 180));
//         // turn = odomTPID.calculateOut();
//       }
// 	  // double out = positionError(targetX, targetY) * cos(headingError(chainX, chainY) * RADIANS_DEGREE);
//       // odomMPID.update(out);
//       odomMPID.update(positionError(targetX, targetY) * cos(headingError(chainX, chainY) * RADIANS_DEGREE));
// 	//   double expectedX = xPos + odomMPID.calculateOut() * sin(drive.imu.getHeading())*343/600*4*M_PI/60;
// 	//   double expectedY = yPos + odomMPID.calculateOut() * cos(drive.imu.getHeading())*343/600*4*M_PI/60;
//   //     if ((fabs(headingError(chainX, chainY)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) {
       
//   //  odomTPID.update(headingError(xPos+chainX-expectedX, yPos+chainY-expectedY));
//   //     } else {
//   //       odomTPID.update(headingError(heading(xPos+chainX-expectedX, yPos+chainY-expectedY) + 180));
//   //     }
// 	//   if (fabs(headingError(chainX, chainY)) > 75) out = 0;
//     } else if (arcMovement && positionError(targetX, targetY) > 0.5) {
//       double radius = positionError(targetX, targetY)/2 / sin(headingError(targetX, targetY) * RADIANS_DEGREE);
//       odomMPID.update(sqrt(fabs(radius * 2*headingError(targetX, targetY) * RADIANS_DEGREE)) * sign(cos(headingError(targetX, targetY) * RADIANS_DEGREE)));
//       // odomMPID.update(fabs(radius * 2*headingError(targetX, targetY) * RADIANS_DEGREE) * sign(cos(headingError(targetX, targetY) * RADIANS_DEGREE)));
//     } else {
//       odomMPID.update(0);
//       odomTPID.update(0);
//     }

//     double turnScaled = fabs(odomMPID.calculateOut()) > 250 ? odomTPID.calculateOut() * (1+.5*((fabs(odomMPID.calculateOut())-250)/250)) : odomTPID.calculateOut();
//     // double turnScaled = fabs(power) > 250 ? turn * (1+.5*((fabs(power)-250)/250)) : turn;
//     if (!driveDisabled && !arcMovement) {
//       drive.moveVelocityLeft(odomMPID.calculateOut() + turnScaled);
//       drive.moveVelocityRight(odomMPID.calculateOut() - turnScaled);
//     } else if (!driveDisabled && arcMovement) {
//       double radius = positionError(targetX, targetY)/2 / sin(headingError(targetX, targetY) * RADIANS_DEGREE);
//       drive.moveVelocityLeft(odomMPID.calculateOut() * (radius + 10 / 2)/radius);
//       drive.moveVelocityRight(odomMPID.calculateOut() * (radius - 10 / 2)/radius);
//     }

//     pros::delay(10);

//     // controller.print(0, 0, "%.1f %.1f %.1f", xPos, yPos, drive.imu.get_heading());
//     // std::cout << xPosition << " "
//     //  << yPosition << " "
//     //  << -headingError(0) << " "
//     //  << moveVelocity << " " 
//     //  << turnVelocity << std::endl;
//   }
// }

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
	// drive_auto_task.suspend();
	// drive.stop();
	// while (!controller.get_digital_new_press(DIGITAL_A)) {
	// 	pros::delay(10);
	// }
	// drive_auto_task.resume();
}

bool move(double target, Pid mPID = movePID, Pid tPID = turnPID, int timeout = 0, double extraTime = 0, double tolerance = 0.5) {
  driveDisabled = true;
  print_task.suspend();

  target += (double)drive.vOdom.get_position()*2.75*M_PI/36000;
  double initialT = drive.imu.get_heading();

  mPID.resetID();
  tPID.resetID();
  mPID.maxLim = maxMoveSpeed;
  tPID.maxLim = maxTurnSpeed;
  if (timeout <= 0) timeout = 9999999;
  while (fabs(target+(double)drive.vOdom.get_position()*2.75*M_PI/36000) > tolerance && timeout > 0) {
    mPID.update(target+(double)drive.vOdom.get_position()*2.75*M_PI/36000);
    tPID.update(headingError(initialT));
    // drive.moveVelocityLeft(mPID.calculateOut() + tPID.calculateOut());
    // drive.moveVelocityRight(mPID.calculateOut() - tPID.calculateOut());
    drive.moveVoltageLeft((mPID.calculateOut() + tPID.calculateOut())*20);
    drive.moveVoltageRight((mPID.calculateOut() - tPID.calculateOut())*20);
    pros::delay(10);
    timeout -= 10;
    controller.print(0, 0, "T%.1f C%.1f E%.1f                 ", target, (double)drive.vOdom.get_position()*2.75*M_PI/36000, target-(double)drive.vOdom.get_position()*2.75*M_PI/36000);
  }
  while (extraTime > 0) {
    mPID.update(target+(double)drive.vOdom.get_position()*2.75*M_PI/36000);
    tPID.update(headingError(initialT));
    // drive.moveVelocityLeft(mPID.calculateOut() + tPID.calculateOut());
    // drive.moveVelocityRight(mPID.calculateOut() - tPID.calculateOut());
    drive.moveVoltageLeft((mPID.calculateOut() + tPID.calculateOut())*20);
    drive.moveVoltageRight((mPID.calculateOut() - tPID.calculateOut())*20);
    pros::delay(10);
    extraTime -= 10;
    controller.print(0, 0, "T%.1f C%.1f E%.1f                 ", target, (double)drive.vOdom.get_position()*2.75*M_PI/36000, target-(double)drive.vOdom.get_position()*2.75*M_PI/36000);
  }
  drive.stop();
	untilKeyPress();
  driveDisabled = false;
  if (timeout > 0) return true;
  print_task.resume();
  return false;
}

bool turn(double target, Pid tPID = turnPID, int timeout = 0, double extraTime = 0, double tolerance = 1) {
  driveDisabled = true;

  tPID.resetID();
  tPID.maxLim = maxTurnSpeed;
  if (timeout <= 0) timeout = 9999999;
  while (fabs(headingError(target)) > tolerance && timeout > 0) {
    tPID.update(headingError(target));
    // drive.moveVelocityLeft(tPID.calculateOut());
    // drive.moveVelocityRight(-tPID.calculateOut());
    drive.moveVoltageLeft(tPID.calculateOut()*20);
    drive.moveVoltageRight(-tPID.calculateOut()*20);
    pros::delay(10);
    timeout -= 10;
  }
  while (extraTime > 0) {
    tPID.update(headingError(target));
    // drive.moveVelocityLeft(tPID.calculateOut());
    // drive.moveVelocityRight(-tPID.calculateOut());
    drive.moveVoltageLeft(tPID.calculateOut()*20);
    drive.moveVoltageRight(-tPID.calculateOut()*20);
    pros::delay(10);
    extraTime -= 10;
  }
  drive.stop();
	untilKeyPress();
  driveDisabled = false;
  if (timeout > 0) return true;
  return false;
}

bool swerve(double tX, double tY, Pid tPID = swervePID, int timeout = 0, double extraTime = 0, double tolerance = 1) {
  driveDisabled = true;

  tPID.resetID();
  tPID.maxLim = maxTurnSpeed;
  if (timeout <= 0) timeout = 9999999;
  while ((fabs(headingError(tX, tY)) > tolerance && fabs(headingError(heading(tX, tY) + 180)) > tolerance) && timeout > 0) {
    double mOut = 0;
    if ((fabs(headingError(tX, tY)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) {
      tPID.update(headingError(tX, tY));
      mOut = fabs(tPID.calculateOut());
    } else {
      tPID.update(headingError(heading(tX, tY) + 180));
      mOut = -fabs(tPID.calculateOut());
    }
    drive.moveVoltageLeft((mOut + tPID.calculateOut())*20/2);
    drive.moveVoltageRight((mOut - tPID.calculateOut())*20/2);
    pros::delay(10);
    timeout -= 10;
  }
  while (extraTime > 0) {
    double mOut = 0;
    if ((fabs(headingError(tX, tY)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) {
      tPID.update(headingError(tX, tY));
      mOut = fabs(tPID.calculateOut());
    } else {
      tPID.update(headingError(heading(tX, tY) + 180));
      mOut = -fabs(tPID.calculateOut());
    }
    drive.moveVoltageLeft((mOut + tPID.calculateOut())*20/2);
    drive.moveVoltageRight((mOut - tPID.calculateOut())*20/2);
    pros::delay(10);
    extraTime -= 10;
  }
  drive.stop();
	untilKeyPress();
  driveDisabled = false;
  if (timeout > 0) return true;
  return false;
}

bool swerve(double target, Pid tPID = swervePID, int timeout = 0, double extraTime = 0, double tolerance = 1) {
  driveDisabled = true;

  tPID.resetID();
  tPID.maxLim = maxTurnSpeed;
  if (timeout <= 0) timeout = 9999999;
  while ((fabs(headingError(target)) > tolerance && fabs(headingError(target + 180)) > tolerance) && timeout > 0) {
    double mOut = 0;
    if ((fabs(headingError(target)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) {
      tPID.update(headingError(target));
      mOut = fabs(tPID.calculateOut());
    } else {
      tPID.update(headingError(target));
      mOut = -fabs(tPID.calculateOut());
    }
    drive.moveVoltageLeft((mOut + tPID.calculateOut())*20/2);
    drive.moveVoltageRight((mOut - tPID.calculateOut())*20/2);
    pros::delay(10);
    timeout -= 10;
  }
  while (extraTime > 0) {
    double mOut = 0;
    if ((fabs(headingError(target)) <= 90 && !(driveMode == 2)) || (driveMode == 1)) {
      tPID.update(headingError(target));
      mOut = fabs(tPID.calculateOut());
    } else {
      tPID.update(headingError(target));
      mOut = -fabs(tPID.calculateOut());
    }
    drive.moveVoltageLeft((mOut + tPID.calculateOut())*20/2);
    drive.moveVoltageRight((mOut - tPID.calculateOut())*20/2);
    pros::delay(10);
    extraTime -= 10;
  }
  drive.stop();
	untilKeyPress();
  driveDisabled = false;
  if (timeout > 0) return true;
  return false;
}

void botMove(double dist, double vel, bool brake = true, bool block = true) {
  driveDisabled = true;
  pros::delay(20);
  drive.moveRelativeLeft(TICKS_INCH * dist, vel);
  drive.moveRelativeRight(TICKS_INCH * dist, vel);

  if (block) pros::delay(fabs(dist) * TICKS_INCH / vel / 300 * 60 * 1000 + 80);
  
  if (block && brake) drive.stop();
  driveDisabled = false;
}

bool untilTargetPos(double tolerance, int timeout = 0, bool antiStall = false, int stallStates = 10, double tX = chainX, double tY = chainY) {
  if (timeout <= 0) timeout = 9999999;
  int time = 0;
  int stalledStates = 0;
  while (positionError(tX, tY) > tolerance && time < timeout) {
    if ((sqrt(deltaX*deltaX+deltaY*deltaY) < 0.02 || fabs(drive.imu.get_roll()) > 15) && time > 500) stalledStates++;
    else stalledStates = 0;
    if (stalledStates > stallStates && antiStall) return false;
    time += 10;
    pros::delay(10);
  }
	untilKeyPress();
  if (time < timeout) return true;
  // botMove((driveMode*2-3)*5, 300);
  return false;
}

bool untilTargetH(double tolerance, int timeout = 0, double extraTime = 0, bool antiStall = false, int stallStates = 10, double tX = chainX, double tY = chainY) {
  if (timeout <= 0) timeout = 9999999;
  int time = 0;
  int stalledStates = 0;
  if (driveMode == 0) {
    while (fmin(fabs(headingError(tX, tY)), fabs(headingError(heading(tX, tY) + 180))) > tolerance && time < timeout) {
      if (fabs(deltaH) < 0.05 && time > 500) stalledStates++;
      else stalledStates = 0;
      if (stalledStates > stallStates && antiStall) return false;
      time += 10;
      pros::delay(10);
    }
  } else if (driveMode == 1) {
    while (fabs(headingError(tX, tY)) > tolerance && time < timeout) {
      if (fabs(deltaH) < 0.05 && time > 500) stalledStates++;
      else stalledStates = 0;
      if (stalledStates > stallStates && antiStall) return false;
      time += 10;
      pros::delay(10);
    }
  } else if (driveMode == 2) {
    while (fabs(headingError(heading(tX, tY) + 180)) > tolerance && time < timeout) {
      if (fabs(deltaH) < 0.05 && time > 500) stalledStates++;
      else stalledStates = 0;
      if (stalledStates > stallStates && antiStall) return false;
      time += 10;
      pros::delay(10);
    }
  }
  pros::delay(extraTime);
  untilKeyPress();
  if (timeout > 0) return true;
  return false;
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