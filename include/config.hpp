#ifndef CONFIG_H
#define CONFIG_H

extern pros::Motor leftfront  ;
extern pros::Motor leftback   ;
extern pros::Motor rightfront ;
extern pros::Motor rightback  ;
extern pros::Motor lift   ;
extern pros::Motor claw  ;
extern pros::Motor ballintake     ;
extern pros::Motor catapult   ;
extern pros::Motor flipper    ;
extern pros::Controller master;         // master control
extern pros::Controller partner;        //partner control
extern pros::ADIAnalogIn bumper;        // not use yet
extern pros::ADIAnalogIn potentiameter; //potentiameter for claw
extern pros::ADIAnalogIn ballshooterp; //potentiameter for catapult
extern pros::ADIDigitalIn limitswitch ; //limitswitch for arm lift
extern pros::ADIDigitalIn limitswitchball ; //limitswitch for ball shoot
extern int automode;
enum redblue {red = 1, blue = -1};
enum frontback {front = 1, back = -1};
extern redblue side;
#endif
