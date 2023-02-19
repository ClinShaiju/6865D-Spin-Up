#include "main.h"

TwoEncoderOdom::TwoEncoderOdom(double sideOff, double backOff, double trackingDiameter, double driveDiameter, std::vector<pros::ADIEncoder>& encList, std::vector<pros::IMU>& ImuList) {
    //Reset global positions
    globalHeading = 0;
    globalX = 0; 
    globalY = 0;
}

void TwoEncoderOdom::updateState() {

    //Update encoder values
    currentEncoderS = encoderList[0].get_value();
    currentEncoderB = encoderList[1].get_value();

    //Find change in distance travelled of the encoders
    double deltaS = trackingWheelCircumference * ((currentEncoderS - prevEncoderS) / 360);
    double deltaB = trackingWheelCircumference * ((currentEncoderB - prevEncoderB) / 360);

    //Update previous encoder values
    prevEncoderS = currentEncoderS;
    prevEncoderB = currentEncoderB;

    //Update global heading
    globalHeading = inertialList[0].get_heading();

    //resetValues();
}

double TwoEncoderOdom::getHeading() {
    return globalHeading;
}

std::vector<pros::ADIEncoder> TwoEncoderOdom::returnEncoders() {
    return encoderList;
}


