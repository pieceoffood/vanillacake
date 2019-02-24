#include "main.h"
#include "config.hpp"
#include <iomanip>
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
   if (catapult.get_position()>1800 && catapult.get_position()<2100 )
   {
     catapult.move_velocity  (15);
   }		else
   if ( catapult.get_position()>=2100 )
   {
     catapult.move_velocity  (50);
   }		else
   {
     catapult.move_velocity  (100);
   }

 }
void opcontrol() {
  //pros::lcd::initialize();
  std::cout << std::fixed;
  std::cout << std::setprecision(1);
  char mytext[64];


  	/*Create a screen*/
  	lv_obj_t * scr = lv_obj_create(NULL, NULL);
  	lv_scr_load(scr);                                   /*Load the screen*/

  	lv_obj_t * title = lv_label_create(lv_scr_act(), NULL);
  	lv_label_set_text(title, "Debug");
  	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);  /*Align to the top*/

  	/*Create anew style*/
  	/*
  	static lv_style_t style_txt;
  	lv_style_copy(&style_txt, &lv_style_plain);
  	style_txt.text.font = &lv_font_dejavu_20;
  	style_txt.text.letter_space = 2;
  	style_txt.text.line_space = 1;
  	style_txt.text.color = LV_COLOR_HEX(0x606060);
  	*/

  	/*Create a new label*/
  	lv_obj_t * txt = lv_label_create(lv_scr_act(), NULL);
  	//lv_obj_set_style(txt, &style_txt);                    /*Set the created style*/
  	lv_label_set_long_mode(txt, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
  	lv_label_set_recolor(txt, true);                      /*Enable re-coloring by commands in the text*/
  	lv_label_set_align(txt, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
  	lv_label_set_text(txt, "Align lines to the middle\n\n"
  	                       "#000080 Re-color# #0000ff words of# #6666ff the text#\n\n"
  	                       "If a line become too long it can be automatically broken into multiple lines");
  	lv_label_set_text(txt, NULL);
  	lv_obj_set_width(txt, 300);                           /*Set a width*/
  	lv_obj_align(txt, NULL, LV_ALIGN_CENTER, 0, 20);      /*Align to center*/

	while(true){

    master.print(1, 0, "pote: %d", potentiameter.get_value());
		master.print(2, 0, "flipper: %8.2f", claw.get_position());
		std::cout << "claw " << claw.get_position() <<"\n";
		std::cout << "lift " << lift.get_position() <<"\n";
    sprintf(mytext, "claw potentiameter: %d, claw %8.2f \n"
                    "lift: %8.2f, set zero:%d\n"
                    "catapult: %8.2f, set zero: %d\n"
                    "leftfront:%8.2f",
		       potentiameter.get_value(), claw.get_position(),
	         lift.get_position(), limitswitch.get_value(),
				   catapult.get_position(), limitswitchball.get_value(),
           leftfront.get_position());
		lv_label_set_text(txt, mytext);

		int left  = master.get_analog (ANALOG_LEFT_Y);
		int right = master.get_analog (ANALOG_RIGHT_X);

    // press DIGITAL_DOWN to reset zero
		if ( master.get_digital(DIGITAL_DOWN))  {
			leftfront.tare_position ( );
			rightfront.tare_position ( );
		}

	  	// chasis arcade
			leftfront.move  (left + right);
			leftback.move   (left + right);
			rightfront.move (left - right);
			rightback.move  (left - right);

		//lift
    if (limitswitch.get_value()==1)
    {
      lift.tare_position();
    }
		if (master.get_digital (DIGITAL_R1) && lift.get_position()<3056)
		{
      lift.get_position();
			lift.move_velocity  (200);
    }		else if (master.get_digital (DIGITAL_R2) && limitswitch.get_value()==0)
		{
			lift.move_velocity  (-150);
    }		else
		{
			lift.move_velocity  (0);
		}

		// claw only activat during 1700- 2410
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
		if (master.get_digital(DIGITAL_A)) 	{
			ballintake.move_velocity  (200);
    }		else
		if (master.get_digital (DIGITAL_Y))		{
			ballintake.move_velocity  (-200);
		}		else
		{
			ballintake.move_velocity  (0);
    }

		//catapult
    if (limitswitchball.get_value()==1) {
      catapult.tare_position ( );  // reset catapult encoder position to zero
    }
		if (partner.get_digital (DIGITAL_X))
		{
			catapult.move_relative  (1000,100);// to loading position
    }		else if (partner.get_digital(DIGITAL_DOWN))
		{
			catapult.move_velocity  (100);
    } else {
			catapult.move_velocity  (0);
		}
	pros::delay (10);
	}
}
