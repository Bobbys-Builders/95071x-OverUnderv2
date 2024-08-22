#ifndef SETUP_HPP
#define SETUP_HPP

#include "main.h"
#include "mechanisms/drivetrain.hpp"
#include "mechanisms/intake.hpp"

#include "mechanisms/climb.hpp"
#include "pid.hpp"

#define M_PI 3.14159265358979323846  /* pi */
#define M_E 2.7182818284590452353602874713526624977572
// TICKS_INCH = 300ticks/motorRotation * 7motorRotations/4wheelRotation * 1wheelRotation/(4*M_PI)inches
#define TICKS_INCH 41.7781725616 // ticks/inch
#define RADIANS_DEGREE 0.01744444444 // radians/degree
int timer = 0;
double xPos = 0;
double yPos = 0;
double driveXPos = 0;
double driveYPos = 0;
int selectedAuton;

// ports
const int FL_PORT = 1; // drive
const int ML_PORT = 2;
const int BL_PORT = 3;
const int FR_PORT = 4;
const int MR_PORT = 4;
const int BR_PORT = 6;

const int LINT_PORT = 7; // intake 
const int RINT_PORT = 8; 

const int LIFTLEFT_PORT = 9; // lift 
const int LIFTRIGHT_PORT = 10; 
const int LIFTROT_PORT = 11; // lift rotation sensor

const int EXP_PORT = 12; // 3 wire expander

const int IMU_PORT = 13; // imu


const char CLMP_PORT = 'B'; // clmp
const char HANG_PORT = 'D';

// controller
pros::Controller controller(CONTROLLER_MASTER);

// mechanisms
Drivetrain drive(FL_PORT, ML_PORT, BL_PORT, FR_PORT, MR_PORT, BR_PORT, IMU_PORT, EXP_PORT);
Intake intake(LINT_PORT, RINT_PORT);
Lift lift(LIFTLEFT_PORT, LIFTRIGHT_PORT);
Climb climb(EXP_PORT, HANG_PORT);
Clamp clamp(EXP_PORT, CLMP_PORT);

// pid
Pid movePID(0, 27, 0.000, 10, 20000, 600, 0);
Pid turnPID(0, 2.2, 0.000, 0.5, 10000, 600, 0); // medium(~30-120)
Pid turnPID2(0, 3, 0.000, 0.5, 10000, 600, 0); // small(<30)
Pid turnPID3(0, 2.2, 0.000, 0.5, 10000, 600, 0); // large(120-180)
Pid swervePID(0, 2.15, 0.000, 0.5, 10000, 600, 0);
Pid swervePID2(0, 3, 0.000, 0.5, 10000, 600, 0);

#endif