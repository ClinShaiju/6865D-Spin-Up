#pragma once

#include "main.h"

class TwoEncoderOdom {
    private:
        static constexpr double PI = 3.14159265358979323846;

        //Global posiitons
        double globalHeading;
        double globalX;
        double globalY;

        //Sensors
        std::vector<pros::ADIEncoder> encoderList;
        std::vector<pros::IMU> inertialList;

        //Distance from tracking center
        double sideOdomOffset;
        double backOdomOffset;

        //Circumference
        double trackingWheelCircumference;
        double driveWheelCircumference;

        //Value of encoders in current state
        double currentEncoderS;
        double currentEncoderB;

        //Value of encoders in previous state
        double prevEncoderB;
        double prevEncoderS;

        //Updates global posiitons

    public:
        TwoEncoderOdom(double, double, double, double, std::vector<pros::ADIEncoder>&, std::vector<pros::IMU>&);
        void updateState();
        double getHeading();
        std::vector<pros::ADIEncoder> returnEncoders();
};