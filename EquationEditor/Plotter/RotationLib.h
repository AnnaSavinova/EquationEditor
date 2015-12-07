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
	Vector operator -() {return Vector(-x, -y, -z);}
	friend Vector operator + (const Vector& v1, const Vector& v2) {return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);}
	double dot(const Vector& b) const {return x*b.x + y*b.y + x*b.z;}
	Vector cross(const Vector& a) const;
	double norm() const { return sqrt(x*x + y*y + z*z);}
	Vector to_normal() const { return *this*(1 / norm());}
	friend Vector operator * (const Matrix3D& mat, const Vector& vec);
	friend Vector operator * (const Vector& vec, const Matrix3D& mat);
	friend Vector operator * (const Vector& vec, double alpha);
	friend Vector operator * (double alpha, const Vector& vec);
	friend double operator * (const Vector& a, const Vector& b);
	friend Vector operator ^ (const Vector& a, const Vector& b);

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
	Matrix3D(const Vector& a, const Vector& b, const Vector& c, bool are_lines = true);
	Matrix3D(const Matrix3D& copy) {
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				mat[i][j] = copy.mat[i][j];
	}

	void setValue(int i, int j, double value);

	double getValue(int i, int j) const;

	Matrix3D getInversed() const;

	Matrix3D transpose() const;

	//Vector mult(const Vector& vec);

	friend Vector operator * (const Matrix3D& mat, const Vector& vec);
	friend Vector operator * (const Vector& vec, const Matrix3D& mat);

	static Matrix3D I() {
		return Matrix3D(Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1));
	}

protected:
	double mat[3][3];
};


