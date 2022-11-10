
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


void Vector::setCoordinate(int index, int x) {
	this->coordinates[index] = x;
}

double Vector::getCoordinate(int index) {
	return this->coordinates[index];
}


double Vector::getLength() {
	return (sqrt(this->scalarProd(*this)));
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
