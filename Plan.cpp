#include "Object.h"
#include "Vector.h"
#include <iostream>
#include "Plan.h"
#include <cmath>

void Plan::setP_PI(Vector* p_pi){
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


Color* Plan::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) {

    Vector rgb(0, 0, 0);

    //Vector* pi = this->getIntersectionPoint();

	Vector pitemp = (*p0) + ((*dir) * t);
	Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));



    Vector v(0, 0, 0); Vector l(0, 0, 0); Vector r(0, 0, 0);

    v = (* dir * (-1)) / (dir->getLength());


    for (int i = 0; i < lights.size(); i++) {

		Vector* pf = (lights[i])->getCoordinate();
		
		l = (*pf - *pi);

		l = l / (l.getLength());


        bool hasShadow = this->hasShadow(objects, pi, l, pf);


        if (!hasShadow) {

            r = (*this->normal * (2 * (l.scalarProd(*this->normal)))) - l;

            double f_diffuse = std::max(0.0, (l.scalarProd(*this->normal)));
            double f_speculated = std::pow(std::max(0.0, (r.scalarProd(v))), this->shininess);

            Vector i_diffuse = (*lights[i]->getIntensity()) * (*this->kd) * f_diffuse;
            Vector i_speculated = (*lights[i]->getIntensity()) * (*this->ke) * f_speculated;

            rgb = rgb + i_diffuse + i_speculated;
			
        }
    }
	
    if (environmentLight != nullptr) {
        Vector i_environment = (*environmentLight) * (*this->ka);
        rgb = rgb + i_environment;
    }

	double cor_max = std::max(std::max(rgb.getCoordinate(0), rgb.getCoordinate(1)), rgb.getCoordinate(2));
	if (cor_max > 1) {
		rgb = rgb / cor_max;
	}
	
    Color* result = new Color(rgb.getCoordinate(0) * 255, rgb.getCoordinate(1) * 255, rgb.getCoordinate(2) * 255, 255);
    return result;
}


Plan::Plan(Vector* p_pi, Vector* normal, Vector* kd, Vector* ke, Vector* ka, double shininess){
    this->p_pi = p_pi;
    this->normal = normal;
    this->kd = kd;
    this->ke = ke;
	this->ka = ka;
    this->shininess = shininess;
    this->setObjectType(ObjectType::PLAN);
}
