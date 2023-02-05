#include "main.h"
#include "flywheel/flywheelImplementation.hpp"
#include "odometry/twoEncoderOdom.hpp"
/*GLOBAL VARS*/
extern bool modKey;
extern int globalFlywheelRPM;

//Alliance color selector
enum alliancePosition {roller, middle};
enum allianceColor {red, blue};
extern alliancePosition currentAlliancePosition;

/*SETUP*/
extern Controller controller;

extern std::shared_ptr<OdomChassisController> drive;
extern TwoEncoderOdom driveOdom;
extern std::vector<pros::ADIEncoder> encoderList;

extern sylib::Motor flyFront;
extern sylib::Motor flyBack;

extern Motor indexer;

extern Motor intake;

extern pros::ADIDigitalOut pistonLeft;

/*GLOBAL FUNCTIONS*/
void isModKey();

void startGrafana();

double exponential(double);