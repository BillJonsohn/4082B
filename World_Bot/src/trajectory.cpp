#include "main.h"

void followPath (Trajectory path){
  for(auto pt : path){
      double leftRPM = pt.leftVelocity * 200 / 6.38;
      double rightRPM = pt.rightVelocity * 200 / 6.38;
      // make motor run the motor velocity  
      chassis.left_motors[0].move_velocity(leftRPM);
      chassis.left_motors[1].move_velocity(leftRPM);
      chassis.left_motors[2].move_velocity(leftRPM);
      chassis.right_motors[0].move_velocity(rightRPM);
      chassis.right_motors[1].move_velocity(rightRPM);
      chassis.right_motors[2].move_velocity(rightRPM);

    pros::delay(10);
  }
}