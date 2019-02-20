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
int  automode=1;
double speed =100.00;
double distance;

void moving (double distance, int speed)
{
  double ticks = (distance*900)/(4*M_PI);
  double startpoint = leftfront.get_position();
  double error=fabs(ticks) - fabs(leftfront.get_position()-startpoint);
  leftfront.move_relative  (ticks, speed);
  leftback.move_relative   (ticks, speed);
  rightfront.move_relative (ticks, speed);
  rightback.move_relative  (ticks, speed);

  while ( error>0 ) {
    pros::delay(3);
  }
  pros::delay(10);
}
void turning (int left, int speed)
{
  double ticks = 735*left;
  double startpoint = leftfront.get_position();
  double error=fabs(ticks) - fabs(leftfront.get_position()-startpoint);
  leftfront.move_relative  (-ticks, speed);
  leftback.move_relative   (-ticks, speed);
  rightfront.move_relative (ticks, speed);
  rightback.move_relative  (ticks, speed);

  while ( error>0 ) {
    pros::delay(3);
  }
  pros::delay(10);
}

void autonomous()
{

  redblue side; // make turn in opposite when on blueside
  frontback isfront;
  switch(automode)
  {
    case 1:
    {
      side=red;
        isfront=front;
      break;
    }
    case 2:
    {
      side=blue;
      isfront=back;
      break;
    }
    case 3:
    {
      side=red;
      isfront=front;
      break;
    }
    case 4:
    {
      side=blue;
      isfront=back;
      break;
    }
    default:
    {
      side=red;
      isfront=front;
      break;
    }
  }

  // 1 red front
  // 3 blue front
  // 2 red back
  // 4 blue back
  switch (isfront) {
    case front : { //front
      if (side==blue) {
        master.print   (0, 0, "bluefront: %d", automode);
      } else {
         master.print  (0, 0, "redfront:  %d", automode);
      }

      moving (-45, 100); // move back to hit the low flag

      moving (70, 100); //move forwards

      turning   (1*side, 100); //turn left
      pros::delay (1000);

      moving (-62, 100); //park on the platform

      break;

    }

    case back : { //back
      if (side==blue) {
        master.print(0, 0, "blueback:  %d", automode);
      } else {
        master.print(0, 0, "redback:   %d", automode);
      }


      moving (-35, 100); //move forwards

      ballintake.move (200); //get ball under cap
      pros::delay  (1500);
      ballintake.move (0);

      moving (5, 100); //forwards

      turning     (-1*side, 100); //turn right


      moving     (-42, 100);

      break;
    }
    default : {
      break;
    }

  }
  master.clear();
}
