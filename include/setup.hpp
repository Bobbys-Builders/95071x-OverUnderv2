#ifndef SETUP_HPP
#define SETUP_HPP

#include "main.h"
#include "mechanisms/drivetrain.hpp"
#include "mechanisms/intake.hpp"
#include "mechanisms/kicker.hpp"
#include "mechanisms/wings.hpp"
#include "mechanisms/climb.hpp"
#include "utilClasses/pid.hpp"
#include "utilClasses/pose.hpp"

#define M_PI 3.14159265358979323846  /* pi */
#define M_E 2.7182818284590452353602874713526624977572
// TICKS_INCH = 300ticks/motorRotation * 4motorRotations/3wheelRotation * 1wheelRotation/(3.25*M_PI)inches
#define TICKS_INCH 39.1766013765 // ticks/inch
#define RADIANS_DEGREE 0.01744444444 // radians/degree
int timer = 0;
double xPos = 0;
double yPos = 0;
double driveXPos = 0;
double driveYPos = 0;
int selectedAuton;

// ports
const int FL_PORT = 18; // drive
const int ML_PORT = 10;
const int BL_PORT = 19;
const int FR_PORT = 12;
const int MR_PORT = 1;
const int BR_PORT = 11;

const int VODOM_PORT = 2; // odom rotation sensor
const int HODOM_PORT = 3;

const int INTL_PORT = 17; // intake
const int INTR_PORT = 13;

const int KCKL_PORT = 9; // kicker
const int KCKR_PORT = 4;
const int KCKROT_PORT = 30;

const int IMU_PORT = 20; // imu

const int EXP_PORT = 30; // 3 wire expander

const char CLM_PORT = 'H'; // climb
const char PTO_PORT = 'F';


const char FLP_PORT = 'D'; // wings
const char FRP_PORT = 'C';
const char BLP_PORT = 'B';
const char BRP_PORT = 'G';
const char ODOM_PORT = 'E'; // odom

// controller
pros::Controller controller(CONTROLLER_MASTER);

// mechanisms
Drivetrain drive(FL_PORT, ML_PORT, BL_PORT, FR_PORT, MR_PORT, BR_PORT, IMU_PORT, VODOM_PORT, HODOM_PORT, EXP_PORT, ODOM_PORT);
Intake intake(INTL_PORT, INTR_PORT);
Kicker kicker(KCKL_PORT, KCKR_PORT, KCKROT_PORT);
Climb climb(EXP_PORT, CLM_PORT, PTO_PORT);
Wings wings(EXP_PORT, FLP_PORT, FRP_PORT, BLP_PORT, BRP_PORT);

// pid
// Pid movePID(0, 17, 0.01, 30, 200000, 600, 0);
// Pid turnPID(0, 2, 0.0005, 2, 10000, 600, 0); // using velocity

Pid movePID(0, 30, 0.001, 15, 2000, 600, 0);
Pid turnPID(0, 10, 0.05, 100, 1500, 600, 0); // using voltage

Pid turnPID2(0, 3, 0.000, 0.5, 10000, 600, 0); // small(<30)
Pid turnPD3(0, 2.2, 0.000, 0.5, 10000, 600, 0); // large(120-180)
Pid swervePID(0, 2.15, 0.000, 0.5, 10000, 600, 0);
Pid swervePID2(0, 3, 0.000, 0.5, 10000, 600, 0);

#endif