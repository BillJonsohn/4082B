#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 6.4, 0.006, 47, 12);//5, 0.003, 35, 15
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 90, 2, 500, 5, 500, 500);//100, 3, 500, 7, 500, 500
  chassis.set_exit_condition(chassis.swing_exit, 80, 4, 500, 7, 500, 500);//100, 3, 500, 7, 500, 500
  chassis.set_exit_condition(chassis.drive_exit, 20, 60, 300, 150, 500, 500);//80, 50, 300, 150, 500, 500
}



void awp() {

  //chassis.set_drive_pid(48, 80, true);
  //chassis.wait_drive();

  chassis.set_turn_pid(180, 110);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 127);
  chassis.wait_drive();

  chassis.set_turn_pid(0, 127);
  chassis.wait_drive();








}

void left_auton() {

}

void right_auton() {

}

void left_special() {

}

void  right_special() {
  
}

