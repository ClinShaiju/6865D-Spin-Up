#pragma once

#include "main.h"

class ThreeEncoderOdom {
    private:
        static constexpr double PI = 3.14159265358979323846;

        double currentHeading;

        std::vector<pros::ADIEncoder> encoderList;

        double leftOdomOffset;
        double rightOdomOffset;
        double backOdomOffset;
        double trackingWheelCircumference;
        double driveWheelCircumference;

        double currentEncoderM;
        double currentEncoderL;
        double currentEncoderR;

        double prevEncoderM;
        double prevEncoderL;
        double prevEncoderR;

        //void updateValues();
        void resetValues();

    public:
        ThreeEncoderOdom(double, double, double, double, std::vector<pros::ADIEncoder>&);
        void updateState();
        double getHeading();
        std::vector<pros::ADIEncoder> returnEncoders();
};