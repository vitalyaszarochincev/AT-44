#include "prog.h"

int main(int argc, char* argv[])
{
    checkParameters(argc);

    FILE* inputFile = fopen(argv[1], "r");
    checkFile(inputFile, argv[1]);

    char* newName = new char[strlen(argv[1])];
    createName(argv[1], newName);

    FILE* outFile = fopen(newName, "wb");
    checkFile(outFile, newName);

    delete newName;
    fcloseall();

    return 0;
}

void createName(char* oldName, char* newName)
{
    strcpy(newName, oldName);
    memset(&newName[strlen(newName) - 3], 0, sizeof(char) * 3); //clean last symbols 3 in name (txt)
    strcat(newName, "bin");
}
