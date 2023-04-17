#pragma once
#include "main.h"

extern pros::ADIDigitalOut endgame;
extern pros::ADIDigitalOut intake;
extern pros::ADIDigitalOut cataBoost;
extern pros::ADIDigitalOut bandBoost;
extern pros::ADIDigitalOut wedges;

void eg();
void actuateIntake();
void actuateBoost();
void releaseBoost();
void actuateWedges();
