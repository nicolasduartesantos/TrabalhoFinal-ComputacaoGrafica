
#include <vector>
#include "Vector.h"


Vector::Vector() {
	this->coordinates[0] = 0;
	this->coordinates[1] = 0;
	this->coordinates[2] = 0;
}


Vector::Vector(double x, double y, double z) {
	this->coordinates[0] = x;
	this->coordinates[1] = y;
	this->coordinates[2] = z;
}


double Vector::scalarProd(Vector b) {
	double product = 0;
	for (int i = 0; i < 3; i++)
	{
		product = product + ((this->coordinates[i]) * (b.coordinates[i]));
	}
	return product;
}

Vector Vector::product(Vector b) {
	Vector x(
		this->coordinates[1] * b.coordinates[2] - this->coordinates[2] * b.coordinates[1],
		this->coordinates[2] * b.coordinates[0] - this->coordinates[0] * b.coordinates[2],
		this->coordinates[0] * b.coordinates[1] - this->coordinates[1] * b.coordinates[0]
	);

	return x;
}


void Vector::setCoordinate(int index, int x) {
	this->coordinates[index] = x;
}

double Vector::getCoordinate(int index) {
	return this->coordinates[index];
}


double Vector::getLength() {
	return (sqrt(this->scalarProd(*this)));
}




bool Vector::operator == (const Vector& b) {
	return (this->coordinates[0] == b.coordinates[0] && this->coordinates[1] == b.coordinates[1] && this->coordinates[2] == b.coordinates[2]);
}


Vector Vector::operator + (const Vector& b) {
	Vector x (
		this->coordinates[0] + b.coordinates[0],
		this->coordinates[1] + b.coordinates[1],
		this->coordinates[2] + b.coordinates[2]
		);

	return x;
}


Vector Vector::operator - (const Vector& b) {
	Vector x(
		this->coordinates[0] - b.coordinates[0],
		this->coordinates[1] - b.coordinates[1],
		this->coordinates[2] - b.coordinates[2]);

    return x;
}


Vector Vector::operator * (const Vector& b) {
	Vector x(
		this->coordinates[0] * b.coordinates[0],
		this->coordinates[1] * b.coordinates[1],
		this->coordinates[2] * b.coordinates[2]
		);

	return x;
}


Vector Vector::operator / (const Vector& b) {
	Vector x(
		this->coordinates[0] / b.coordinates[0],
		this->coordinates[1] / b.coordinates[1],
		this->coordinates[2] / b.coordinates[2]
		);

	return x;
}


Vector Vector::operator * (const double& b) {
	Vector x(
		this->coordinates[0] * b,
		this->coordinates[1] * b,
		this->coordinates[2] * b
	);

	return x;
}


Vector Vector::operator / (const double& b) {
	Vector x(
		this->coordinates[0] / b,
		this->coordinates[1] / b,
		this->coordinates[2] / b
	);

	return x;
}


// ROTAÇÃO
Vector Vector::rotX(double a) {

	double matrix[4][4] = { {1, 0, 0, 0}, {0, cos(a), -sin(a), 0}, {0, sin(a), cos(a), 0}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}


Vector Vector::rotY(double a) {
	double matrix[4][4] = { {cos(a), 0, sin(a), 0}, {0, 1, 0, 0}, {-sin(a), 0, cos(a), 0}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}


Vector Vector::rotZ(double a) {
	double matrix[4][4] = { {cos(a), -sin(a), 0, 0}, {sin(a), cos(a), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}


// TRANSLAÇÃO
Vector Vector::translation(double tx, double ty, double tz) {

	double matrix[4][4] = { {1, 0, 0, tx}, {0, 1, 0, ty}, {0, 0, 1, tz}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}


// ESCALA
Vector Vector::scaling(double sx, double sy, double sz) {

	double matrix[4][4] = { {sx, 0, 0, 0}, {0, sy, 0, 0}, {0, 0, sz, 0}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}


// CISALHAMENTO
Vector Vector::shearingYX(double a) {
	double matrix[4][4] = { {1, tan(a), 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}

Vector Vector::shearingXY(double a) {
	double matrix[4][4] = { {1, 0, 0, 0}, {tan(a), 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}

Vector Vector::shearingYZ(double a) {
	double matrix[4][4] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, tan(a), 1, 0}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}

Vector Vector::shearingZY(double a) {
	double matrix[4][4] = { {1, 0, 0, 0}, {0, 1, tan(a), 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}

Vector Vector::shearingXZ(double a) {
	double matrix[4][4] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {tan(a), 0, 1, 0}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}

Vector Vector::shearingZX(double a) {
	double matrix[4][4] = { {1, 0, tan(a), 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };

	double x = (matrix[0][0] * this->coordinates[0]) + (matrix[0][1] * this->coordinates[1]) + (matrix[0][2] * this->coordinates[2]) + (matrix[0][3] * 1);
	double y = (matrix[1][0] * this->coordinates[0]) + (matrix[1][1] * this->coordinates[1]) + (matrix[1][2] * this->coordinates[2]) + (matrix[1][3] * 1);
	double z = (matrix[2][0] * this->coordinates[0]) + (matrix[2][1] * this->coordinates[1]) + (matrix[2][2] * this->coordinates[2]) + (matrix[2][3] * 1);

	Vector ret = Vector(x, y, z);

	return ret;
}


// REFLEXÃO
Vector Vector::reflectionXY() {
	double matrix[4][4] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, -1, 0}, {0, 0, 0, 1} };

	Vector ret = Vector((matrix[0][0] * this->getCoordinate(0) + matrix[0][1] * this->getCoordinate(1) + matrix[0][2] * this->getCoordinate(2) + matrix[0][3] * 1),
		(matrix[1][0] * this->getCoordinate(0) + matrix[1][1] * this->getCoordinate(1) + matrix[1][2] * this->getCoordinate(2) + matrix[1][3] * 1),
		(matrix[2][0] * this->getCoordinate(0) + matrix[2][1] * this->getCoordinate(1) + matrix[2][2] * this->getCoordinate(2) + matrix[2][3] * 1));

	return ret;
}

Vector Vector::reflectionXZ() {
	double matrix[4][4] = { {1, 0, 0, 0}, {0, -1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };

	Vector ret = Vector((matrix[0][0] * this->getCoordinate(0) + matrix[0][1] * this->getCoordinate(1) + matrix[0][2] * this->getCoordinate(2) + matrix[0][3] * 1),
		(matrix[1][0] * this->getCoordinate(0) + matrix[1][1] * this->getCoordinate(1) + matrix[1][2] * this->getCoordinate(2) + matrix[1][3] * 1),
		(matrix[2][0] * this->getCoordinate(0) + matrix[2][1] * this->getCoordinate(1) + matrix[2][2] * this->getCoordinate(2) + matrix[2][3] * 1));

	return ret;
}

Vector Vector::reflectionYZ() {
	double matrix[4][4] = { {-1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };

	Vector ret = Vector((matrix[0][0] * this->getCoordinate(0) + matrix[0][1] * this->getCoordinate(1) + matrix[0][2] * this->getCoordinate(2) + matrix[0][3] * 1),
		(matrix[1][0] * this->getCoordinate(0) + matrix[1][1] * this->getCoordinate(1) + matrix[1][2] * this->getCoordinate(2) + matrix[1][3] * 1),
		(matrix[2][0] * this->getCoordinate(0) + matrix[2][1] * this->getCoordinate(1) + matrix[2][2] * this->getCoordinate(2) + matrix[2][3] * 1));

	return ret;
}
