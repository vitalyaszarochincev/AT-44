#ifndef PROG_H_INCLUDED
#define PROG_H_INCLUDED

#include <iostream>
#include <cstdarg>
#include <cstdlib>
#include <fstream>
#include <cstring>

#define REQUIRED_PARAMETERS_NUM 2

using std::cin;
using std::cout;
using std::endl;

enum Errors
{
    INCORRECT_PARAMETERS = 1,
    INCORRECT_FILE = 2
};

void checkParameters(int);
void __exit(Errors, ...);
void checkFile(FILE*, char*);
void createName(char*, char*);

#endif // PROG_H_INCLUDED
