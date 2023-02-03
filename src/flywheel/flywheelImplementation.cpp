#include "main.h"
#include "math/utils.hpp"
#include "okapi/impl/device/motor/motor.hpp"

const double kP = .71;
const double kI = 0;
const double kD = 0.25;
//const double kF = 0;

double integral = 0;


const int flywheelRatio = 7;
double motorSlew = 140;

double targetRPM = 0;
double currentRPM = 0;
double lastError = 0;
double motorPower = 0;

bool flyPressed = false;
bool flyToggled = false;

void flyPID() {
    motorPower = 0;
    
    currentRPM = (flyFront.get_velocity() + flyBack.get_velocity()) / 2.0;

    const double error = targetRPM - currentRPM;
    
    double derivative = error - lastError;

    lastError = error;

    if (error > 15) {
        motorPower = 12000;
    }
    else {
        integral += error;

        motorPower += error * kP * 10;
        motorPower += integral * kI;
        motorPower += derivative * kD * 10;
        //motorPower += 12000 * kF;
        motorPower += targetRPM * 12000 / 600 * 1.1;
    }

    

    if (motorPower > 12000)  // limit the voltage to the maximum value (12 volts)
        motorPower = 12000;
    else if (motorPower < 0)  // limit the voltage to the minimum value (-12 volts)
        motorPower = 0;
    if (targetRPM == 0) {
        motorPower = 0;
    }

    flyBack.set_voltage(motorPower);
    flyFront.set_voltage(-motorPower);

}


void flyToggle() {
    bool flyButton = controller.getDigital(ControllerDigital::R1);
    //If modkey, toggle flywheel
    if (modKey) {
        if (flyButton) {
            if (!flyPressed) {
                if (!flyToggled) {
                    integral = 0;
                    targetRPM = globalFlywheelRPM / flywheelRatio;
                    flyToggled = true;
                }
                else {
                    integral = 0;
                    targetRPM = 0;
                    flyToggled = false;
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
        if (flyToggled) {
            if (flyButton) flyToggled = false;
        }
        else if (flyButton) {
            if (!flyPressed) {
                integral = 0;
                targetRPM = globalFlywheelRPM / flywheelRatio;
                
                flyPressed = true;
            }   
        }
        else {
            integral = 0;
            targetRPM = 0;
            flyPressed = false;
        }
    }
}

double getEmaRPM() {
    double avg = (flyFront.get_velocity() + flyBack.get_velocity()) / 2.0;
    return flyBack.get_estimator_voltage();
}

double getVelocity() {

    if (flyBack.get_velocity() < 1) return 0;
    return flyBack.get_velocity();
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