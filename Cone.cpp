#include "Cone.h"

void Cone::setRad(double rad) {
	this->rad = rad;
}
double Cone::getRad() {
	return this->rad;
}


void Cone::setCenter_base(Vector* center_base) {
	this->center_base = center_base;
}
Vector* Cone::getCenter_base() {
	return this->center_base;
}


void Cone::setDirection(Vector* direction) {
	this->direction = direction;
}
Vector* Cone::getDirection() {
	return this->direction;
}


void Cone::setHeight(double height) {
	this->height = height;
}
double Cone::getHeight() {
	return this->height;
}


bool Cone::intersect(Vector* p0, Vector* dir) {

}


bool Cone::intersect_for_shadow(Vector* p0, Vector* dir) {

}


Color* Cone::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) {

}


Cone::Cone(double rad, Vector* center_base, Vector* direction, double height, Vector* kd, Vector* ke, Vector* ka, double shininess) {
	this->rad = rad;
	this->center_base = center_base;
	this->direction = direction;
	this->height = height;
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
	Vector v_temp = *center_base + *direction * height;
	this->vertex = new Vector(v_temp.getCoordinate(0), v_temp.getCoordinate(1), v_temp.getCoordinate(2));
	this->cos = height / sqrt(rad * rad + height * height);
}


Cone::Cone(double rad, Vector* center_base, Vector* direction, double height, Vector* vertex, Vector* kd, Vector* ke, Vector* ka, double shininess) {
	this->rad = rad;
	this->center_base = center_base;
	this->direction = direction;
	this->height = height;
	this->vertex = vertex;
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
	this->cos = height / sqrt(rad * rad + height * height);
}
