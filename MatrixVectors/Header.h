#include <iostream>

using namespace std;

class Vector
{
public:

	Vector(std::initializer_list<float> list);

	Vector();

	~Vector();

	Vector(const Vector& other);

	Vector& operator = (const Vector& other);

	friend ostream& operator <<(ostream& os, const Vector& v);

	bool operator ==(const Vector& other);

	bool operator !=(const Vector& other);

	Vector operator +(const Vector& other);

	void operator +=(const Vector& other);

	Vector operator -(const Vector& other);

	void operator -=(const Vector& other);

	Vector operator *(const float factor);

	void operator *=(const float factor);

	float operator *(const Vector& other);

	float operator [](int index);

	int dimension();

private:
	int dim;
	float* coord;
};

class Matrix
{
public:

	Matrix(std::initializer_list<Vector> list);

	Matrix();

	friend ostream& operator <<(ostream& os, const Matrix& m);

	~Matrix();

	Matrix(const Matrix& other);

	Matrix& operator = (const Matrix& other);

	bool operator ==(const Matrix& other);

	bool operator !=(const Matrix& other);

	Matrix operator +(const Matrix& other);

	void operator += (const Matrix& other);

	Matrix operator -(const Matrix& other);

	void operator -=(const Matrix& other);

	Matrix operator *(const float factor);

	void operator *=(const float factor);

	Matrix operator *(const Vector& v);

	void operator *=(const Vector& v);

	Matrix operator *(const Matrix& other);

	void operator *=(const Matrix& m);

	void transpos();

	Matrix minor(int l, int n);

	float determinant();

	Matrix inverse();

	Matrix solve(Vector& v);

private:

	int columns;
	int rows;

	float** table;
};
