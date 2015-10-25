#include "prog.h"

void reversDigit(vector<int>& digitArr)
{
    for(size_t i = 0; i < digitArr.size(); i++)
    {
        int buff = 0;

        for(size_t j = 0; j < sizeof(int) * BITS_IN_BYTE; j++)
        {
            buff |= digitArr[i] & 1;
            buff <<= 1;
            digitArr[i] >>= 1;
        }

        digitArr[i] = buff;
    }
}

void task5(char* fileName, int num)
{
    cout << num << endl;
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
