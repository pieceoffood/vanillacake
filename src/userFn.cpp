#include "main.h"
#include "cmath"
#include "config.hpp"

void basemovement(double distance, int speed)
{
  double ticks=(distance*900)/(4*M_PI);
  leftfront.move_relative  (ticks, speed);
  leftback.move_relative   (ticks, speed);
  rightfront.move_relative (ticks, speed);
  rightback.move_relative  (ticks, speed);
}

void baseturn(int left, int speed) // right=positive and left=negative
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

  while (fabs (ticks) - fabs (leftfront.get_position() - start) > 50) {
    pros::delay(3);
    printf("moving lf %8.2f rf %8.2f  target %8.2f",
    leftfront.get_position(), rightfront.get_position(), target);
  }
  pros::delay(100);
}


void turning (int left, int speed) // right=positive and left=negative
{
  double start = leftfront.get_position();
  double ticks = 735*left;
  double target = leftfront.get_position() + ticks;
  leftfront.move_relative  (ticks, speed);
  leftback.move_relative   (ticks, speed);
  rightfront.move_relative (-ticks, speed);
  rightback.move_relative  (-ticks, speed);

  while (fabs (ticks) - fabs (leftfront.get_position() - start)> 50) {
    pros::delay(3);
    printf("turing lf %8.2f rf %8.2f  target %8.2f",
    leftfront.get_position(), rightfront.get_position(), target);
  }
  pros::delay(100);
}


void turnDegree(double degree, int speed) // right=positive and left=negative
{
  double start;
  double ticks = 735.0/90*degree;
  start = leftfront.get_position();
  double target = leftfront.get_position() + ticks;
  leftfront.move_relative  (ticks, speed);
  leftback.move_relative   (ticks, speed);
  rightfront.move_relative (-ticks, speed);
  rightback.move_relative  (-ticks, speed);

  while (fabs (ticks) - fabs (leftfront.get_position() - start)> 50) {
    pros::delay(3);
    printf("turnDegree start %8.2f, target %8.2f, ticks %8.2f, lf position %8.2f rf position %8.2f condition, %d \n",
    start, target, ticks, leftfront.get_position(), rightfront.get_position(),
    fabs (ticks) - fabs (leftfront.get_position() - start)> 0);
  }
  pros::delay(100);
}

void gyroTurn(double degree, int speed) // right=positive and left=negative
{
  lv_obj_t * txt = lv_label_create(lv_scr_act(), NULL);
  //lv_obj_set_style(txt, &style_txt);                    /*Set the created style*/
  lv_label_set_long_mode(txt, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
  lv_label_set_recolor(txt, true);                      /*Enable re-coloring by commands in the text*/
  lv_label_set_align(txt, LV_LABEL_ALIGN_LEFT);       /*Center aligned lines*/
  lv_label_set_text(txt, NULL);
  lv_obj_set_width(txt, 300);                           /*Set a width*/
  lv_obj_align(txt, NULL, LV_ALIGN_CENTER, 0, 20);      /*Align to center*/

  gyro.reset();

  double start=gyro.get_value();
  double target=start+degree*10;
  int turnside;
  char mytext[100];
  if (degree>0) {
    turnside=1;
  } else turnside=-1;
  while (fabs(fabs(target)-fabs(gyro.get_value())) >2 ) {
    leftfront.move(speed*turnside);
    leftback.move(speed*turnside);
    rightfront.move(-speed*turnside);
    rightback.move(-speed*turnside);
    pros::delay(5);
    lv_label_set_text(txt, NULL);
    printf("gyro start %8.2f, target %8.2f, gyro %8.2f\n", start, target,gyro.get_value());
    sprintf(mytext, "gyro start %8.2f\n, target %8.2f\n, gyro %8.2f\n", start, target,gyro.get_value()
         );
    lv_label_set_text(txt, mytext);
  }

  leftfront.move(0);
  leftback.move(0);
  rightfront.move(0);
  rightback.move(0);

}


void ballLoad () {
  while (limitswitchball.get_value()==1) {
    catapult.move_velocity  (100);
    catapult.tare_position ( );
    pros::delay(3);
  }
  catapult.move_absolute(2090, 100);
}
