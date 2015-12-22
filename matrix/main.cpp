#include "list.h"
#include "matrix.h"
#include <fstream>
#include <math.h>

using std::endl;

int main()
{
    std::ofstream testFile("C:\\Users\\vitalii\\Documents\\projects\\matrix\\data\\test.txt");
    testFile.close();
    testFile.open("C:\\Users\\vitalii\\Documents\\projects\\matrix\\data\\test.txt", std::ios::app | std::ios::out);
    int arr[5] = {1, 2, 3, 4, 5};
    List<int> list1;
    List<int> list2(5);
    List<int> list3(arr, 5);
    List<int> list4(list3);

    testFile << "list1 : " << endl;
    list1.print();
    testFile << endl << "list2 : " << endl;
    list2.print();
    testFile << endl << "list3 : " << endl;
    list3.print();
    testFile << endl << "list4 : " << endl;
    list4.print();

    testFile << endl << "list3 size : " << list3.getSize() << endl;
    testFile << endl << "list1 isEmpty : " << list1.isEmpty() << endl;
    testFile << endl << "list3 isEmpty : " << list3.isEmpty() << endl;

    testFile << endl << "list3 push back : " << endl;
    list3.pushBack(10);
    list3.print();
    testFile << endl << "list3 push front : " << endl;
    list3.pushFront(11);
    list3.print();
    testFile << endl << "list3 add 3 : " << endl;
    list3.add(12, 3);
    list3.print();

    testFile << endl << "list3 get head : " << endl;
    testFile << list3.getHead() << endl;
    testFile << endl << "list3 get tail : " << endl;
    testFile << list3.getTail() << endl;
    testFile << endl << "list3 get val 4 : " << endl;
    testFile << list3.getVal(4) << endl;

    testFile << endl << "reverse list3 : " << endl;
    list3.revers();
    list3.print();

    testFile << endl << "list3 pop head : " << endl;
    list3.popFront();
    list3.print();

    testFile << endl << "list3 pop 5 : " << endl;
    list3.pop(5);
    list3.print();

    testFile << endl << "list3 pop tail : " << endl;
    list3.popBack();
    list3.print();

    testFile << endl << "operator = list1 = list4 : " << endl;
    list1 = list4;
    list1.print();

    testFile << endl << "list3 operator [] : " << endl;
    for(size_t i = 0; i < list3.getSize(); i++)
    {
        testFile << list3[i] << " ";
    }
    testFile << endl;

    int* arr1 = new int[3];
    int* arr2 = new int[3];
    int* arr3 = new int[3];

    for(int i = 0; i < 3; i++)
    {
        arr1[i] = i;
        arr2[i] = i * 2;
        arr3[i] = i * 3;
    }

    int** matArr = new int*[3];

    matArr[0] = arr1;
    matArr[1] = arr2;
    matArr[2] = arr3;

    Matrix matr1;
    Matrix matr2(5, 3);
    Matrix matr3(matArr, 3, 3);

    testFile << endl << "matr1 : " << endl;
    matr1.print();

    testFile << endl << "matr2 : " << endl;
    matr2.print();

    testFile << "matr3 : " << endl;
    matr3.print();

    testFile << "matr *=(int) 5 : " << endl;
    matr3 *= 5;
    matr3.print();

    return 0;
}
