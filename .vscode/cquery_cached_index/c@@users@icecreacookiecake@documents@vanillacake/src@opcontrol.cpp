#include "main.h"

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
void opcontrol() {

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

	while(true){
		int left  = master.get_analog (ANALOG_LEFT_Y);
		int right = master.get_analog (ANALOG_RIGHT_Y);

			leftfront.move_velocity (left);
			leftback.move_velocity  (left);
			rightfront.move_velocity (right);
			rightback.move_velocity  (right);

		if (master.get_digital (DIGITAL_R1))
		{
			liftleft.move_velocity  (127);
			liftright.move_velocity (127);
    }

		else if (master.get_digital (DIGITAL_R2))
		{
			liftleft.move_velocity  (-127);
			liftright.move_velocity (-127);
    }

		else
		{
			liftleft.move_velocity  (0);
			liftright.move_velocity (0);
    }

		if (master.get_digital (DIGITAL_L1))
		{
			flipper.move_velocity(100);
		}

		else if (master.get_digital (DIGITAL_L2))
		{
			flipper.move_velocity(-100);
		}

		else
		{
			flipper.move_velocity(0);
		}

		pros::delay(3);
	}

}
