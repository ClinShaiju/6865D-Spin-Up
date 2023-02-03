#pragma once
#include "main.h"

void flyPID();
void flyToggle();
double getEmaRPM();
double getVelocity();

extern double motorPower;
extern double currentRPM;
extern double targetRPM;