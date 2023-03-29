#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"

pros::Motor lMotor (12, true);
pros::Motor rMotor (20);
pros::ADIDigitalIn cataLimit1('G');
pros::ADIDigitalIn cataLimit2('B');

cata_states state = HOLD;

int intakeSpeed = 0;

void cataShare(){
    while(true){
        if(state == PRIME){
            lMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            rMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            if(!cataLimit1.get_value() || cataLimit2.get_value()){
                lMotor.move(127);
                rMotor.move(127);
            }
            else{
                state = HOLD;
            }
        }
        else if(state == HOLD){
            lMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            rMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            //pros::delay(25);
            lMotor.move(intakeSpeed);
            rMotor.move(intakeSpeed);
        }
        else if(state == SHOOT){
            lMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            rMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            lMotor.move(127);
            rMotor.move(127);
            if(!cataLimit1.get_value()){
                //pros::delay(5);
                lMotor.move(0);
                rMotor.move(0);
                pros::delay(110);
                state = PRIME;
            }
        }
        pros::delay(10);
    }


}

void cataPrime(){
    state = PRIME;
}

void cataHold(){
    state = HOLD;
}

void cataShoot(){
    state = SHOOT;
}

void cataIntake(int speed){
    intakeSpeed = -speed;
}

void cataRoller(int time){
    intakeSpeed = 127;
    pros::delay(time);
    intakeSpeed = 0;
}

void cataWait(){
    while(state == SHOOT){
        pros::delay(10);
    }
}

void cataInitialize(){
    pros::Task cataTask(cataShare);
}