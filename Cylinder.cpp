#include "Cylinder.h"

void Cylinder::setRad(double rad) {
	this->rad = rad;
}
double Cylinder::getRad() {
	return this->rad;
}


void Cylinder::setCenter_base(Vector* center_base) {
	this->center_base = center_base;
}
Vector* Cylinder::getCenter_base() {
	return this->center_base;
}


void Cylinder::setDirection(Vector* direction) {
	this->direction = direction;
}
Vector* Cylinder::getDirection() {
	return this->direction;
}


bool Cylinder::intersect(Vector* p0, Vector* dir) {
	Vector w = *dir - (*dir * *this->direction) * *this->direction;
	Vector v = (*p0 - *this->center_base) - (((*p0 - *this->center_base) * *this->direction) * *this->direction);

	double delta, t1, t2;

	double a = w.scalarProd(w);
	double b = v.scalarProd(w);
	double c = v.scalarProd(v) - ((this->rad) * (this->rad));

	delta = (b * b) - 4 * a * c;

    if (delta > 0)
    {
        this->setHasIntersection(true);
        double t = (-b + sqrt(delta)) / (2 * a);;

        if (t < 0)
        {
            this->setHasIntersection(false);
            return false;
        }

        Vector pitemp = (*p0) + ((*dir) * t);
        Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));

        this->setIntersectionPoint(pi);

        Vector distancePiP0Vector = (*p0) - (*pi);
        double distancePiP0 = distancePiP0Vector.getLength();
        this->setP0distance(distancePiP0);

        this->setT(t);

        return true;
    }

    else if (delta == 0)
    {
        if (a == 0) {

        }

        this->setHasIntersection(true);
        t1 = (-b + sqrt(delta)) / (2 * a);
        t2 = (-b - sqrt(delta)) / (2 * a);

        double t = 0;
        if (t1 <= t2) t = t1;
        else          t = t2;

        if (t < 0)
        {
            this->setHasIntersection(false);
            return false;
        }


        Vector pitemp = (*p0) + ((*dir) * t);
        Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));

        this->setIntersectionPoint(pi);

        // 0 <= (P - B) * u <= H
        // 0 <= (pi - center_base) * direction <= height


        Vector distancePiP0Vector = (*p0) - (*pi);
        double distancePiP0 = distancePiP0Vector.getLength();
        this->setP0distance(distancePiP0);

        this->setT(t);

        return true;
    }

    else
    {
        this->setHasIntersection(false);
        return false;
    }
}


bool Cylinder::intersect_for_shadow(Vector* p0, Vector* dir) {

}


Color* Cylinder::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) {

}


Cylinder::Cylinder(double rad, Vector* center_base, Vector* direction, double height, Vector* kd, Vector* ke, Vector* ka, double shininess) {
	this->rad = rad;
	this->center_base = center_base;
	this->direction = direction;
	this->height = height;
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
}
