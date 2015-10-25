#ifndef PROG_H_INCLUDED
#define PROG_H_INCLUDED

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstdarg>
#include <vector>
#include <cctype>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

enum Parameters
{
    ONLY_EXE = 1,
    ONE_PARAM = 2,
    TWO_PARAMETERS = 3,
    THREE_PARAMETERS = 4,
    NO_PARAMETERS = -1,
    MANY_PARAMETERS = -2,
    MIN_TASK = 1,
    MAX_TASK = 10,
    INCORRECT_TASK = -3,
    INCORRECT_FILE = -4,
    NUM_OF_TASKS = 10,
    INCORRECT_NUMBER = -5
};

int checkParameters(int, char**);
void checkFile(FILE*, char*);
void task1(char*, int);
void task2(char*, int);
void task3(char*, int);
void task4(char*, int);
void task5(char*, int);
void task6(char*, int);
void task7(char*, int);
void task8(char*, int);
void task9(char*, int);
void task10(char*, int);
void __exit(int, ...);
void writeArrToFile(FILE*);
void readDigFromFile(FILE*, int);

#endif // PROG_H_INCLUDED
