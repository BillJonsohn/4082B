#include "main.h"
#include "pros/adi.hpp"

pros::ADIDigitalOut endgame('G');
pros::ADIDigitalOut intake('D');
pros::ADIDigitalOut cataBoost('F');
pros::ADIDigitalOut bandBoost('H');
pros::ADIDigitalOut wedges('C');
bool intakeUp = false;
bool cataBoostActive = false;
bool wedgesUp = false;
bool bandCata = false;

void eg(){
    endgame.set_value(true);
}

void actuateIntake(){
    intakeUp = !intakeUp;
    intake.set_value(intakeUp);
}

void actuateBoost(){
    cataBoostActive = !cataBoostActive;
    cataBoost.set_value(cataBoostActive);
}

void releaseBoost(){
    bandCata = true;
    bandBoost.set_value(bandCata);
}

void actuateWedges(){
    wedgesUp = !wedgesUp;
    wedges.set_value(wedgesUp);
}
