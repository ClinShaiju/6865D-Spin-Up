#include "main.h"

ThreeEncoderOdom::ThreeEncoderOdom(double sideOff, double backOff, double trackingDiameter, double driveDiameter, std::vector<pros::ADIEncoder>& encList) {
    currentHeading = 0;
    
    currentEncoderL = 0;
    currentEncoderR = 0;
    currentEncoderM = 0;

    prevEncoderL = 0;
    prevEncoderR = 0;
    prevEncoderM = 0;
    
    encoderList = encList;
    
    leftOdomOffset = sideOff;
    rightOdomOffset = sideOff;
    backOdomOffset = backOff;
    trackingWheelCircumference = trackingDiameter * PI;
    driveWheelCircumference = driveDiameter * PI;

    // leftDrive = lDrive;
    // rightDrive = rDrive;

    //resetValues();
}

void ThreeEncoderOdom::resetValues() {
    encoderList[0].reset();
    encoderList[1].reset();
    encoderList[2].reset();
}
/*
void ThreeEncoderOdom::updateValues() {
    prevEncoderL = currentEncoderL;
    prevEncoderR = currentEncoderR;
    prevEncoderM = currentEncoderM;

    currentEncoderL = encoderList[0].get_value();
    currentEncoderR = encoderList[1].get_value(); 
    currentEncoderM = encoderList[2].get_value();
}*/

void ThreeEncoderOdom::updateState() {

    //Update encoder values
    currentEncoderL = encoderList[0].get_value();
    currentEncoderR = encoderList[1].get_value(); 
    currentEncoderM = encoderList[2].get_value();
    //std::cout << currentEncoderL << std::endl;

    //Find change in distance travelled of the encoders
    double deltaL = trackingWheelCircumference * ((currentEncoderL - prevEncoderL) / 360);
    double deltaR = trackingWheelCircumference * ((currentEncoderR - prevEncoderR) / 360);
    double deltaM = trackingWheelCircumference * ((currentEncoderM - prevEncoderM) / 360);

    //Update previous encoder values
    prevEncoderL = currentEncoderL;
    prevEncoderR = currentEncoderR;
    prevEncoderM = currentEncoderM;

    //Update global heading
    currentHeading += (deltaL - deltaR) / (rightOdomOffset + leftOdomOffset) * (PI / 180);

    //resetValues();
}

double ThreeEncoderOdom::getHeading() {
    return currentHeading;
}

std::vector<pros::ADIEncoder> ThreeEncoderOdom::returnEncoders() {
    return encoderList;
}


