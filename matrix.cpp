#include "matrix.h"

#include "array.h"

#include <iostream>
using std::cout; // пространство имен std для cout
using std::cin; // пространство имен std для cin

#include <iomanip> // для манипулятора setw
using std::setw;   // пространство имен std для setw

#include <cstdlib>

Matrix::Matrix() // конструктор по умолчанию
{
    size = 10; // по умолчанию размер матрицы = 10 объектам типа Array
    ptr = new Array [size]; // выделить место в памяти для матрицы
    for (int ix = 0; ix < size; ix++) // обнуляем матрицу
        for (int jx = 0; jx < 10; jx++)
            ptr[ix][jx] = 0;
}

Matrix::Matrix(int matrixSize, int arraySize) // конструктор с параметрами
{
    size = (matrixSize > 0 ? matrixSize : 10); // количество строк

    ptr = new Array [size]; // выделить место в памяти для матрицы

    for (int ix = 0; ix < size; ix++) // перераспределяем выделенную память
        ptr[ix].setSize(arraySize > 0 ? arraySize : 10); // количество столбцов

    for (int ix = 0; ix < size; ix++) // обнуляем матрицу
        for (int jx = 0; jx < ptr->getSize(); jx++)
            ptr[ix][jx] = 0;
}

Matrix::Matrix(  Matrix &matrixToCopy ) // конструктор копии
    :size(matrixToCopy.size)              // инициализатор размера массива
{
    ptr = new Array [size]; // выделить место в памяти для матрицы

    for (int ix = 0; ix < size; ix++) // перераспределяем выделенную память
        ptr[ix].setSize(size); // количество столбцов

    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            ptr[ix][jx] = matrixToCopy[ix][jx];// заполняем матрицу значениями матрицы matrixToCopy
}

Matrix::~Matrix() // десструктор класса Matrix
{
   delete  [] ptr; // освободить память, удалив матрицу
}

int Matrix::getSize() const // возвратить количество элементов матрицы
{
    return size;
}

Array *Matrix::getPtr() const
{
    return ptr;
}

// перегруженный оператор вывода для класса Array (вывод элементов массива на экран)
ostream &operator<< (ostream &output, const Matrix &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
    {
        for (int jx = 0; jx < obj.ptr->getSize(); jx++)
        {
            output << setw(5) // под каждое число выделяется 5 позиций
                   << obj.ptr[ix][jx];
        }
        cout << std::endl;
    }

    output << std::endl; // перенос маркера на новую строку

    return output; // позволяет множественный вывод, типа cout << x << y << z << ...
}

// перегруженный оператор ввода, для заполнения матрицы с клавиатуры
istream &operator>> (istream & input, Matrix &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
        for (int jx = 0; jx < obj.ptr->getSize(); jx++)
            input >> obj.ptr[ix][jx]; // заполняем матрицу

    return input; // позволяет множественный ввод, типа cin >> x >> y >> z >> ...
}

// перегруженный оператор взятия индекса
Array &Matrix::operator[] (int subscript)
{
    if(subscript < 0 || subscript >= size)
    {
        std::cerr << "\n Ошибка индекса: " << subscript << std::endl;
        exit(1); // завершить работу программы, неправильный индекс
    }
    return ptr[subscript]; // возврат ссылки на элемент массива
}

void Matrix::setMatrix() // заполнение массива
{
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            cin >> ptr[ix][jx]; // ввод элементов матрицы с клавиатуры
}

void Matrix::getMatrix() // вывод массива
{
    for (int ix = 0; ix < size; ix++)
    {
        for (int jx = 0; jx < ptr->getSize(); jx++)
            cout << setw(5) << ptr[ix][jx]; // вывод элементов матрицы на экран
        cout << std::endl;
    }

    cout << std::endl; // новая строка
}

int *Matrix::search(const int key) const // поиск по ключу
{
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            if ( key == ptr[ix][jx] ) // поиск по ключу
                return (&ptr[ix][jx]);             // позиция искомого элемента

    return NULL;
}

Matrix Matrix::operator+ (const Matrix &right)
{
    if (size != right.size || ptr->getSize() != right.getPtr()->getSize())
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }

    Matrix result(size, ptr->getSize());
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            result.ptr[ix][jx] = ptr[ix][jx] + right.ptr[ix][jx];

    return result; // вернуть сумму
}

Matrix Matrix::operator+= (const Matrix &right)
{
    if (size != right.size || ptr->getSize() != right.getPtr()->getSize())
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }

//    Matrix result(size, ptr->getSize());
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            ptr[ix][jx] = ptr[ix][jx] + right.ptr[ix][jx];

    return *this; // вернуть сумму
}

Matrix Matrix::operator- (const Matrix &right)
{
    if (size != right.size || ptr->getSize() != right.getPtr()->getSize())
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }

    Matrix result(size, ptr->getSize());
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            result.ptr[ix][jx] = ptr[ix][jx] - right.ptr[ix][jx];

    return result; // вернуть сумму
}

const Matrix &Matrix::operator= (const Matrix &right) // оператор присваивания
{
    if (&right != this) // чтобы не выполнялось самоприсваивание
    {
        if (size != right.size || ptr->getSize() != right.getPtr()->getSize())
        {
            delete [] ptr; // освободить пространство
            size = right.size; // установить нужный размер матрицы
            ptr = new Array [size]; // выделить память под копируемый массив

            for (int ix = 0; ix < size; ix++) // перераспределяем выделенную память
                ptr[ix].setSize(right.getPtr()->getSize()); // количество столбцов
        }

        for (int ix = 0; ix < size; ix++)
            for (int jx = 0; jx < ptr->getSize(); jx++)
                ptr[ix][jx] = right.ptr[ix][jx]; // скопировать массив
    }

    return *this; // разрешает множественное присваивание, например x = t = e
}

bool Matrix::operator== (const Matrix &right) const// оператор сравнения
{
    if (size != right.size || ptr->getSize() != right.getPtr()->getSize())
        return false; // матрицы с разным количеством элементов

    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            if (ptr[ix][jx] != right.ptr[ix][jx])
                return false; // матрицы не равны

    return true; // матрицы равны
}
