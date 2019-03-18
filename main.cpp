#include <iostream>
using namespace std;

#include "matrix.h"
#include "array.h"
#include <cstdlib>

int main()
{
    srand(time(NULL));
    Matrix myMatrix1(5,5); // конструктор с параметрами

    // заполнение матрицы
    for (int ix = 0; ix < myMatrix1.getSize(); ix++)
        for (int jx = 0; jx < myMatrix1.getPtr()->getSize(); jx++)
            myMatrix1[ix][jx] = rand() % 100;

    cout << myMatrix1;  // перегруженный оператор вывода

    Matrix myMatrix2(myMatrix1); // конструктор копии

    myMatrix2.getMatrix(); // вывод матрицы с помощью метода класса Matrix

    //myMatrix2.setMatrix(); // заполнение матрицы с помощью метода класса Matrix

    int * adr = myMatrix2.search(99);

    if (adr == NULL)
        cout << "Значения " << 99 << " в матрице нет!\n";
    else
        cout << "Значение " << 99 << " находится в памяти по адресу: " << adr << endl;

    cout << (myMatrix1 + myMatrix2); // перегруженная операция сложения

    cout << "Как видите, myMatrix1 осталась без изменения!\n";
    cout << myMatrix1;

    myMatrix1 += myMatrix2; // перегруженная операция сложения-присвоения

    cout << "myMatrix1 содержит значения ,полученные при: myMatrix1 += myMatrix2; !\n";
    cout << myMatrix1;

    cout << (myMatrix1 - myMatrix1); // перегруженная операция вычитания

    Matrix myMatrix3 = myMatrix2; // перегруженная операция присваивания

    cout << myMatrix3;

    if (myMatrix3 == myMatrix2)
        cout << "Матрицы myMatrix3 и myMatrix2 равны!\n";

    return 0;
}
