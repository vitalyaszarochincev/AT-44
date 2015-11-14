#include "cip.h"

void encode(const char* inputFileName)
{
    FILE* txtFile = openFile(inputFileName, "rt");

    char* binFileName = createFileName(inputFileName);
    FILE* binFile = openFile(binFileName, "wb");
    formatFile(binFile);

    char key = createKey(binFileName);

    delete(binFileName);

    encodeFile(txtFile, binFile, key);

    fclose(txtFile);
    fclose(binFile);
}

inline void formatFile(FILE* file)
{
    fwrite(controlStr, sizeof(char), CONTROL_STR_LENGHT, file);
}

inline void encodeFile(FILE* txtFile, FILE* binFile, char key)
{
    char str[MAX_STR_LEN] = {0};
    char strLenght = 0;
    long fileLenght = 0;

    fwrite(&fileLenght, sizeof(long), 1, binFile);

    while(fgets(str, MAX_STR_LEN, txtFile))
    {
        deleteStrBreaks(str);
        strLenght = (char)strlen(str);
        encodeStr(str, key);

        fwrite(&strLenght, sizeof(char), 1, binFile);
        fwrite(str, sizeof(char), strLenght, binFile);

        fileLenght += 1 + strLenght;
    }

    fseek(binFile, sizeof(char) * CONTROL_STR_LENGHT, SEEK_SET);
    fwrite(&fileLenght, sizeof(long), 1, binFile);
}

inline void deleteStrBreaks(char* str)
{
    for(size_t i = strlen(str); i; i--)
    {
        if(str[i] == '\n')
        {
            str[i] = 0;
        }
    }
}
