#pragma once
#include <exception>
#include <cmath>
#define M_PI       3.1415926535897932384

class Matrix3D;

class Vector{
public:	
	Vector();
	Vector( double inputX, double inputY, double inputZ );
	void initialize( double inputX, double inputY, double inputZ );
	void normalize();
	void operator =( const Vector& vect );
	Vector operator -() {return Vector(-this->x, -this->y, -this->z);}
	friend Vector operator + (const Vector v1, const Vector v2) {return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);}
	double dot(Vector b) {return x*b.x + y*b.y + x*b.z;}
	Vector cross(Vector a);
	double norm() { return sqrt(x*x + y*y + z*z);}
	Vector to_normal() { return *this*(1 / this->norm());}
	friend Vector operator * (Matrix3D mat, Vector vec);
	friend Vector operator * (Vector vec, Matrix3D mat);
	friend Vector operator * (Vector vec, double alpha);
	friend Vector operator * (double alpha, Vector vec);
	friend double operator * (Vector a, Vector b);
	friend Vector operator ^ (Vector a, Vector b);
	double x;
	double y;
	double z;
};

// Все кватернионы нормализованные
class Quaternion {
public:
	Quaternion();
	Quaternion( double inputW, const Vector& vect );
	Quaternion( double inputW, double inputAngle, double inputY, double inputZ );
	Quaternion getInversedQuaternion();
	// Получает вектор который нужно повернуть на угол и вокруг оси задаваемой кватернионом 
	Vector makeRotation( const Vector& vect );
	void initialize( double inputW, const Vector& vect );
	void Quaternion::initialize( double inputAngle, double inputX, double inputY, double inputZ );
	void operator =( const Quaternion& quat );
	Quaternion operator *( const Quaternion& quat );
	double w;
	double x;
	double y;
	double z;
};

class Matrix3D {
public:
	Matrix3D() {};
	~Matrix3D() {};
	Matrix3D(Vector a, Vector b, Vector c, bool are_lines = true);
	Matrix3D(const Matrix3D& copy) {
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				mat[i][j] = copy.mat[i][j];
	}

	void setValue(int i, int j, double value);

	double getValue(int i, int j) const;

	Matrix3D getInversed();

	Matrix3D transpose();

	//Vector mult(Vector vec);

	friend Vector operator * (Matrix3D mat, Vector vec);
	friend Vector operator * (Vector vec, Matrix3D mat);

	static Matrix3D I() {
		return Matrix3D(Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1));
	}

protected:
	double mat[3][3];
};


