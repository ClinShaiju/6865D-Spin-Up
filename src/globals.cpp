#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/impl/device/controller.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"

const QLength trackWidth = 0_in;
const QLength wheelDiameter = 0_in;

/*PORTS*/
//Drive
const int backLeftPort = 1;
const int backRightPort = 2;
const int frontRightPort = 3;
const int frontLeftPort = 4;

Controller controller;

//Drivetrain
Motor backLeft = Motor(backLeftPort, false, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);
Motor backRight = Motor(backRightPort, true, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);
Motor frontLeft = Motor(frontLeftPort, false, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);
Motor frontRight = Motor(frontRightPort, false, okapi::AbstractMotor::gearset::green,
 okapi::AbstractMotor::encoderUnits::degrees);

MotorGroup leftDrive = {backLeft, frontLeft};
MotorGroup rightDrive = {backRight, frontRight};

std::shared_ptr<ChassisController> drive = ChassisControllerBuilder()
    .withMotors(leftDrive, rightDrive)
    .withDimensions(AbstractMotor::gearset::green, {{wheelDiameter, trackWidth}, imev5GreenTPR})
    .build();
