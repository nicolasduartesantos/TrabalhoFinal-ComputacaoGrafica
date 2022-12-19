#include "Object.h"
#include "Vector.h"
#include "Camera.h"
#include <iostream>
#include "Plan.h"
#include <cmath>

void Plan::setP_PI(Vector* p_pi) {
	this->p_pi = p_pi;
}

Vector* Plan::getP_PI() {
	return this->p_pi;
}


void Plan::setNormal(Vector* normal) {
	this->normal = normal;
}

Vector* Plan::getNormal() {
	return this->normal;
}


bool Plan::intersect(Vector* p0, Vector* dir) {

	Vector w = *p0 - *(this->p_pi);

	double t;
	this->setObjectSurface(ObjectSurface::ON_PLAN);

	double drn = dir->scalarProd(*this->normal);

	if (drn == 0) {
		this->setHasIntersection(false);
		return false;
	}

	t = (-(w.scalarProd(*this->normal)) / drn);

	if (t < 0)
	{
		this->setHasIntersection(false);
		return false;
	}
	else
	{

		this->setHasIntersection(true);
		Vector pitemp = (*p0) + ((*dir) * t);
		Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));

		this->setIntersectionPoint(pi);

		Vector distancePiP0Vector = (*p0) - (*pi);
		double distancePiP0 = distancePiP0Vector.getLength();
		this->setP0distance(distancePiP0);

		this->setT(t);

		return true;
	}
}


bool Plan::intersect_for_shadow(Vector* p0, Vector* dir) {

	Vector w = *p0 - *(this->p_pi);

	double t;

	double drn = dir->scalarProd(*this->normal);

	if (drn == 0) {
		this->setHasIntersectionShadow(false);
		return false;
	}

	t = -(w.scalarProd(*this->normal) / drn);

	if (t < 0)
	{
		this->setHasIntersectionShadow(false);
		return false;
	}
	else
	{
		this->setHasIntersectionShadow(true);
		Vector pitemp = (*p0) + ((*dir) * t);
		Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));

		Vector distancePiP0Vector = (*p0) - (*pi);
		double distancePiP0 = distancePiP0Vector.getLength();
		this->setP0distanceShadow(distancePiP0);

		this->setTShadow(t);

		return true;
	}
}


Color* Plan::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Environment* environmentLight) {

	return RGBtoPaint(lights, objects, p0, dir, environmentLight, this->normal, this);

}


void Plan::rotX(double a) {

	double x = this->initial_p_pi->getCoordinate(0);
	double y = this->initial_p_pi->getCoordinate(1);
	double z = this->initial_p_pi->getCoordinate(2);

	this->translation(-(this->initial_p_pi->getCoordinate(0)), -(this->initial_p_pi->getCoordinate(1)), -(this->initial_p_pi->getCoordinate(2)));

	*this->initial_p_pi = (*this->initial_p_pi).rotX(a);
	*this->initial_normal = (*this->initial_normal).rotX(a);

	this->translation(x, y, z);
}

void Plan::rotY(double a) {
	double x = this->initial_p_pi->getCoordinate(0);
	double y = this->initial_p_pi->getCoordinate(1);
	double z = this->initial_p_pi->getCoordinate(2);

	this->translation(-(this->initial_p_pi->getCoordinate(0)), -(this->initial_p_pi->getCoordinate(1)), -(this->initial_p_pi->getCoordinate(2)));

	*this->initial_p_pi = (*this->initial_p_pi).rotY(a);
	*this->initial_normal = (*this->initial_normal).rotY(a);

	this->translation(x, y, z);
}

void Plan::rotZ(double a) {
	double x = this->initial_p_pi->getCoordinate(0);
	double y = this->initial_p_pi->getCoordinate(1);
	double z = this->initial_p_pi->getCoordinate(2);

	this->translation(-(this->initial_p_pi->getCoordinate(0)), -(this->initial_p_pi->getCoordinate(1)), -(this->initial_p_pi->getCoordinate(2)));

	*this->initial_p_pi = (*this->initial_p_pi).rotZ(a);
	*this->initial_normal = (*this->initial_normal).rotZ(a);

	this->translation(x, y, z);
}

void Plan::translation(double tx, double ty, double tz) {
	*this->initial_p_pi = (*this->initial_p_pi).translation(tx, ty, tz);
}

void Plan::scaling(double sx, double sy, double sz) { }

void Plan::reflectionXY() {
	double x = this->initial_p_pi->getCoordinate(0);
	double y = this->initial_p_pi->getCoordinate(1);
	double z = this->initial_p_pi->getCoordinate(2);

	this->translation(-(this->initial_p_pi->getCoordinate(0)), -(this->initial_p_pi->getCoordinate(1)), -(this->initial_p_pi->getCoordinate(2)));

	*this->initial_p_pi = (*this->initial_p_pi).reflectionXY();
	*this->initial_normal = (*this->initial_normal).reflectionXY();

	this->translation(x, y, z);
}

void Plan::reflectionXZ() {
	double x = this->initial_p_pi->getCoordinate(0);
	double y = this->initial_p_pi->getCoordinate(1);
	double z = this->initial_p_pi->getCoordinate(2);

	this->translation(-(this->initial_p_pi->getCoordinate(0)), -(this->initial_p_pi->getCoordinate(1)), -(this->initial_p_pi->getCoordinate(2)));

	*this->initial_p_pi = (*this->initial_p_pi).reflectionXZ();
	*this->initial_normal = (*this->initial_normal).reflectionXZ();

	this->translation(x, y, z);
}

void Plan::reflectionYZ() {
	double x = this->initial_p_pi->getCoordinate(0);
	double y = this->initial_p_pi->getCoordinate(1);
	double z = this->initial_p_pi->getCoordinate(2);

	this->translation(-(this->initial_p_pi->getCoordinate(0)), -(this->initial_p_pi->getCoordinate(1)), -(this->initial_p_pi->getCoordinate(2)));

	*this->initial_p_pi = (*this->initial_p_pi).reflectionYZ();
	*this->initial_normal = (*this->initial_normal).reflectionYZ();

	this->translation(x, y, z);
}


void Plan::doWorldToCamera(Camera* camera) {

	Vector n = camera->worldToCamera(*this->initial_normal) - camera->worldToCamera(Vector(0, 0, 0));
	Vector* n_Normalized = new Vector(n / n.getLength());
	delete this->getNormal();
	this->setNormal(n_Normalized);

	Vector* ppi = new Vector(camera->worldToCamera(*this->initial_p_pi));
	delete this->getP_PI();
	this->setP_PI(ppi);

}


Plan::Plan(Vector* p_pi, Vector* normal, Vector* kd, Vector* ke, Vector* ka, double shininess) {
	this->p_pi = p_pi;
	this->normal = normal;
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
	this->setObjectType(ObjectType::PLAN);

	this->initial_p_pi = new Vector(*this->p_pi);
	this->initial_normal = new Vector(*this->normal);
}


Plan::Plan() { }


Plan::~Plan() {
	delete this->getP_PI();
	delete this->getNormal();

	delete this->initial_p_pi;
	delete this->initial_normal;
}