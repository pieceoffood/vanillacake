#include "main.h"
#include "cmath"
#include "config.hpp"
#include "userFn.hpp"

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
 typedef struct {
   int speed;
 } my_task_arg;

 void my_task_fn(void* argument) {
   // Following two lines get the members of the my_task_arg struct
   int speed = ((my_task_arg*)argument)->speed;
   while (limitswitchball.get_value()==1) {
     catapult.move_velocity  (100);
     catapult.tare_position ( );
     pros::delay(3);
   }
   catapult.move_absolute(2090, 100);
 }

 void autonomous()
 {
   my_task_arg* argument = new my_task_arg();
   argument->speed = 100;
   pros::Task my_task(my_task_fn, argument);

   redblue side=red;
   frontback isfront=front;


 }
