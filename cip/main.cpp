#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define REQUIRED_NUM_OF_PARAMETERS 3
#define NAME_TAIL 4
#define ENCODE "-e"
#define DECODE "-d"
#define MAX_STR_LEN 256
#define CONTROL_STR_LENGHT 4

using std::cout;
using std::endl;

const char controlStr[] = {"lab2"};

enum Errors
{
	INCORRECT_PARAMETERS = 1,
	INCORRECT_FILE = 2
};

void __exit(Errors);
inline void checkParameters(int);
inline void checkFile(FILE*);
void createFileName(char*);
void encode(FILE*, FILE*, char);
void decode(FILE*, char);
long countFileLenght(FILE*);
inline void formatFile(FILE*);
void checkFormat(FILE*);
char createKey(char*);

int main(int argc, char** argv)
{
	checkParameters(argc);

    if(!strcmp(argv[1], ENCODE))
    {
        FILE* txtFile = fopen(argv[2], "r");
        checkFile(txtFile);

        createFileName(argv[2]);
        FILE* binFile = fopen(argv[2], "wb");
        checkFile(binFile);
        formatFile(binFile);

        memset(&argv[2][strlen(argv[2]) - NAME_TAIL], 0, sizeof(char) * NAME_TAIL);
        char key = createKey(argv[2]);

        encode(txtFile, binFile, key);

        fclose(txtFile);
        fclose(binFile);
    }else if(!strcmp(argv[1], DECODE))
    {
        FILE* binFile = fopen(argv[2], "rb");
        checkFile(binFile);
        checkFormat(binFile);

        memset(&argv[2][strlen(argv[2]) - NAME_TAIL], 0, sizeof(char) * NAME_TAIL);
        char key = createKey(argv[2]);

        decode(binFile, key);
    }else
    {
        __exit(INCORRECT_PARAMETERS);
    }

	return 0;
}

inline void checkParameters(int argc)
{
	if(argc != REQUIRED_NUM_OF_PARAMETERS)
		 __exit(INCORRECT_PARAMETERS);
}

void __exit(Errors errorCode)
{
	switch(errorCode)
	{
	case INCORRECT_PARAMETERS:
		cout << "incorrect parameters" << endl;
		break;

	case INCORRECT_FILE:
		cout << "incorrect file" << endl;
		break;
	}

	exit(0);
}

inline void checkFile(FILE* file)
{
	if(!file)
		__exit(INCORRECT_FILE);
}

void createFileName(char* oldName)
{
	size_t oldNameLenght = strlen(oldName);

	strcpy(&oldName[oldNameLenght - NAME_TAIL], ".bin");
}

void encode(FILE* txtFile, FILE* binFile, char key)
{
    char str[MAX_STR_LEN] = {0};
    char strLenght = 0;
    char encodedStrLenght = 0;

    while(fgets(str, MAX_STR_LEN, txtFile))
    {
        strLenght = (char)strlen(str) - 1;

        for(char i = 0; i < strLenght; i++)
        {
            str[i] ^= key;
        }

        encodedStrLenght = strLenght ^ key;

        fwrite(&encodedStrLenght, sizeof(char), 1, binFile);
        fwrite(str, sizeof(char), strLenght, binFile);
    }
}

void decode(FILE* file, char key)
{
    char str[MAX_STR_LEN] = {0};
    char strLenght = 0;
    size_t i = (size_t)countFileLenght(file) - CONTROL_STR_LENGHT;

    fseek(file, CONTROL_STR_LENGHT, SEEK_SET);

    while(i)
    {
        i -= fread(&strLenght, sizeof(char), 1, file);

        strLenght ^= key;
        i -= fread(str, sizeof(char), strLenght, file);

        for(char i = 0; i < strLenght; i++)
        {
            str[i] ^= key;
        }

        printf("%d %s\n", strLenght, str);
        memset(str, 0, sizeof(char) * MAX_STR_LEN);
    }
}

inline void formatFile(FILE* file)
{
    fwrite(controlStr, sizeof(char), CONTROL_STR_LENGHT, file);
}

long countFileLenght(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long result = ftell(file);
    rewind(file);

    return result;
}

void checkFormat(FILE* file)
{
    char contStr[CONTROL_STR_LENGHT] = {0};

    fread(contStr, sizeof(char), CONTROL_STR_LENGHT, file);

    if(strcmp(controlStr, contStr))
        __exit(INCORRECT_FILE);
}

char createKey(char* name)
{
    long long key = 0;

    while(*name)
    {
        key += key * 255 + *name;
        name++;
    }
    return (char)(key % 256);
}
