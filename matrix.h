#include <iostream>
#include <ctime>
#include <iomanip>

#define PI 3.1415956535

using namespace std;

class Matrix;

class Array
{
public:
	int x[5];
	Array() {
		for (int i = 0; i < 5; i++) {
			x[i] = rand() % 21 - 10;
		}
	}

	int& operator [](int i)
	{
		return x[i];
	}
	friend Matrix;
};



class Matrix
{

public:
	Array y[5];

	void show() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				cout << setw(4) << y[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}

	void edit(int a, int b) {
		cin >> y[a][b];
	}

	Array& operator [](int i)
	{
		return y[i];
	}

	Matrix &operator +(Matrix N)
	{
		int i, j;
		Matrix temp;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				temp[i][j] = N.y[i][j] + y[i][j];
			}
		}
		return temp;
	}

	Matrix &operator -(Matrix N)
	{
		int i, j;
		Matrix temp;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				temp[i][j] = N.y[i][j] - y[i][j];
			}
		}
		return temp;
	}

	bool operator ==(Matrix N)
	{
		bool k = 1;
		int i, j;
		Matrix temp;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				if (N.y[i][j] != y[i][j]) {
					k = 0;
				}
			}
		}
		return k;
	}

	Matrix &operator =(Matrix N)
	{
		int i, j;
		Matrix temp;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				y[i][j] = N.y[i][j];
			}
		}
		return *this;
	}

	Matrix &operator +=(Matrix N)
	{
		int i, j;
		Matrix temp;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				y[i][j] += N.y[i][j];
			}
		}
		return *this;
	}

	Matrix &operator -=(Matrix N)
	{
		int i, j;
		Matrix temp;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				y[i][j] -= N.y[i][j];
			}
		}
		return *this;
	}

};

void main() {
	srand(time(NULL));

	system("pause");
}
