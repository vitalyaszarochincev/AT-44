#include "prog.h"

void writeInd(FILE* txtFile, FILE* indFile)
{
    long strInd = 0;
    char* buff = new char;

    while(!feof(txtFile))
    {
        strInd = ftell(txtFile);
        fwrite(&strInd, sizeof(long), 1, indFile);
        buff = readStr(txtFile, buff);
    }
}

void reversDigit(vector<int>& digitArr)
{
    for(size_t i = 0; i < digitArr.size(); i++)
    {
        int buff = 0;

        for(size_t j = 0; j < sizeof(int) * BITS_IN_BYTE; j++)
        {
            buff |= digitArr[i] & LAST_BIT;
            buff <<= 1;
            digitArr[i] >>= 1;
        }

        digitArr[i] = buff;
    }
}

int countSumm(FILE* file, long fileLenght)
{
    int sum = 0;
    int buff = 0;
    size_t digitNum = fileLenght / sizeof(int);

    for(size_t i = 0; i < digitNum; i++)
    {
        fread(&buff, sizeof(int), 1, file);
        
        if(!isdigit(buff))
        {
            sum += buff;
        }
    }

    return sum;
}

long countFileLenght(FILE* file)
{
    fseek(file, 0, SEEK_END);

    long lenght = ftell(file);

    rewind(file);

    return lenght;
}

char* findStr(long ind, FILE* txtFile, FILE* indFile)
{
    fseek(indFile, sizeof(long) * ind, SEEK_CUR);

    if(feof(indFile))
    {
        __exit(INCORRECT_INDEX, ind);
    }

    long strAddr = 0;

    fread(&strAddr, sizeof(long), 1, indFile);
    fseek(txtFile, strAddr, SEEK_SET);

    if(feof(txtFile))
    {
        __exit(INCORRECT_INDEX, ind);
    }

    char* buff = new char;

    return readStr(txtFile, buff);
}

FILE* openFile(char* fileName, const char mode[MODE_LENGHT + 1])
{
    FILE* file = fopen(fileName, mode);
    checkFile(file, fileName);

    if(!strcmp(mode, "rb"))
    {
        checkFileFormat(file, fileName);
    }else if(!strcmp(mode, "wb"))
    {
        formatFile(file);
    }
    return file;
}

char* readStr(FILE* file, char* buff)
{
    static size_t buffSize = START_STRING_SIZE;

    buff = (char*)alloc(buff, sizeof(char) * buffSize);
    memset(buff, 0, sizeof(char) * buffSize);

    char chr = 0;

    for(size_t i = 0; !feof(file); i++)
    {
        chr = fgetc(file);

        if((chr == '\n') || (chr == EOF))
        {
            break;
        }

        buff[i] = chr;

        if(i == (buffSize - 1))
        {
            buff = (char*)alloc(buff, sizeof(char) * buffSize);
            memset(&buff[i], 0, sizeof(char) * (buffSize - i));
        }
    }

    return buff;
}

void checkMem(void* buff)
{
    if(!buff)
    {
        fcloseall();
        __exit(MEMORY_NOT_ALLOCATED);
    }
}

void* alloc(void* buff, size_t size)
{
    buff = realloc(buff, sizeof(char) * size);
    checkMem(buff);

    return buff;
}