#include "main.h"
/*GLOBAL VARS*/
extern bool modKey;

/*DRIVE MEASUREMENTS*/
//Drive
const QLength trackWidth;
const QLength wheelDiameter;
//Odom
const QLength odomTrackWidth;
const QLength backOdomDist;

/*PORTS*/
//Drive
const int backLeftPort;
const int backRightPort;
const int frontRightPort;
const int frontLeftPort;
//Flywheel
const int flyBackPort;
const int flyFrontPort;
//Indexer
const int indexerPort;

/*SETUP*/
extern Controller controller;

Motor backLeft;
Motor backRight;
Motor frontLeft;
Motor frontRight;

MotorGroup leftDrive;
MotorGroup rightDrive;

extern std::shared_ptr<ChassisController> drive;

extern Motor flyBack;
extern Motor flyFront;

extern Motor indexer;
