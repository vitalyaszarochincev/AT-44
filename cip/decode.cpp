#include "cip.h"

void decode(const char* inputFileName)
{
    FILE* binFile = openFile(inputFileName, "rb");
    checkFormat(binFile);

    char key = createKey(inputFileName);
    decodeFile(binFile, key);

    fclose(binFile);
}

inline void checkFormat(FILE* file)
{
    char contStr[CONTROL_STR_LENGHT + 1] = {0};

    fread(contStr, sizeof(char), CONTROL_STR_LENGHT, file);

    if(strcmp(controlStr, contStr))
    {
        __exit(INCORRECT_FILE);
    }
}

inline void decodeFile(FILE* binFile, char key)
{
    char str[MAX_STR_LEN] = {0};
    char strLenght = 0;
    long fileLenght = 0;
    long countedFileLenght = countFileLenght(binFile) - INFO_LENGHT;

    fseek(binFile, CONTROL_STR_LENGHT, SEEK_SET);
    fread(&fileLenght, sizeof(long), 1, binFile);

    checkFileLenght(fileLenght, countedFileLenght);

    while(fileLenght)
    {
        fileLenght -= fread(&strLenght, sizeof(char), 1, binFile);
        fileLenght -= fread(str, sizeof(char), strLenght, binFile);

        encodeStr(str, key);

        cout << (int)strLenght << ' ' << str << endl;
        memset(str, 0, sizeof(char) * MAX_STR_LEN);
    }
}

inline void checkFileLenght(long fileLenght, long countedFileLenght)
{
    if(fileLenght != countedFileLenght)
    {
        __exit(INCORRECT_FILE);
    }
}
