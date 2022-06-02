#include <iostream>

class Vector
{
public:

	friend std::ostream& operator <<(std::ostream& os, const Vector& v);

	Vector(std::initializer_list<float> list);

	Vector();

	~Vector();

	Vector(const Vector& other);

	Vector& operator = (const Vector& other);


	friend std::ostream& operator <<(std::ostream& os, const Vector& v);

	bool operator ==(const Vector& other);

	bool operator !=(const Vector& other);

	Vector operator +(const Vector& other);

	void operator +=(const Vector& other);

	Vector operator -(const Vector& other);

	void operator -=(const Vector& other);

	Vector operator *(const float factor);

	void operator *=(const float factor);

	float operator *(const Vector& other);

private:
	int dim;
	float* coord;
};