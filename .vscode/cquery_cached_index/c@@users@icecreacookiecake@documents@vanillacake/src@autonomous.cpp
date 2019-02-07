#include "main.h"
#include "cmath"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
  pros::Controller master (pros::E_CONTROLLER_MASTER);
  pros::Motor leftfront  (1, pros::E_MOTOR_GEARSET_18, false);
  pros::Motor leftback   (2, pros::E_MOTOR_GEARSET_18, true);
  pros::Motor rightfront (3, pros::E_MOTOR_GEARSET_18, true);
  pros::Motor rightback  (4, pros::E_MOTOR_GEARSET_18, false);
  pros::Motor liftleft   (11, pros::E_MOTOR_GEARSET_18, false);
  pros::Motor liftright  (12, pros::E_MOTOR_GEARSET_18, true);
  pros::Motor flipper    (6, pros::E_MOTOR_GEARSET_18, false);

  leftfront.set_encoder_units  (pros::E_MOTOR_ENCODER_COUNTS);
  leftback.set_encoder_units   (pros::E_MOTOR_ENCODER_COUNTS);
  rightfront.set_encoder_units (pros::E_MOTOR_ENCODER_COUNTS);
  rightback.set_encoder_units  (pros::E_MOTOR_ENCODER_COUNTS);
  liftleft.set_brake_mode      (pros::E_MOTOR_BRAKE_BRAKE);
  liftright.set_brake_mode     (pros::E_MOTOR_BRAKE_BRAKE);
  flipper.set_brake_mode       (pros::E_MOTOR_BRAKE_HOLD);
/*
  int distance;
  distance = -(45*900)/(4*M_PI);// move 45 inch back
  // the measurement is not accurate and you may need to fine tune

  leftfront.move_relative  (distance, 200);
  leftback.move_relative   (distance, 200);
  rightfront.move_relative (distance, 200);
  rightback.move_relative  (distance, 200);

pros::delay(2000); // wait 2 sec until finished move.
// need to adjust depend on distance

distance = (60*900)/(4*M_PI); // move 60 inch

leftfront.move_relative  (distance, 200);
leftback.move_relative   (distance, 200);
rightfront.move_relative (distance, 200);
rightback.move_relative  (distance, 200);

pros::delay (3500);

distance = 790; // turn 90 degree

leftfront.move_relative  (-distance, 200);
leftback.move_relative   (-distance, 200);
rightfront.move_relative (distance, 200);
rightback.move_relative  (distance, 200);

pros::delay (500);// wait enghout time until finished move.
// need to adjust depend on distance

distance = -(65*900)/(4*M_PI); // move 65 inch back

leftfront.move_relative  (distance, 200);
leftback.move_relative   (distance, 200);
rightfront.move_relative (distance, 200);
rightback.move_relative  (distance, 200);

pros::delay (2500);
*/
}
