#include "prog.h"

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
        printf("$%d\n", buff);
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

void task6(char* fileName, int num)
{
    cout << num << endl;
}

void task7(char* fileName, int num)
{
    cout << num << endl;
}

void task8(char* fileName, int num)
{
    cout << num << endl;
}

void task9(char* fileName, int num)
{
    cout << num << endl;
}

void task10(char* fileName, int num)
{
    cout << num << endl;
}
