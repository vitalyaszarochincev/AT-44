#include "cip.h"

char createKey(const char* name)
{
    long key = 0;
    size_t dotInd = findDot(name);

    for(size_t i = 0; i < dotInd; i++)
    {
        key += key * 255 + name[i];
    }

    return (char)(key % MODULE);
}

void checkFile(FILE* file)
{
	if(!file)
    {
		__exit(INCORRECT_FILE);
    }
}

FILE* openFile(const char* name, const char* mode)
{
    FILE* file = fopen(name, mode);
    checkFile(file);

    return file;
}

size_t findDot(const char* str)
{
    size_t i = strlen(str);

    for(; i; i--)
    {
        if(str[i] == '.')
        {
            break;
        }
    }

    return i;
}

char* createFileName(const char* oldName)
{
	size_t oldNameLenght = strlen(oldName);
    char* newName = new char[oldNameLenght + 1];

	strcpy(newName, oldName);
    strcpy(&newName[findDot(newName)], ".bin");

	return newName;
}

void encodeStr(char* str, char key)
{
    char strLenght = (char)strlen(str);
    for(char i = 0; i < strLenght; i++)
    {
        str[i] ^= key;
    }
}

long countFileLenght(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long result = ftell(file);
    rewind(file);

    return result;
}
