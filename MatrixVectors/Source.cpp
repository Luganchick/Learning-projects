#include <iostream>
#include <stdexcept>
#include <stdarg.h>

using namespace std;

class Vector
{
	friend class Matrix;
public:


	Vector(std::initializer_list<float> list)
	{
		dim = list.size();
		coord = new float[dim];

		int i = 0;
		for (float x : list)
		{
			*(coord + i) = x;
			i++;
		}
	};

	Vector()
	{
		dim = 0;
	}

	~Vector()
	{
		delete[] coord;
	}

	Vector(const Vector& other)
	{
		this->dim = other.dim;
		this->coord = new float[dim];

		for (int i = 0; i < dim; i++)
		{
			*(this->coord + i) = *(other.coord + i);
		}
	}

	Vector & operator = (const Vector& other)
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

	friend ostream& operator <<(ostream& os, const Vector &v)
	{
		cout << '{' << ' ';
		for (int i = 0; i < v.dim; i++)
		{
			cout << *(v.coord + i) << ' ';
		}
		cout << '}';

		return os;
	}

	bool operator ==(const Vector& other)
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

	bool operator !=(const Vector& other)
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

	Vector operator +(const Vector& other)
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

	void operator +=(const Vector& other)
	{
		*this = *this + other;
	}

	Vector operator -(const Vector& other)
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

	void operator -=(const Vector& other)
	{
		*this = *this - other;
	}

	Vector operator *(const float factor)
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
	
	void operator *=(const float factor)
	{
		*this = *this * factor;
	}

	float operator *(const Vector& other)
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

	float operator [](int index)
	{
		if (index <= dim)
		{
			return *(coord + index);
		}
		else
		{
			//Доделать
		}
	}

	int dimension()
	{
		return dim;
	}

	void set_dim(int new_dim)
	{
		if (dim == 0)
		{
			dim = new_dim;
			coord = new float[dim];
		}
	}

private:
	int dim;
	float* coord;
};

class Matrix
{

public:
	Matrix(std::initializer_list<Vector> list)
	{
		rows = list.size();

		for (Vector x : list)
		{
			if (columns)
			{
				if (columns != x.dimension())
				{
					// Доделать
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

	Matrix()
	{
		rows = 0;
		columns = 0;
	}

	friend ostream& operator <<(ostream& os, const Matrix& m)
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

	~Matrix()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] * (table + i);
		}
		delete[] table;
	}

	Matrix(const Matrix& other)
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

	Matrix& operator = (const Matrix& other)
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

	bool operator ==(const Matrix& other)
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

	bool operator !=(const Matrix& other)
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

	Matrix operator +(const Matrix& other)
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
			//Доделать
		}
	}

	void operator += (const Matrix& other)
	{
		*this = *this + other;
	}

	Matrix operator -(const Matrix& other)
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
			//Доделать
		}
	}

	void operator -=(const Matrix& other)
	{
		*this = *this - other;
	}

	Matrix operator *(const float factor)
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

	void operator *=(const float factor)
	{
		*this = *this * factor;
	}

	Vector operator *(Vector& v)
	{
		
	}

	Matrix operator *(Matrix& other)
	{
		if (columns = other.rows)
		{
			Matrix mult;
			mult.columns = other.columns;
			mult.rows = rows;
			mult.table = new float* [mult.rows];

			for (int i = 0; i < rows; i++)
			{
				*(mult.table) = new float[mult.columns];
			}

			for (int i = 0; i < mult.rows; i++)
			{
				for (int j = 0; j < mult.columns; j++)
				{

				}
			}
		}
		else
		{
			// Доделать
		}
	}

private:
	int columns;
	int rows;

	float** table;
};



int main()
{
	Matrix d = { {1, 4}, {2, 5}, {3, 6} };
	Vector a = { 1, 0 };
	Vector b;

	b = d * a;

	cout << d << endl << '*' << endl << a << endl << '=' << endl << b;
}