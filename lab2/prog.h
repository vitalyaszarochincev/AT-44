#ifndef PROG_H_INCLUDED
#define PROG_H_INCLUDED

#define CRT_SECURE_NO_WARNINGS //kill visual studio

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstdarg>
#include <vector>
#include <cctype>
#include <cstring>

#define BITS_IN_BYTE 8
#define CONTROL_STR_SIZE 5
#define LAST_BIT 1
#define ESCALATION 4
#define MODE_LENGHT 2
#define START_STRING_SIZE 10

#define SIZE_OF_CHAR (sizeof(char))
#define SIZE_OF_CONTROL_STRING ((CONTROL_STR_SIZE) * (SIZE_OF_CHAR))
#define SIZE_OF_LONG (sizeof(long))
#define OFFSET ((SIZE_OF_CONTROL_STRING) + (SIZE_OF_LONG))

#define EXSTEND_SIZE(size) ((size) *= (2))

typedef void (*task_t)(char*, int);

using std::cout;
using std::cin;
using std::endl;
using std::vector;

enum Errors
{
    ONLY_EXE = 1,
    ONE_PARAM = 2,
    TWO_PARAMETERS = 3,
    THREE_PARAMETERS = 4,
    NUM_OF_TASKS = 10,
    MIN_TASK = 1,
    MAX_TASK = 10,
    NO_PARAMETERS = -1,
    MANY_PARAMETERS = -2,
    INCORRECT_TASK = -3,
    INCORRECT_FILE = -4,
    INCORRECT_NUMBER = -5,
    INCORRECT_INDEX = -6,
    MEMORY_NOT_ALLOCATED = -7
};

const char controlStr[CONTROL_STR_SIZE + 1] = {"task0"};

void __exit(int, ...);
int checkParameters(int, char**);
void checkFile(FILE*, char*);
bool checkFileAndContinue(FILE*);
void checkFileFormat(FILE*, char*);
void formatFile(FILE*);
void formatFile(FILE*, long);
void task1(char*, int);
void task2(char*, int);
void task4(char*, int);
void task3(char*, int);
void task5(char*, int);
void task6(char*, int);
void task7(char*, int);
void task8(char*, int);
void task9(char*, int);
void task10(char*, int);
template<typename arrType> void writeArrToFile(vector<arrType>&, FILE*);
template<typename arrType> void writeArrToFile(vector<arrType>&, FILE*, char);
template<typename digType> void readDigFromFile(FILE*, int, digType&);
template<typename arrType> void readArr(vector<arrType>&);
template<typename arrType> void writeArr(vector<arrType>&, FILE*);
void reversDigit(vector<int>&);
int countSumm(FILE*, long);
long countFileLenght(FILE*);
char* createFileName(char*);
void writeInd(FILE*, FILE*);
char* findStr(long, FILE*, FILE*);
FILE* openFile(char*, const char[]);
void checkMem(void*);
void* alloc(void*, size_t);
char* readStr(FILE* file, char* buff);

#endif // PROG_H_INCLUDED
