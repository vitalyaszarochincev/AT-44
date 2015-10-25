#include "prog.h"

void task1(char* fileName, int num)
{
    FILE* file = NULL;

    if(num == NO_PARAMETERS)
    {
        file = fopen(fileName, "wb");
        checkFile(file, fileName);

        vector<int> digitArr;

        writeArrToFile(digitArr, file);
    }else
    {
        file = fopen(fileName, "rb");
        checkFile(file, fileName);

        int digit = 0;
        readDigFromFile(file, num, digit);
    }
}

void task2(char* fileName, int num)
{
    FILE* file = NULL;

    if(num == NO_PARAMETERS)
    {
        file = fopen(fileName, "wb");
        checkFile(file, fileName);

        vector<short> digitArr;

        writeArrToFile(digitArr, file);
    }else
    {
        file = fopen(fileName, "rb");
        checkFile(file, fileName);

        short digit = 0;
        readDigFromFile(file, num, digit);
    }
}

void task3(char* fileName, int num)
{
    FILE* file = NULL;

    if(num == NO_PARAMETERS)
    {
        file = fopen(fileName, "wb");
        checkFile(file, fileName);

        vector<double> digitArr;

        writeArrToFile(digitArr, file);
    }else
    {
        file = fopen(fileName, "rb");
        checkFile(file, fileName);

        double digit = 0;
        readDigFromFile(file, num, digit);
    }
}

void task4(char* fileName, int num)
{
    FILE* file = NULL;

    if(num == NO_PARAMETERS)
    {
        file = fopen(fileName, "wb");
        checkFile(file, fileName);

        vector<int> digitArr;
        writeArrToFile(digitArr, file, 'r');
    }else
    {
        file = fopen(fileName, "rb");
        checkFile(file, fileName);

        int digit = 0;
        readDigFromFile(file, num, digit);
    }
}

template<typename arrType>
void writeArrToFile(vector<arrType>& digitArr, FILE* file)
{
    readArr(digitArr);
    writeArr(digitArr, file);
}

template<typename arrType>
void writeArrToFile(vector<arrType>& digitArr, FILE* file, char mode)
{
    readArr(digitArr);

    if(mode == 'r')
    {
        reversDigit(digitArr);
    }

    writeArr(digitArr, file);
}

template<typename digType>
void readDigFromFile(FILE* file, int num, digType& digit)
{
    fseek(file, (num - 1) * sizeof(digType), SEEK_SET);

    fread(&digit, sizeof(digType), 1, file);

    if(feof(file) || (num <= 0))
    {
        __exit(INCORRECT_NUMBER, num);
    }

    cout << digit << endl;
}

template<typename arrType>
void readArr(vector<arrType>& digitArr)
{
    arrType digit = 1;

    while(digit)
    {
        cin >> digit;

        if(!isdigit(digit))
        {
            digitArr.push_back(digit);
        }
    }
}

template<typename arrType>
void writeArr(vector<arrType>& digitArr, FILE* file)
{
    for(size_t i = 0; i < digitArr.size() - 1; i++)
    {
        fwrite(&digitArr[i], sizeof(arrType), 1, file);
    }
}
