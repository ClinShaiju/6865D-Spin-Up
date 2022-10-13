#include "main.h"

bool leftIsPressed = false;
bool toggle = false;
const int flyRPM = 420;

void flyToggle() {
    //Toggle flywheel
    if (controller.getDigital(ControllerDigital::left)) {
        if (!leftIsPressed) {
            if (!toggle) {
                flyBack.moveVelocity(flyRPM);
                flyFront.moveVelocity(flyRPM);
                toggle = true;
            }
            else {
                flyBack.moveVoltage(0);
                flyFront.moveVoltage(0);
                toggle = false;
            }
            leftIsPressed = true;
        }
    }
    else {
        leftIsPressed = false;
    }

    /*Test flywheel speeds*/
    if (controller.getDigital(ControllerDigital::R1)) flyRPM = 600;
    if (controller.getDigital(ControllerDigital::R2)) flyRPM = 500;
    if (controller.getDigital(ControllerDigital::L1)) flyRPM = 420;
    
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