#include "main.h"

bool flyPressed = false;
bool flyToggle = false;
int flyRPM = 420;

void flyToggle() {
    bool flyButton = controller.getDigital(ControllerDigital::R1);
    //If modkey, toggle flywheel
    if (modKey) {
        if (flyButton) {
            if (!flyPressed) {
                if (!flyToggle) {
                    flyBack.moveVelocity(flyRPM);
                    flyFront.moveVelocity(flyRPM);
                    flyToggle = true;
                }
                else {
                    flyBack.moveVoltage(0);
                    flyFront.moveVoltage(0);
                    flyToggle = false;
                }
                flyPressed = true;
            }
        }
        else {
            flyPressed = false;
        }
    }
    //If modkey off, hold for flywheel
    else {
        if (flyToggle) {
            if (flyButton) flyToggle = false;
        }
        else if (flyButton) {
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