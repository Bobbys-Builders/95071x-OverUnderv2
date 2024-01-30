#ifndef SETUP_HPP
#define SETUP_HPP

#include "main.h"
#include "mechanisms/drivetrain.hpp"
#include "mechanisms/intake.hpp"
#include "mechanisms/kicker.hpp"
#include "mechanisms/wings.hpp"
#include "mechanisms/climb.hpp"

#define M_PI 3.14159265358979323846  /* pi */
#define M_E 2.7182818284590452353602874713526624977572
// TICKS_INCH = 300ticks/motorRotation * 7motorRotations/4wheelRotation * 1wheelRotation/(4*M_PI)inches
#define TICKS_INCH 41.7781725616 // ticks/inch
#define RADIANS_DEGREE 0.01744444444 // radians/degree
int timer = 0;
double xPos = 0;
double yPos = 0;
int selectedAuton;

// ports
const int FL_PORT = 17; // drive
const int ML_PORT = 18;
const int BL_PORT = 19;
const int FR_PORT = 14;
const int MR_PORT = 12;
const int BR_PORT = 15;

const int VODOM_PORT = 9; // odom rotation sensor
const int HODOM_PORT = 10;

const int INT_PORT = 20; // intake

const int KCKL_PORT = 8; // kicker
const int KCKR_PORT = 2;

const int KCKROT_PORT = 7; // kicker rotation sensor

const int EXP_PORT = 15; // 3 wire expander

const int IMU_PORT = 16; // imu

const char CLMU_PORT = 'F'; // climb
const char CLMD_PORT = 'B';


const char FLP_PORT = 'D'; // wings
const char FRP_PORT = 'D';
const char BLP_PORT = 'A';
const char BRP_PORT = 'C';
const char ODOM_PORT = 'E'; // odom

// controller
pros::Controller controller(CONTROLLER_MASTER);

// mechanisms
Drivetrain drive(FL_PORT, ML_PORT, BL_PORT, FR_PORT, MR_PORT, BR_PORT, IMU_PORT, VODOM_PORT, HODOM_PORT, EXP_PORT, ODOM_PORT);
Intake intake(INT_PORT);
Kicker kicker(KCKL_PORT, KCKR_PORT, KCKROT_PORT);
Climb climb(EXP_PORT, CLMU_PORT, CLMD_PORT);
Wings wings(EXP_PORT, FLP_PORT, FRP_PORT, BLP_PORT, BRP_PORT);

#endif