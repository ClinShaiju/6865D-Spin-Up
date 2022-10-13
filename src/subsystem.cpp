#include "main.h"
bool L2Pressed = false;
bool L1Pressed = false;

void index() {
    //Check if modkey is active for long shoot
    if (modKey) {
         if (controller.getDigital(ControllerDigital::L2) && !L2Pressed) {
            indexer.moveRelative(360, 200);
            L2Pressed = true;
        }
        else {
            L2Pressed = false;
        }
    }
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
    }
} 