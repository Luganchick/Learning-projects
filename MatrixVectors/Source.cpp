#include <iostream>
#include <stdexcept>
#include"Header.h"


Vector::Vector(std::initializer_list<float> list)
{
	dim = list.size();
	coord = new float[dim];

	int i = 0;
	for (float x : list)
	{
		*(coord + i) = x;
		i++;
	}
}

Vector::Vector()
{
	dim = 0;
}

Vector::~Vector()
{
	delete[] coord;
}

Vector::Vector(const Vector& other)
{
	this->dim = other.dim;
	this->coord = new float[dim];

	for (int i = 0; i < dim; i++)
	{
		*(this->coord + i) = *(other.coord + i);
	}
}

Vector & Vector::operator = (const Vector& other)
{
	delete[] this->coord;
	this->dim = other.dim;
	this->coord = new float[dim];

	for (int i = 0; i < dim; i++)
	{
		*(this->coord + i) = *(other.coord + i);
	}

	return *this;

}

ostream& operator <<(ostream& os, const Vector &v)
{
	for (int i = 0; i < v.dim; i++)
	{
		cout << *(v.coord + i) << endl;
	}

	return os;
}

bool Vector::operator ==(const Vector& other)
{
	if (this->dim != other.dim)
	{
		return false;
	}

	for (int i = 0; i < dim; i++)
	{
		if (*(this->coord + i) != *(other.coord + i))
		{
			return false;
		}
	}
	return true;
}

bool Vector::operator !=(const Vector& other)
{
	if (this->dim != other.dim)
	{
		return true;
	}

	for (int i = 0; i < dim; i++)
	{
		if (*(this->coord + i) != *(other.coord + i))
		{
			return true;
		}
	}
	return false;
}

Vector Vector::operator +(const Vector& other)
{
	if (this->dim == other.dim)
	{
		Vector sum;
		sum.dim = this->dim;
		sum.coord = new float[sum.dim];

		for (int i = 0; i < dim; i++)
		{
			*(sum.coord + i) = *(this->coord + i) + *(other.coord + i);
		}

		return sum;
	}
	else
	{
		throw "You can not summ vectors of different dimensions";

	}
}

void Vector::operator +=(const Vector& other)
{
	*this = *this + other;
}

Vector Vector::operator -(const Vector& other)
{
	if (this->dim == other.dim)
	{
		Vector sum;
		sum.dim = this->dim;
		sum.coord = new float[sum.dim];

		for (int i = 0; i < dim; i++)
		{
			*(sum.coord + i) = *(this->coord + i) - *(other.coord + i);
		}

		return sum;
	}
	else
	{
		throw "You can not subtract vectors of different dimensions";
	}
}

void Vector::operator -=(const Vector& other)
{
	*this = *this - other;
}

Vector Vector::operator *(const float factor)
{
	Vector mult;
	mult.dim = this->dim;
	mult.coord = new float[mult.dim];

	for (int i = 0; i < mult.dim; i++)
	{
		*(mult.coord + i) = *(this->coord + i) * factor;
	}

	return mult;
}
	
void Vector::operator *=(const float factor)
{
	*this = *this * factor;
}

float Vector::operator *(const Vector& other)
{
	float mult = 0;

	if (this->dim == other.dim)
	{
		for (int i = 0; i < this->dim; i++)
		{
			mult += *(this->coord + i) * *(other.coord + i);
		}

		return mult;
	}
	else
	{
		throw "You can not multiply vectors of different dimensions";
	}
}

float Vector::operator [](int index)
{
	if (index <= dim)
	{
		return *(coord + index);
	}
	else
	{
		throw "Index of Vector out of range";
	}
}

int Vector::dimension()
{
	return dim;
}


Matrix::Matrix(std::initializer_list<Vector> list)
{
	rows = list.size();

	for (Vector x : list)
	{
		if (columns)
		{
			if (columns != x.dimension())
			{
				throw "Vectors have different dimension";
			}
		}
		else
		{
			columns = x.dimension();
		}
	}

	table = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		table[i] = new float [columns];
	}

	int i = 0;
	for (Vector x : list)
	{
		for (int j = 0; j < columns; j++)
		{
			table[i][j] = x[j];
		}
		i++;
	}
}

Matrix::Matrix()
{
	rows = 0;
	columns = 0;
}

ostream& operator <<(ostream& os, const Matrix& m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			cout << *(*(m.table + i) + j) << ' ';
		}
		cout << endl;
	}

	return os;
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] * (table + i);
	}
	delete[] table;
}

Matrix::Matrix(const Matrix& other)
{
	columns = other.columns;
	rows = other.rows;
	table = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		*(table + i) = new float[columns];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			table[i][j] = other.table[i][j];
		}
	}
}

Matrix& Matrix::operator = (const Matrix& other)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] * (table + i);
	}
	delete[] table;

	rows = other.rows;
	columns = other.columns;

	table = new float* [rows];
	for (int i = 0; i < rows; i++)
	{
		*(table + i) = new float[columns];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			table[i][j] = other.table[i][j];
		}
	}

	return *this;
}

bool Matrix::operator ==(const Matrix& other)
{
	if (rows == other.rows and columns == other.columns)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (table[i][j] != other.table[i][j])
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Matrix::operator !=(const Matrix& other)
{
	if (*this == other)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Matrix Matrix::operator +(const Matrix& other)
{
	if (columns == other.columns and rows == other.rows)
	{
		Matrix sum;

		sum.rows = rows;
		sum.columns = columns;
		sum.table = new float* [rows];

		for (int i = 0; i < rows; i++)
		{
			*(sum.table + i) = new float[columns];
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				sum.table[i][j] = this->table[i][j] + other.table[i][j];
			}
		}
		return sum;
	}
	else
	{
		throw "Matrices have different dimension";
	}
}

void Matrix::operator += (const Matrix& other)
{
	*this = *this + other;
}

Matrix Matrix::operator -(const Matrix& other)
{
	if (columns == other.columns and rows == other.rows)
	{
		Matrix diff;

		diff.rows = rows;
		diff.columns = columns;
		diff.table = new float* [rows];

		for (int i = 0; i < rows; i++)
		{
			*(diff.table + i) = new float[columns];
		}
		cout << *this;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				diff.table[i][j] = this->table[i][j] - other.table[i][j];
			}
		}
		return diff;
	}
	else
	{
		throw "Matrices have different dimension";
	}
}

void Matrix::operator -=(const Matrix& other)
{
	*this = *this - other;
}

Matrix Matrix::operator *(const float factor)
{
	Matrix mult;
	mult.columns = columns;
	mult.rows = rows;
	mult.table = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		*(mult.table + i) = new float[columns];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mult.table[i][j] = this->table[i][j] * factor;
		}
	}

	return mult;
}

void Matrix::operator *=(const float factor)
{
	*this = *this * factor;
}

Matrix Matrix::operator *(const Vector& v)
{
	Matrix m = { v };
	m.transpos();
	return *this * m;
}

void Matrix::operator *=(const Vector &v)
{
	*this = *this * v;
}

Matrix Matrix::operator *(const Matrix& other)
{
	if (columns = other.rows)
	{
		Matrix mult;
		mult.columns = other.columns;
		mult.rows = rows;
		mult.table = new float* [mult.rows];

		for (int i = 0; i < mult.rows; i++)
		{
			*(mult.table + i) = new float[mult.columns];
		}


		for (int i = 0; i < mult.rows; i++)
		{
			for (int j = 0; j < mult.columns; j++)
			{
				mult.table[i][j] = 0;
			}
		}

		for (int i = 0; i < mult.rows; i++)
		{
			for (int k = 0; k < mult.columns; k++)
			{
				for (int j = 0; j < columns; j++)
				{
					mult.table[i][k] += table[i][j] * other.table[j][k];
				}
			}
		}
		return mult;
	}
	else
	{
		throw "Can't multiply matrices";
	}
}

void Matrix::operator *=(const Matrix& m)
{
	*this = *this * m;
}

void Matrix::transpos()
{
	Matrix t;
	t.columns = this->rows;
	t.rows = this->columns;
	t.table = new float* [t.rows];

	for (int i = 0; i < t.rows; i++)
	{
		*(t.table + i) = new float[t.columns];
	}

	for (int i = 0; i < t.rows; i++)
	{
		for (int j = 0; j < t.columns; j++)
		{
			t.table[i][j] = this->table[j][i];
		}
	}

	*this = t;
}

Matrix Matrix::minor(int l, int n)
{
	if (this->columns == this->rows and this->rows > 1)
	{
		Matrix m;
		m.columns = this->columns - 1;
		m.rows = this->rows - 1;
		m.table = new float* [m.rows];

		for (int i = 0; i < m.rows; i++)
		{
			*(m.table + i) = new float[m.columns];
		}

		for (int i = 0; i < l; i++)
		{
			for (int j = 0; j < n; j++)
			{
				m.table[i][j] = this->table[i][j];
			}
			for (int j = n + 1; j < columns; j++)
			{
				m.table[i][j - 1] = this->table[i][j];
			}
		}

		for (int i = l + 1; i < rows; i++)
		{
			for (int j = 0; j < n; j++)
			{
				m.table[i - 1][j] = this->table[i][j];
			}
			for (int j = n + 1; j < columns; j++)
			{
				m.table[i - 1][j - 1] = this->table[i][j];
			}
		}
		return m;
	}
	else
	{
		throw "Unable to find matrix minor";
	}
}

float Matrix::determinant()
{
	if (this->columns == this->rows)
	{
		if (this->rows == 1)
		{
			return this->table[0][0];
		}
		else
		{
			float res = 0;
			for (int i = 0; i < columns; i++)
			{
				res += (i % 2 == 0 ? 1.0 : (-1.0)) * this->table[0][i] * (this->minor(0, i)).determinant();
			}

			return res;
		}
	}
}

Matrix Matrix::inverse()
{
	if (this->columns == this->columns)
	{
		if (this->determinant() != 0)
		{
			Matrix alg_add;
			alg_add.columns = columns;
			alg_add.rows = rows;
			alg_add.table = new float *[rows];

			for (int i = 0; i < rows; i++)
			{
				*(alg_add.table + i) = new float[columns];
			}

			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < columns; j++)
				{
					alg_add.table[i][j] = (this->minor(i, j)).determinant() *((i + j) % 2 == 0? 1: (-1));
				}
			}
			alg_add.transpos();

			return alg_add * (1 / this->determinant());
		}
		else
		{
			throw "Inverse matrix does not exist";
		}
	}
	else
	{
		throw "Unable to find inverse matrix";
	}
}

Matrix Matrix::solve(Vector& v)
{
	if (this->rows == v.dimension())
	{
		Matrix res;
		float factor;
		res.columns = columns + 1;
		res.rows = rows;
		res.table = new float* [res.rows];

		for (int i = 0; i < rows; i++)
		{
			*(res.table + i) = new float[res.columns];
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				res.table[i][j] = this->table[i][j];
			}
		}

		for (int i = columns; i < columns + 1; i++)
		{

			for (int j = 0; j < rows; j++)
			{
				res.table[j][i] = v[j];
			}
		}

		for (int i = 0; i < columns and i < rows; i++)
		{
			if (res.table[i][i] == 0)
			{
				for (int j = i + 1; j < rows; j++)
				{
					if (res.table[j][i] != 0)
					{
						float var;

						for (int k = i; k < res.columns; k++)
						{
							var = res.table[i][k];
							res.table[i][k] = res.table[j][k];
							res.table[j][k] = var;
						}
					}
				}
				if (res.table[i][i] == 0)
				{
					continue;
				}
			}

			for (int j = i + 1; j < rows; j++)
			{
				factor = (-1) * res.table[j][i] / res.table[i][i];

				for (int k = 0; k < res.columns; k++)
				{
					res.table[j][k] += res.table[i][k] * factor;
				}
			}

		}

		if (rows > columns)
		{
			for (int i = columns + 1; i < rows; i++)
			{
				if (res.table[i][columns + 1] != 0)
				{
					throw "the system has no solutions";
				}
			}
		}

		//reverse Gaus

		for (int i = (rows < columns ? rows : columns) - 1; i >= 0; i--)
		{
			if (res.table[i][i] != 0)
			{
				for (int j = i - 1; j >= 0; j--)
				{
					factor = (-1) * res.table[j][i] / res.table[i][i];

					for (int k = 0; k < res.columns; k++)
					{
						res.table[j][k] += res.table[i][k] * factor;
					}
				}
			}
		}

		for (int i = 0; i < rows; i++)
		{
			bool f = 1;

			for (int j = 0; j < columns; j++)
			{
				if (res.table[i][j] != 0)
				{
					f = 0;
				}
			}

			if (res.table[i][columns] != 0 and f)
			{
				throw "Impossible to solve the system of equations";
			}
		}

		for (int i = 0; i < rows and i < columns; i++)
		{
			factor = (res.table[i][i] != 0 ? 1 / res.table[i][i] : 1);
			
			for (int j = i; j < res.columns; j++)
			{
				res.table[i][j] *= factor;
			}
		}

		return res;
	}
	else
	{
		throw "Impossible to solve the system of equations";
	}
}
