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
int  automode=100;
double speed =100.00;
int distance;
int side;    // 1 or -1 to make turning in opposite direction



void driveRelative(double distance, int speed=100) {
  double startpoint=leftfront.get_position();
  leftfront.move_relative  (distance, speed);
  leftback.move_relative   (distance, speed);
  rightfront.move_relative (distance, speed);
  rightback.move_relative  (distance, speed);
  while (fabs(leftfront.get_position()-startpoint)<=fabs(distance)) {
    pros::delay(20);
  }
}

void driveInch(double inch, int speed=100) {
  double startpoint=leftfront.get_position();
  double distance=inch*900/4/M_PI;
  leftfront.move_relative  (distance, speed);
  leftback.move_relative   (distance, speed);
  rightfront.move_relative (distance, speed);
  rightback.move_relative  (distance, speed);
  while (fabs(leftfront.get_position()-startpoint)<=fabs(distance)) {
    pros::delay(20);
  }
}


void driveRotate(double distance=725.0, int speed=50) {
  double startpoint=leftfront.get_position();
  leftfront.move_relative  (-distance, speed);
  leftback.move_relative   (-distance, speed);
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



  pros::lcd::initialize();
  pros::lcd::print(2, "blue: %d\n", blue.get_value());
  pros::lcd::print(3, "back: %d\n", back.get_value());
  pros::lcd::print(4, "automode: %d\n", automode);

  // 0 red front for automode
  // 1 blue front
  // 2 red back
  // 3 blue back
  automode = blue.get_value() + back.get_value()*2;

  if (blue.get_value()) {
    side = -1;
  } else {
    side = 1;
  }

  switch (back.get_value()) {
    case 0 : { //front
      if (blue.get_value()) {
        master.print(0, 1, "bluefront: %d", automode);
      } else {
         master.print(0, 1, "redfront:  %d", automode);
      }
      pros::lcd::print(2, "left position: %f\n", leftfront.get_position());
      pros::lcd::print(3, "right position: %f\n", rightfront.get_position());

      driveRelative(-2600 ,100); // move back a little to hit the flag


      pros::delay (100);
      driveRelative(4350 ,100); // move forward
      pros::delay (3000);
      break;

    }

    case 1 : { //back
      if (blue.get_value()) {

        master.print(0, 1, "blueback:  %d", automode);
      } else {
        master.print(0, 1, "redback:   %d", automode);
      }
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
    default : {
      //programming skills chanllenge
      // step 1 catapult
      // step 2 back to ball
      driveInch(-36);
      pros::delay(2000);
      // step 3 take ball
      ballintake.move(200);
      pros::delay(1500);
      ballintake.move(0);
      //step 4 move
      driveInch(36);
      pros::delay(2000);
      driveRotate(725.0); // turn left face audiance
      pros::delay(1000);

      //step 5
      driveInch(-36); // drive back to flag
      pros::delay(2000);

      // step 6 move avway from left low flag
      driveInch(24); //
      pros::delay(2000);
      driveRotate(725.0); // turn left
      pros::delay(1000);

      // step 7 get cap
      driveInch(24); //
      pros::delay(2000);
      // claw
      claw.move_relative(60/180*900, 150); // claw down
      pros::delay(1000);


      // step 8
      driveInch(24); //
      pros::delay(2000);
      driveRotate(-725.0); // turn right
      pros::delay(1000);

      // step 9 drive back to middle low flag
      driveInch(-24); //
      pros::delay(2000);

      // step 10
      driveInch(24); //
      pros::delay(2000);

      // step 11 flip cap
      claw.move_relative(-60/180*900, 150); // open claw
      pros::delay(1000);
      lift.move_relative(700 ,200);// flipper the cap
      pros::delay(1000);
      lift.move_relative(-700 ,200);
      pros::delay(1000);

      // step 12 go to  cap
      driveRotate(725.0); // turn left
      pros::delay(1000);
      driveInch(24*3);
      pros::delay(8000);
      claw.move_relative(60/180*900, 150); // claw down
      pros::delay(1000);

      driveRotate(-725.0); // turn right
      pros::delay(1000);

      // 13 to right low flag
      driveInch(-24);
      pros::delay(2000);



















      break;
    }

  }
  master.clear();
}
