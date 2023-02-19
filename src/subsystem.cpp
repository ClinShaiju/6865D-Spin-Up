#include "main.h"
bool L2Pressed = false;
bool L1Pressed = false;
bool endgameButtonPressed = false;
bool autoaimButtonPressed = false;

void index() {
    //Check if modkey is active for long shoot
    if (!modKey) {
         if (controller.getDigital(ControllerDigital::L2) && !L2Pressed) {
            indexer.moveRelative(360, 200);
            L2Pressed = true;
        }
        else if (!controller.getDigital(ControllerDigital::L2)) {
            L2Pressed = false;
        }
    }
    /*
    //Else run rapid shoot 
    else {
        //Rapid fire 3 discs
        if (controller.getDigital(ControllerDigital::L2) && !L2Pressed) {
            indexer.moveRelative(360 * 3, 600);
            L2Pressed = true;
        }
        else {
            L2Pressed = false;
        }
        //Shoot single disc
        if (controller.getDigital(ControllerDigital::L1) && !L1Pressed) {
            indexer.moveRelative(360, 600);
            L1Pressed = true;
        }
        else {
            L1Pressed = false;
        }
    }*/
} 

void runIntake() {
    if (controller.getDigital(ControllerDigital::L1) && !L1Pressed) {
        if (!modKey) {
            intake.moveVelocity(600);
        }
        else {
            intake.moveVelocity(-600);
        }
        L1Pressed = true;
    }
    else if (!controller.getDigital(ControllerDigital::L1)){
            intake.moveVelocity(0);
            L1Pressed = false;
    }
}

void endgameExpansion(QTime millis) {
	double sec = millis.convert(okapi::second);

    //if (sec > 95) {
        if (controller.getDigital(ControllerDigital::B) && !endgameButtonPressed) {
            pistonLeft.set_value(true); 
            endgameButtonPressed = true;
        }
        else if (!controller.getDigital(ControllerDigital::B)){
            endgameButtonPressed = false;
        }
    //}


}

void autoAim(alliancePosition alliancePos) {
    drive->setMaxVelocity(100);

    //Coordinates of high goal
    QLength goalCoordX = 0_ft;
    QLength goalCoordY = 0_ft;

    //Assign point to aim towards
    if (alliancePos == roller) {
        goalCoordX = 2150_mm;
        goalCoordY = 100_mm;
    } else if (alliancePos == middle) {
        goalCoordX = 950_mm;
        goalCoordY = 2850_mm;
    }

    //Aim toward goal if button is pressed
    if (controller.getDigital(ControllerDigital::A) && !autoaimButtonPressed) {
        drive->turnToPoint({goalCoordX, goalCoordY});
        autoaimButtonPressed = true;
    }
    else if (!controller.getDigital(ControllerDigital::A)){
        autoaimButtonPressed = false;
    }
    drive->setMaxVelocity(200);
}