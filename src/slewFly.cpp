#include "main.h"

bool leftIsPressed = false;
bool toggle = false;
int currentSlew = 0;

void flyToggle() {
    if (controller.getDigital(ControllerDigital::left)) {
        if (!leftIsPressed) {
            if (!toggle) {
                slew(420, 2);
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
}

void slew(int vel, int time) {
    while (currentSlew < vel) {
        flyBack.moveVelocity(currentSlew);
        flyFront.moveVelocity(currentSlew);

        currentSlew += vel / (time * 10);

        pros::delay(100);
    }
}