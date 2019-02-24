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
void basemovement(double distance, int speed)
{
  double ticks=(distance*900)/(4*M_PI);
  leftfront.move_relative  (ticks, speed);
  leftback.move_relative   (ticks, speed);
  rightfront.move_relative (ticks, speed);
  rightback.move_relative  (ticks, speed);
}
void baseturn(int left, int speed)
{
  double ticks=735*left;
  leftfront.move_relative  (ticks, speed);
  leftback.move_relative   (ticks, speed);
  rightfront.move_relative (-ticks, speed);
  rightback.move_relative  (-ticks, speed);
}

void moving (double distance, int speed)
{
  double start = leftfront.get_position();
  double ticks = (distance*900)/(4*M_PI);
  double target = leftfront.get_position() + ticks;
  leftfront.move_relative  (ticks, speed);
  leftback.move_relative   (ticks, speed);
  rightfront.move_relative (ticks, speed);
  rightback.move_relative  (ticks, speed);

  while (fabs (ticks) - fabs (leftfront.get_position() - start) > 0) {
    pros::delay(3);
  }
  pros::delay(50);
}
void turning (int left, int speed)
{
  double start = leftfront.get_position();
  double ticks = 735*left;
  double target = leftfront.get_position() + ticks;
  leftfront.move_relative  (-ticks, speed);
  leftback.move_relative   (-ticks, speed);
  rightfront.move_relative (ticks, speed);
  rightback.move_relative  (ticks, speed);

  while (fabs (ticks) - fabs (leftfront.get_position() - start)> 0) {
    pros::delay(3);
  }
  pros::delay(50);
}

void autonomous()
{
  redblue side;
  frontback isfront;

  // 1 red front
  // 2 blue front
  // 3 red back
  // 4 blue back
  // 5 skill program 1
  // 6 skill program 2
  switch(automode) // assign value to side and isfront based on the auto selection button pressed
  {
    case 1:
    {
      side = red;
      isfront = front;
      break;
    }
    case 2:
    {
      side = blue;
      isfront = front;
      break;
    }
    case 3:
    {
      side = red;
      isfront = back;
      break;
    }
    case 4:
    {
      side = blue;
      isfront = back;
      break;
    }
    default:
    {
      break;
    }
  }

  if (automode>=1 && automode <=4 ) {
    switch (isfront) {
      case front : { //front
        if (side==blue) {
          master.print   (0, 0, "bluefront: %d", automode, blue, isfront);
        } else {
           master.print  (0, 0, "redfront:  %d", automode);
        }

        moving (-45,100); // move back to hit the low flag
        //pros::delay(10);

        moving (70, 100); //move forwards
        //pros::delay(10);

        turning   (-1*side, 100); //turn left
        //pros::delay (10);

        moving (-62, 150); //park on the platform

        break;

      }

      case back : { //back
        if (side==red) {

          master.print(0, 0, "blueback:  %d", automode);
        } else {
          master.print(0, 0, "redback:   %d", automode);
        }

        moving (-35, 100); //move forwards

        ballintake.move (200); //get ball under cap
        pros::delay(1000);
        ballintake.move (0);

        moving (5, 50); //forwards

        turning     (1*side, 50); //turn right
        moving     (-42, 150); //park on the platoform

        break;
      }
      default : {
        break;
      }

    }
  } else  if (automode == 5)
  {
    //skill 1 program
    master.clear();
    master.print(0, 0, "automode:  %d%d%d", automode, blue, isfront);
    moving (36, 100);
    claw.move_absolute(750,200); // close claw
    pros::delay(500);
    lift.move_absolute(150, 200);// lift up a little
    moving (-36, 100);
    lift.move_absolute(0, 100);// lift down
    pros::delay(500);
    claw.move_absolute(0,200); // claw open
    pros::delay(500);
    lift.move_absolute(450, 200);
    pros::delay(500);
    lift.move_absolute(0, 200);
    pros::delay(500);
  } else if (automode ==6 )
  {
    //skill 2 program
  }
  master.clear();
}
