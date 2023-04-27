#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"

pros::Motor lMotor (12, true);
pros::Motor rMotor (20);
pros::ADIDigitalIn cataLimit1('E');
pros::ADIDigitalIn cataLimit2('B');

cata_states state = HOLD;

int intakeSpeed = 0;

void cataShare(){
    while(true){
        if(state == PRIME){
            lMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            rMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            if(cataLimit2.get_value()){

                if(cataLimit1.get_value()){
                //wait(13);
                lMotor.move(0);
                rMotor.move(0);
                wait(50);
                state = HOLD;
                }

                else if(!bandCata){
                    lMotor.move(80);
                    rMotor.move(80);
                }
                else{
                    lMotor.move(102);
                    rMotor.move(102);
                }
            }
            else{
                lMotor.move(127);
                rMotor.move(127);
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
            lMotor.move(110);
            rMotor.move(110);
            if(!cataLimit2.get_value()){
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
    intakeSpeed = -127;
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

void wait(int msec){
    pros::delay(msec);
}