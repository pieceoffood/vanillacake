#include "main.h"
#include "config.hpp"
/*
cd (change directory)
cd .. (go up one level)
prosv5 make clean (clean everything)
prosv5 build-compile-commands (compile the code)
prosv5 upload --slot 5 (upload the program to V5 slot 5)
prosv5 v5 rm-all
prosv5 v5 rm-file slot_4.bin --erase-all
*/

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void shootball() {
  //catapult
  //
  if (limitswitchball.get_value()==1) {
    catapult.tare_position ( );
  }
  while (catapult.get_position()<2100 )
  {
    catapult.move_velocity  (100);
    pros::delay(10);
  }
  catapult.move_velocity  (0);
  pros::delay(500);
  catapult.move_velocity  (100);
  pros::delay(100);
  catapult.move_velocity(0);
  }



void opcontrol() {

  pros::lcd::initialize();
	while(true){
		int left  = master.get_analog (ANALOG_LEFT_Y);
		int right = master.get_analog (ANALOG_RIGHT_X);

		//print screen
		pros::lcd::print(0, "limitswitch: %d, life position: %8.1f\n", limitswitch.get_value(), lift.get_position());
		pros::lcd::print(1, "potentiameter: %d\n", potentiameter.get_value());
		pros::lcd::print(2, "left: %8.1f, right %8.1f\n", leftfront.get_position(), rightfront.get_position());
		pros::lcd::print(3, "catapult: %8.1f, reset %d\n", catapult.get_position(), limitswitchball.get_value());
		pros::lcd::print(4, "claw: %8.1f\n", claw.get_position());

    // chasis arcade drive
			leftfront.move  (left - right);
			leftback.move   (left - right);
			rightfront.move (left + right);
			rightback.move  (left + right);

    if ( master.get_digital(DIGITAL_DOWN))  {
			leftfront.tare_position ( );
			rightfront.tare_position ( );
		}


    //lift
    if (limitswitch.get_value()==1) {
      lift.tare_position();  // reset lift encoude zero
    }
		if (master.get_digital (DIGITAL_R1) && lift.get_position()<3056) // limit lift up position
		{
			lift.move_velocity  (200);
    }		else if (master.get_digital (DIGITAL_R2) && limitswitch.get_value()==0) // stop the lift at lowest
		{
			lift.move_velocity  (-150);
    }		else
		{
			lift.move_velocity  (0);
		}

		// claw only activat during 1700- 2600
		// There is overshoot issue and this range 1850 - 2350 is right for coarse stop
		if (master.get_digital (DIGITAL_L1) && potentiameter.get_value()>1700)
		{

			claw.move_velocity  (-100); // up/

    }		else if (master.get_digital (DIGITAL_L2) && potentiameter.get_value()<2600)
		{
			claw.move_velocity  (100); // down
    }		else
		{
			claw.move_velocity  (0);
    }

		//ballintake
		if (master.get_digital (DIGITAL_A)) 	{
			ballintake.move_velocity  (200);
    }		else
		if (master.get_digital (DIGITAL_Y))		{
			ballintake.move_velocity  (-200);
		}	else
		{
			ballintake.move_velocity  (0);
    }

		//catapult
    if (limitswitchball.get_value()==1) {
      catapult.tare_position ( );
    }
		if (master.get_digital (DIGITAL_X))
		{
			shootball();
    }		else
		{
			catapult.move_velocity  (0);
    }
	pros::delay (10);
	}
}
