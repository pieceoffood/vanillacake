#include "main.h"
#include "cmath"
#include "config.hpp"

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
int automode=100;
int speed =100;
int distance;

void driveRelative(float distance, int speed) {
  float startpoint=leftfront.get_position();
  leftfront.move_relative  (distance, speed);
  leftback.move_relative   (distance, speed);
  rightfront.move_relative (distance, speed);
  rightback.move_relative  (distance, speed);
  while (fabs(leftfront.get_position()-startpoint)<=fabs(distance)) {
    pros::delay(20);
  }

}
void autonomous()
{
  ballintake.set_encoder_units (pros::E_MOTOR_ENCODER_COUNTS);
  catapult.set_encoder_units   (pros::E_MOTOR_ENCODER_COUNTS);
  int blueside ;
  int backside;
  automode = blue.get_value() + back.get_value()*2;

  pros::lcd::initialize();
  pros::lcd::print(2, "blue: %d\n", blue.get_value());
  pros::lcd::print(3, "back: %d\n", back.get_value());
  pros::lcd::print(4, "automode: %d\n", automode);
  int side;
  if (blueside) {
    side = -1;
  } else {
    side = 1;
  }
  // 0 red front
  // 1 blue front
  // 2 red back
  // 3 blue back
  switch (automode) {
    case 0 : { //redfront
      master.print(0, 1, "redfront:  %d", automode);
      driveRelative(-2600 ,100); // move back a little to hit the flag


      pros::delay (100);
      driveRelative(4350 ,100); // move back a little to hit the flag
      pros::delay (3000);
      break;

    }

    case 1 : { //bluefront
      master.print(0, 1, "bluefront: %d", automode);
      leftfront.tare_position ( );
			rightfront.tare_position ( );
      distance=725;
      speed=50;
      leftfront.move_relative  (distance, speed);
      leftback.move_relative   (distance, speed);
      rightfront.move_relative (-distance, speed);
      rightback.move_relative  (-distance, speed);
      pros::delay(2000);
      pros::lcd::print(2, "left position: %f\n", leftfront.get_position());
  		pros::lcd::print(3, "right position: %f\n", rightfront.get_position());
      break;
    }
    case 2 : { //redback
      master.print(0, 1, "redback:   %d", automode);

      driveRelative(-2400 ,100);
      pros::delay(500);

      ballintake.move(200);
      pros::delay(1500);
      ballintake.move(0);

      distance = (5*900)/(4*M_PI); // moves forward
      leftfront.move_relative  (distance, 150);
      leftback.move_relative   (distance, 150);
      rightfront.move_relative (distance, 150);
      rightback.move_relative  (distance, 150);
      pros::delay(1000);

      distance = 760*side; // turn 90 degree left

      leftfront.move_relative  (-distance, 100);
      leftback.move_relative   (-distance, 100);
      rightfront.move_relative (distance, 100);
      rightback.move_relative  (distance, 100);

      pros::delay (1500);

      distance = -(40*900)/(4*M_PI); // move back onto the platform

      leftfront.move_relative  (distance, 150);
      leftback.move_relative   (distance, 150);
      rightfront.move_relative (distance, 150);
      rightback.move_relative  (distance, 150);

      pros::delay (2000);
      break;
    }
    case 3 : {
      master.print(0, 1, "blueback:  %d", automode);
      // some automode code here
      break;
      }
    default : {
      break;
    }

  }
  master.clear();
}
