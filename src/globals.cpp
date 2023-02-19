#include "flywheel/flywheelImplementation.hpp"
#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/impl/device/controller.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/util/timer.hpp"
#include "pros/rtos.h"

/*GLOBAL VARS*/
bool modKey = false;
int globalFlywheelRPM = 2000;

//Alliance color selector
alliancePosition currentAlliancePosition = middle;

/*DRIVE MEASUREMENTS*/
//Drive
const QLength trackWidth = 40_cm;
const QLength wheelDiameter = 4.125_in;
//Odom
const QLength odomTrackWidth = 215_mm;
const QLength backOdomDist = 80_mm;

/*PORTS*/
//Drive
const int backLeftPort = 20;
const int backRightPort = 19;
const int frontRightPort = 17;
const int frontLeftPort = 18;
//Flywheel
const int flyBackPort = 11;
const int flyFrontPort = 12;
//Indexer
const int indexerPort = 13;
//Intake
const int intakePort = 14;
//Sensors
const int inertialPort = 10;

pros::IMU inertial = pros::IMU(inertialPort);


/*SETUP*/
Controller controller;
//Drivetrain
Motor backLeft = Motor(backLeftPort, true, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);
Motor backRight = Motor(backRightPort, false, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);
Motor frontLeft = Motor(frontLeftPort, true, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);
Motor frontRight = Motor(frontRightPort, false, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);

MotorGroup leftDrive = {backLeft, frontLeft};
MotorGroup rightDrive = {backRight, frontRight};

pros::ADIEncoder sideEncoder('A', 'B', true);
// pros::ADIEncoder rightEncoder('C', 'D', true);
pros::ADIEncoder middleEncoder('E', 'F', false);

std::vector<pros::ADIEncoder> encoderList = {sideEncoder, middleEncoder};
std::vector<pros::IMU> inertialList = {inertial};

TwoEncoderOdom driveOdom(0.0, 0.0, 2.75, 4.125, encoderList, inertialList);


/*
C,D front encoder
A,B left encoder
E,F right encoder
*/
std::shared_ptr<OdomChassisController> drive = ChassisControllerBuilder()
    .withMotors(leftDrive, rightDrive)
    .withDimensions(AbstractMotor::gearset::green, {{wheelDiameter, trackWidth}, imev5GreenTPR})
    .withSensors(
        ADIEncoder{'C', 'D'},
        ADIEncoder{'A', 'B', true},
        ADIEncoder{'E', 'F'}
    )
    .withOdometry({{2.75_in, odomTrackWidth, backOdomDist, 2.75_in}, quadEncoderTPR})
    .buildOdometry();

//Flywheel
sylib::SpeedControllerInfo flyController (
    [](double rpm){return 0;},
        0, // kP
        0, // kI
        0, // kD
        0, // kH
        false, // anti-windup enabled
        0, // anti-windup range
        false, // p controller bounds threshold enabled
        0, // p controller bounds cutoff enabled
        0, // kP2 for when over threshold
        0 // range to target to apply max voltage
);

sylib::Motor flyBack = sylib::Motor(flyBackPort, 600, false, flyController);
sylib::Motor flyFront =  sylib::Motor(flyFrontPort, 600, true, flyController);

//Indexer
Motor indexer = Motor(indexerPort, false, okapi::AbstractMotor::gearset::blue,
    okapi::AbstractMotor::encoderUnits::degrees);

Motor intake = Motor(intakePort, true, okapi::AbstractMotor::gearset::blue,
    okapi::AbstractMotor::encoderUnits::degrees);

//Endgame
pros::ADIDigitalOut pistonLeft('G', false);

/*GLOBAL FUNCTIONS*/
void isModKey() {
    modKey = controller.getDigital(ControllerDigital::R2);
}

void startGrafana() {
    // std::cout << pros::millis() << " , " << currentRPM
    //    << " , " << targetRPM << " , " << (motorPower / 10.0) << " , " << getError() << std::endl;
}

double exponential(double axisValue) {
  double percentage = axisValue;
  if (percentage > 0) {
    percentage = 1.2*pow(1.043, percentage) - 1.2 + 0.2 * percentage;
  }
  else {
    percentage = -percentage;

    percentage = 1.2*pow(1.043, percentage) - 1.2 + 0.2 * percentage;

    percentage = -percentage;
    
  }
  controller.setText(1,1,std::to_string(percentage));
  return percentage*4;
}