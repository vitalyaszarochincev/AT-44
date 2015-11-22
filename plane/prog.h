#ifndef PROG_H_INCLUDED
#define PROG_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using std::cout;
using std::endl;

const int UP = 72;
const int DOWN = 80;
const int EXIT = 27;
const double OFFSET = 0.1;
const int MAX_ANGLE = 90;
const int MIN_ANGLE = -MAX_ANGLE;
const int MIN_HIGH = 0;
const int DELAY = 100;

double countHigh(double);
void printError();
void printStatus(double, double);
void printWarning(int);

#endif // PROG_H_INCLUDED
