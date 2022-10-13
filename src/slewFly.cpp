#include "main.h"

bool flyPressed = false;
bool toggle = false;
const int flyRPM = 420;

void flyToggle() {
    //Hold flywheel
    if (controller.getDigital(ControllerDigital::left)) {
        if (!flyPressed) {
            flyBack.moveVelocity(flyRPM);
            flyFront.moveVelocity(flyRPM);
            flyPressed = true;
        }   
    }
    else {
        flyFront.moveVoltage(0);
        flyBack.moveVoltage(0);
        flyPressed = false;
    }

    /*Test flywheel speeds*/
    if (controller.getDigital(ControllerDigital::left)) flyRPM = 600;
    if (controller.getDigital(ControllerDigital::up)) flyRPM = 500;
    if (controller.getDigital(ControllerDigital::right)) flyRPM = 420;

}

/*
void slew(int vel, int time) {
    while (currentSlew < vel) {
        flyBack.moveVelocity(currentSlew);
        flyFront.moveVelocity(currentSlew);

        currentSlew += vel / (time * 10);

        pros::delay(100);
    }
}*/