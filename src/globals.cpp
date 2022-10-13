#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/impl/device/controller.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"

/*GLOBAL VARS*/
bool modKey = false;

/*DRIVE MEASUREMENTS*/
//Drive
const QLength trackWidth = 40_cm;
const QLength wheelDiameter = 12.9590697_in;
//Odom
const QLength odomTrackWidth = 0_in;
const QLength backOdomDist = 0_in;

/*PORTS*/
//Drive
const int backLeftPort = 1;
const int backRightPort = 2;
const int frontRightPort = 3;
const int frontLeftPort = 4;
//Flywheel
const int flyBackPort = 5;
const int flyFrontPort = 6;
//Indexer
const int indexerPort = 7;


/*SETUP*/
//Drivetrain
Motor backLeft = Motor(backLeftPort, false, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);
Motor backRight = Motor(backRightPort, true, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);
Motor frontLeft = Motor(frontLeftPort, false, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);
Motor frontRight = Motor(frontRightPort, true, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);

MotorGroup leftDrive = {backLeft, frontLeft};
MotorGroup rightDrive = {backRight, frontRight};

std::shared_ptr<ChassisController> drive = ChassisControllerBuilder()
    .withMotors(leftDrive, rightDrive)
    .withDimensions(AbstractMotor::gearset::green, {{wheelDiameter, trackWidth}, imev5GreenTPR})
    .withSensors(
        ADIEncoder{'A', 'B'},
        ADIEncoder{'C', 'D', true},
        ADIEncoder{'E', 'F'}
    )
    .withOdometry({{2.75_in, odomTrackWidth, backOdomDist, 2.75_in}, quadEncoderTPR})
    .buildOdometry();

//Flywheel
Motor flyBack = Motor(flyBackPort, false, okapi::AbstractMotor::gearset::blue,
    okapi::AbstractMotor::encoderUnits::degrees);
Motor flyFront = Motor(flyFrontPort, true, okapi::AbstractMotor::gearset::blue,
    okapi::AbstractMotor::encoderUnits::degrees);

//Indexer
Motor indexer = Motor(indexerPort, false, okapi::AbstractMotor::gearset::blue,
    okapi::AbstractMotor::encoderUnits::degrees);

/*GLOBAL FUNCTIONS*/
void isModKey() {
    modKey = controller.getDigital(ControllerDigital::R2);
}