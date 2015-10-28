#include "prog.h"


void task1(char* fileName, int num)
{
    if(num == NO_PARAMETERS)
    {
        FILE* file = openFile(fileName, "wb");

        vector<int> digitArr;

        writeArrToFile(digitArr, file);
        fclose(file);
    }else
    {
        FILE* file = openFile(fileName, "rb");

        int digit = 0;
        readDigFromFile(file, num, digit);
        fclose(file);
    }
}

void task2(char* fileName, int num)
{
    if(num == NO_PARAMETERS)
    {
        FILE* file = openFile(fileName, "wb");

        vector<short> digitArr;

        writeArrToFile(digitArr, file);
        fclose(file);
    }else
    {
        FILE* file = openFile(fileName, "rb");

        short digit = 0;
        readDigFromFile(file, num, digit);
        fclose(file);
    }
}

void task3(char* fileName, int num)
{
    if(num == NO_PARAMETERS)
    {
        FILE* file = openFile(fileName, "wb");

        vector<double> digitArr;

        writeArrToFile(digitArr, file);
        fclose(file);
    }else
    {
        FILE* file = openFile(fileName, "rb");

        double digit = 0;
        readDigFromFile(file, num, digit);
        fclose(file);
    }
}

void task4(char* fileName, int num)
{
    if(num == NO_PARAMETERS)
    {
        FILE* file = openFile(fileName, "wb");

        vector<int> digitArr;
        writeArrToFile(digitArr, file, 'r');
        fclose(file);
    }else
    {
        FILE* file = openFile(fileName, "rb");
        
        int digit = 0;
        readDigFromFile(file, num, digit);
        fclose(file);
    }
}

void task5(char* fileName, int num)
{
    FILE* file = fopen(fileName, "rb");
    bool mode = checkFileAndContinue(file);

    if(mode)
    {
        checkFileFormat(file, fileName);
        long fileLenght = countFileLenght(file);
        fseek(file, OFFSET, SEEK_SET);

        cout << countSumm(file, fileLenght - OFFSET) << endl;
        fclose(file);
    }else
    {
        file = fopen(fileName, "wb");
        checkFile(file, fileName);
        formatFile(file, countFileLenght(file));

        vector<int> digitArr;
        writeArrToFile(digitArr, file);
        fclose(file);
    }
}

void task6(char* txtFileName, int num)
{
    FILE* txtFile = openFile(txtFileName, "r");
    char* indFileName = createFileName(txtFileName);
    FILE* indFile = openFile(indFileName, "wb");

    writeInd(txtFile, indFile);
    fclose(indFile);

    indFile = openFile(indFileName, "rb");

    long neededInd = 0;

    cin >> neededInd;
    puts(findStr(neededInd, txtFile, indFile));
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
    fseek(file, (num - 1) * sizeof(digType) + (CONTROL_STR_SIZE * sizeof(char)), SEEK_SET);

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
