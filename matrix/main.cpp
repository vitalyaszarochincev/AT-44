#include "list.h"
#include "matrix.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    List<int> list1(5);
    list1.print();
    list1.pushBack(7);
    list1.print();
    list1.pushFront(1);
    list1.print();
    list1.add(4, 2);
    list1.print();
    cout << list1.getHead() << " " << list1.getTail() << " " << list1.getVal(3) << endl;
    list1.revers();
    list1.print();
    cout << list1.popBack() << endl;
    list1.print();

    return 0;
}

