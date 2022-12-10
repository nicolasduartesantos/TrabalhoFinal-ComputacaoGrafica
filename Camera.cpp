#include "Camera.h"
#include "Vector.h"

void Camera::setEye(Vector* eye) {
	this->eye = eye;
}
Vector* Camera::getEye() {
	return this->eye;
}


void Camera::setAt(Vector* at) {
	this->at = at;
}
Vector* Camera::getAt() {
	return this->at;
}


void Camera::setUp(Vector* up) {
	this->up = up;
}
Vector* Camera::getUp() {
	return this->up;
}


Vector Camera::worldToCamera(Vector world) {

    Vector k = *this->getEye() - *this->getAt();
    Vector normalK = k / k.getLength();

    Vector ViewUp = *this->getUp() - *this->getEye();

    Vector i = ViewUp.product(normalK);
    Vector normalI = i / i.getLength();

    Vector normalJ = normalK.product(normalI);

    double matrix[4][4] = {
        {normalI.getCoordinate(0), normalI.getCoordinate(1), normalI.getCoordinate(2), -normalI.scalarProd(*this->getEye())},
        {normalJ.getCoordinate(0), normalJ.getCoordinate(1), normalJ.getCoordinate(2), -normalJ.scalarProd(*this->getEye())},
        {normalK.getCoordinate(0), normalK.getCoordinate(1), normalK.getCoordinate(2), -normalK.scalarProd(*this->getEye())},
        {0, 0, 0, 1} };

	double x = ((matrix[0][0] * world.getCoordinate(0)) + (matrix[0][1] * world.getCoordinate(1)) + (matrix[0][2] * world.getCoordinate(2)) + (matrix[0][3] * 1));
	double y = ((matrix[1][0] * world.getCoordinate(0)) + (matrix[1][1] * world.getCoordinate(1)) + (matrix[1][2] * world.getCoordinate(2)) + (matrix[1][3] * 1));
	double z = ((matrix[2][0] * world.getCoordinate(0)) + (matrix[2][1] * world.getCoordinate(1)) + (matrix[2][2] * world.getCoordinate(2)) + (matrix[2][3] * 1));

	Vector ret = Vector(x, y, z);

	return ret;
}


Camera::Camera(Vector* eye, Vector* at, Vector* up) {
	this->eye = eye;
	this->at = at;
	this->up = up;
}


Camera::~Camera() {
	delete this->getEye();
	delete this->getAt();
	delete this->getUp();
}
