#include "main.h"
#include "config.hpp"


pros::Controller master  (pros::E_CONTROLLER_MASTER);
pros::Controller partner (pros::E_CONTROLLER_PARTNER);
pros::Motor leftfront  (7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftback   (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightfront (9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightback  (10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lift       (20, pros::E_MOTOR_GEARSET_18, false);
pros::Motor claw       (12, pros::E_MOTOR_GEARSET_18, true);
pros::Motor ballintake (19, pros::E_MOTOR_GEARSET_18, false);
pros::Motor catapult   (13, pros::E_MOTOR_GEARSET_36, false);
pros::ADIDigitalIn limitswitch  (1);
pros::ADIAnalogIn potentiameter (2);
pros::ADIAnalogIn ballshooterp  (3);
pros::ADIDigitalIn limitswitchball(4);
pros::ADIDigitalIn blue (7); // use jumper to select side blue=1 and red=0
pros::ADIDigitalIn back (8); // use jumper to select front=0 and back=1




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  lift.set_brake_mode          (pros::E_MOTOR_BRAKE_HOLD);
  claw.set_brake_mode          (pros::E_MOTOR_BRAKE_HOLD);
  catapult.set_brake_mode      (pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
