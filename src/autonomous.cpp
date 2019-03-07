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

   // 1 red front
   // 2 blue front
   // 3 red back
   // 4 blue back
   // 5 redfront no park
   // 6 bluefront no park
   // 7 skills 1
   // 8 skills 2

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
     case 5:
     {
       side = red;
       isfront = front;
       break;
     }
     case 6:
     {
       side = blue;
       isfront = front;
       break;
     }
     default:
     {
       break;
     }
   }

   if (automode>=1 && automode <=4 ) {
     switch (isfront) {
       case front : { //////////////////////// front ///////////////////////////
         if (side==blue) {
           master.print   (0, 0, "bluefront: %d, %d, %d", automode, blue, isfront);
         } else {
            master.print  (0, 0, "redfront:  %d, %d, %d", automode, blue, isfront);
         }

         turnDegree       (15*side,100);

         ballLoad();
         pros::delay              (1650);

         catapult.move_relative   (500, 100); //shoot ball
         pros::delay              (100);

         turnDegree               (-15*side, 100); // turns

         moving                   (-45, 100); // move back to hit the low flag

         moving                   (70, 100); //move forwards

         turning                  (-1*side, 95); //turn left

         moving                   (62, 150); //park on the platform

         break;

       }

       case back : { /////////////////////// back //////////////////////////////
         if (side==red) {

           master.print(0, 0, "blueback:  %d, %d, %d", automode, blue, isfront);
         } else {
           master.print(0, 0, "redback:   %d, %d, %d", automode, blue, isfront);
         }

         moving          (-34, 100); //move forwards

         ballintake.move (200); // get ball under cap
         pros::delay     (1000);

         ballintake.move (0); // stops ball intake

         moving          (5, 50); // forwards

         turning         (1*side, 50); // turn left

         moving          (42, 150); // park on the platoform

         break;
       }
       default : {
         break;
       }

     }
   } else  if (automode == 5 || automode == 6)
   {
     /////////////////// redfront nopark , bluefront nopark ////////////////////

     ballLoad();
     pros::delay              (1500);

     moving                   (-33, 100); //move back

     ballintake.move          (200); //get ball under cap
     pros::delay              (1000);

     ballintake.move          (0); // stops ball intake

     moving                   (36, 100); //move back

     turning                  (-1*side, 100); //turn left

     moving                   (-16, 50);
     pros::delay              (300);

     turnDegree               (15*side, 100);

     catapult.move_relative   (1000, 100); //shoot ball at hight flag
     pros::delay              (500);

     turnDegree               (-15*side, 100); // turns
     pros::delay              (10);

     leftfront.move           (0); // stops base
     leftback.move            (0);
     rightback.move           (0);
     rightfront.move          (0);

     moving                   (-32, 100); // moves forwards and hits flag

     moving                   (10,100); // moves away from the flag
     //end


   } else if (automode ==7 )
   {

     //skill 1 program
     master.clear();
     master.print(0, 0, "automode:  %d ", automode);

     //////////////////////////////// skill 1 //////////////////////////////////




   } else if (automode == 8)
   {
     ////////////////////////// skill 2 ////////////////////////////////////////
     ballLoad();
     pros::delay            (1500);

     moving                 (-35, 100); // move back

     ballintake.move        (200); // get ball under cap
     pros::delay            (1000);

     ballintake.move        (0); // stops ball intake

     moving                 (35, 100); // move back

     turning                (-1, 100); // turn left

     moving                 (-6, 100); // move backwards
     pros::delay(100);

     turnDegree             (15, 50); // turns
     pros::delay(100);

     catapult.move_relative (1000, 100); // shoot ball
     pros::delay            (500);

     turnDegree             (-15, 100); // turn
     pros::delay            (100);

     leftfront.move         (0); // stops base
     leftback.move          (0);
     rightback.move         (0);
     rightfront.move        (0);

     moving                 (-36, 100); // moves backwards to hit flag

     moving                 (67, 100); // moves forwards away from flag to park

     turning                (-1*side, 100); // turns to the left

     moving                 (42, 200); // parks on alliance

     //end
   } else if (automode == 9)
   {


   }

   master.clear();
 }
