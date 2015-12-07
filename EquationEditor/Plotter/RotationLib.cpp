#include "RotationLib.h""
#include "math.h"


Vector::Vector(): x(1), y(1), z(1) {}

Vector::Vector( double inputX, double inputY, double inputZ ): x(inputX), y(inputY), z(inputZ) {}

void Vector::initialize( double inputX, double inputY, double inputZ ) {
	x = inputX;
	y = inputY;
	z = inputZ;
}
void Vector::normalize() {
	double norm = sqrt( x*x + y*y + z*z );
	x = x / norm;
	y = y / norm;
	z = z / norm;
}
void Vector::operator =( const Vector& vect ) {
	x = vect.x;
	y = vect.y;
	z = vect.z;
}


Quaternion::Quaternion(): w(0), x(0), y(0), z(1) {}

Quaternion::Quaternion( double inputAngle, const Vector& vect ) {
	double vnorm = sqrt( vect.x*vect.x + vect.y*vect.y + vect.z*vect.z );
	w = cos( inputAngle / 180 / 2 * M_PI );
	x = sin( inputAngle / 180 / 2 * M_PI ) * vect.x / vnorm;
	y = sin( inputAngle / 180 / 2 * M_PI ) * vect.y / vnorm;
	z = sin( inputAngle / 180 / 2 * M_PI ) * vect.z / vnorm;
}
Quaternion::Quaternion( double inputAngle, double inputX, double inputY, double inputZ ) {
	double vnorm = sqrt( inputX*inputX + inputY*inputY + inputZ*inputZ );
	w = cos( inputAngle / 180 / 2 * M_PI );
	x = sin( inputAngle / 180 / 2 * M_PI ) * inputX / vnorm;
	y = sin( inputAngle / 180 / 2 * M_PI ) * inputY / vnorm;
	z = sin( inputAngle / 180 / 2 * M_PI ) * inputZ / vnorm;
}
Vector Quaternion::makeRotation( const Vector& vect ) {
	// Создаем кватернион соответсвующий получаемому вектору
	Quaternion start;
	start.x = vect.x;
	start.y = vect.y;
	start.z = vect.z;
	start.w = 0;
	Quaternion inversed = this->getInversedQuaternion();
	Quaternion res = (*this) * start;
	res = res * inversed;
	double norm = sqrt( res.x*res.x + res.y*res.y + res.z*res.z );
	return Vector( res.x/norm, res.y/norm, res.z/norm );
}
void Quaternion::initialize( double inputAngle, const Vector& vect ) {
	double vnorm = sqrt( vect.x*vect.x + vect.y*vect.y + vect.z*vect.z );
	w = cos( inputAngle / 180 / 2 * M_PI );
	x = sin( inputAngle / 180 / 2 * M_PI ) * vect.x / vnorm;
	y = sin( inputAngle / 180 / 2 * M_PI ) * vect.y / vnorm;
	z = sin( inputAngle / 180 / 2 * M_PI ) * vect.z / vnorm;
}
void Quaternion::initialize( double inputAngle, double inputX, double inputY, double inputZ ) {
	double vnorm = sqrt( inputX*inputX + inputY*inputY + inputZ*inputZ );
	w = cos( inputAngle / 180 / 2 * M_PI );
	x = sin( inputAngle / 180 / 2 * M_PI ) * inputX / vnorm;
	y = sin( inputAngle / 180 / 2 * M_PI ) * inputY / vnorm;
	z = sin( inputAngle / 180 / 2 * M_PI ) * inputZ / vnorm;
}
void Quaternion::operator =( const Quaternion& quat ) {
	w = quat.w;
	x = quat.x;
	y = quat.y;
	z = quat.z;
}
Quaternion Quaternion::getInversedQuaternion() {
	return Quaternion( w, -x, -y, -z );
}
Quaternion Quaternion::operator *( const Quaternion& quat ) { 
	
	Quaternion q;
	q.w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
	q.x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
	q.y = w * quat.y - x * quat.z + y * quat.w + z * quat.x;
	q.z = w * quat.z + x * quat.y - y * quat.x + z * quat.w;
	return q;
} 

Matrix3D::Matrix3D(const Vector& a, const Vector& b, const Vector& c, bool are_lines) {
	if (are_lines) {
		mat[0][0] = a.x;
		mat[0][1] = a.y;
		mat[0][2] = a.z;
		mat[1][0] = b.x;
		mat[1][1] = b.y;
		mat[1][2] = b.z;
		mat[2][0] = c.x;
		mat[2][1] = c.y;
		mat[2][2] = c.z;
	}
	else {
		mat[0][0] = a.x;
		mat[1][0] = a.y;
		mat[2][0] = a.z;
		mat[0][1] = b.x;
		mat[1][1] = b.y;
		mat[2][1] = b.z;
		mat[0][2] = c.x;
		mat[1][2] = c.y;
		mat[2][2] = c.z;
	}
}

void Matrix3D::setValue(int i, int j, double value) {
	if (i < 3 && j < 3 && i > 0 && j > 0) {
		mat[i][j] = value;
		return;
	}
	throw std::exception("Index error");
}

double Matrix3D::getValue(int i, int j) const {
	if (i < 3 && j < 3 && i > 0 && j > 0) {
		return mat[i][j];
	}
	throw std::exception("Index error");
}

Matrix3D Matrix3D::getInversed() const  {
	Matrix3D result;

	double det = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) -
		mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
		mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);

	double invdet = 1 / det;

	result.mat[0][ 0] = (mat[1][ 1] * mat[2][ 2] - mat[2][ 1] * mat[1][ 2]) * invdet;
	result.mat[0][ 1] = (mat[0][ 2] * mat[2][ 1] - mat[0][ 1] * mat[2][ 2]) * invdet;
	result.mat[0][ 2] = (mat[0][ 1] * mat[1][ 2] - mat[0][ 2] * mat[1][ 1]) * invdet;
	result.mat[1][ 0] = (mat[1][ 2] * mat[2][ 0] - mat[1][ 0] * mat[2][ 2]) * invdet;
	result.mat[1][ 1] = (mat[0][ 0] * mat[2][ 2] - mat[0][ 2] * mat[2][ 0]) * invdet;
	result.mat[1][ 2] = (mat[1][ 0] * mat[0][ 2] - mat[0][ 0] * mat[1][ 2]) * invdet;
	result.mat[2][ 0] = (mat[1][ 0] * mat[2][ 1] - mat[2][ 0] * mat[1][ 1]) * invdet;
	result.mat[2][ 1] = (mat[2][ 0] * mat[0][ 1] - mat[0][ 0] * mat[2][ 1]) * invdet;
	result.mat[2][ 2] = (mat[0][ 0] * mat[1][ 1] - mat[1][ 0] * mat[0][ 1]) * invdet;

	return result;
}

Matrix3D Matrix3D::transpose() const  {
	Matrix3D result;

	result.mat[0][0] = mat[0][0];
	result.mat[0][1] = mat[1][0];
	result.mat[0][2] = mat[2][0];
	result.mat[1][0] = mat[1][1];
	result.mat[1][1] = mat[2][1];
	result.mat[1][2] = mat[3][1];
	result.mat[2][0] = mat[1][2];
	result.mat[2][1] = mat[2][2];
	result.mat[2][2] = mat[3][2];

	return result;
}

//Vector Matrix3D::mult( const Vector& vec ) {
//	Vector result;
//	result.x = mat[0][0] * vec.x + mat[0][1] * vec.y + mat[0][2] * vec.z;
//	result.y = mat[1][0] * vec.x + mat[1][1] * vec.y + mat[1][2] * vec.z;
//	result.z = mat[2][0] * vec.x + mat[2][1] * vec.y + mat[2][2] * vec.z;
//	return result;
//}

Vector operator * (const Matrix3D& mat, const Vector& vec) {
	Vector result;
	result.x = mat.mat[0][0] * vec.x + mat.mat[0][1] * vec.y + mat.mat[0][2] * vec.z;
	result.y = mat.mat[1][0] * vec.x + mat.mat[1][1] * vec.y + mat.mat[1][2] * vec.z;
	result.z = mat.mat[2][0] * vec.x + mat.mat[2][1] * vec.y + mat.mat[2][2] * vec.z;
	return result;
}

Vector operator * (const Vector& vec, const Matrix3D& mat) {
	Vector result;
	result.x = mat.mat[0][0] * vec.x + mat.mat[1][0] * vec.y + mat.mat[2][0] * vec.z;
	result.y = mat.mat[0][1] * vec.x + mat.mat[1][1] * vec.y + mat.mat[2][1] * vec.z;
	result.z = mat.mat[0][2] * vec.x + mat.mat[1][2] * vec.y + mat.mat[2][2] * vec.z;
	return result;
}

Vector operator * (const Vector& vec, double alpha) {
	Vector result;
	result.x = alpha * vec.x;
	result.y = alpha * vec.y;
	result.z = alpha * vec.z;
	return result;
}

Vector operator * (double alpha, const Vector& vec) {
	Vector result;
	result.x = alpha * vec.x;
	result.y = alpha * vec.y;
	result.z = alpha * vec.z;
	return result;
}

Vector Vector::cross(const Vector& a) const  {
	Vector result;
	result.x = a.y * z - y * a.z;
	result.y = a.z * x - z * a.x;
	result.z = a.x * y - x * a.y;
	return result;
}

Vector operator ^ (const Vector& a, const Vector& b) {
	return a.cross(b);
}

double operator * (const Vector& a, const Vector& b) {
	return a.dot(b);
}