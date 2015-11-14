#ifndef CIP_H_INCLUDED
#define CIP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

typedef void (*TASK_F)(const char*);

const char controlStr[] = {"lab2"};
const char ENCODE[] = {"-e"};
const char DECODE[] = {"-d"};

const int MAX_STR_LEN = 256;
const int CONTROL_STR_LENGHT = 4;
const int MODULE = 256;


using std::cout;
using std::endl;

enum Errors
{
	INCORRECT_PARAMETERS = 1,
	INCORRECT_FILE = 2
};

enum
{
    NO_PARAMETERS = 1,
    ONE_PARAMETER = 2,
    REQUIRED_NUM_OF_PARAMETERS = 3
};

#define INFO_LENGHT ((CONTROL_STR_LENGHT) + (sizeof(long)))

void encode(const char*);
inline void encodeFile(FILE*, FILE*, char);

void encodeStr(char*, char);

void decode(const char*);
inline void decodeFile(FILE*, char);

char createKey(const char*);
size_t findDot(const char*);
inline void deleteStrBreaks(char*);

void __exit(Errors);
inline int checkParameters(int, char**);
inline void checkFormat(FILE*);

FILE* openFile(const char*, const char*);
inline void formatFile(FILE*);
void checkFile(FILE*);
char* createFileName(const char*);
long countFileLenght(FILE*);
inline void checkFileLenght(long, long);

#endif // CIP_H_INCLUDED
