#ifndef USERFN_H
#define USERFN_H

void basemovement(double distance, int speed);

void baseturn(int left, int speed);

void moving (double distance, int speed);

void turning (int left, int speed);

void turnDegree(double degree, int speed);

void gyroTurn(double degree, int speed); // right=positive and let=negative

void ballLoad();

#endif
