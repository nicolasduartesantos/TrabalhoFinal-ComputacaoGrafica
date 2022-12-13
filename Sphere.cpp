#include "Object.h"
#include "Sphere.h"
#include "Camera.h"
#include <iostream>
#include <cmath>

void Sphere::setRad(double rad) {
    this->rad = rad;
}

double Sphere::getRad() {
    return this->rad;
}


void Sphere::setCenter(Vector* center) {
    this->center = center;
}
Vector* Sphere::getCenter() {
    return this->center;
}


bool Sphere::intersect(Vector* p0, Vector* dir) {

    Vector w = (*p0) - *(this->center); 

    double delta, t1, t2;
    double a = dir->scalarProd(*dir);
    double b = 2 * (w.scalarProd(*dir));
    double c = w.scalarProd(w) - ((this->rad) * (this->rad));

    delta = (b * b) - 4 * a * c;

    this->setObjectSurface(ObjectSurface::ON_SPHERE);

    if (delta >= 0)
    {
        this->setHasIntersection(true);
        t1 = (-b + sqrt(delta)) / (2 * a);
        t2 = (-b - sqrt(delta)) / (2 * a);

        if (t1 < 0 && t2 < 0)
        {
            this->setHasIntersection(false);
            return false;
        }
        else {

            if (t1 < 0) {
                t = t2;
            }
            else if (t2 < 0) {
                t = t1;
            }
            else {
                if (t1 <= t2) t = t1;
                else          t = t2;
            }
        }
        
        
        Vector pitemp = (*p0) + ( (*dir) * t);
        Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));
        this->setIntersectionPoint(pi);


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


bool Sphere::intersect_for_shadow(Vector* p0, Vector* dir) {

    Vector w = (*p0) - *(this->center);

    double delta, t1, t2;
    double a = dir->scalarProd(*dir);
    double b = 2 * (w.scalarProd(*dir));
    double c = w.scalarProd(w) - ((this->rad) * (this->rad));

    delta = (b * b) - 4 * a * c;

    if (delta >= 0)
    {
        this->setHasIntersectionShadow(true);
        t1 = (-b + sqrt(delta)) / (2 * a);
        t2 = (-b - sqrt(delta)) / (2 * a);

        double t = 0;

        if (t1 < 0 && t2 < 0)
        {
            this->setHasIntersectionShadow(false);
            return false;
        }
        else {

            if (t1 < 0) {
                t = t2;
            }
            else if (t2 < 0) {
                t = t1;
            }
            else {
                if (t1 <= t2) t = t1;
                else          t = t2;
            }
        }

        Vector pitemp = (*p0) + ((*dir) * t);
        Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));

        Vector distancePiP0Vector = (*p0) - (*pi);
        double distancePiP0 = distancePiP0Vector.getLength();
        this->setP0distanceShadow(distancePiP0);
        this->setTShadow(t);

        return true;
    }
    else
    {
        this->setHasIntersectionShadow(false);
        return false;
    }
}


Color* Sphere::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) {

    Vector rgb(0, 0, 0);

    Vector* pi = this->getIntersectionPoint();

    Vector* n = new Vector();
        
    Vector ntemp = (*pi - (*this->center)) / (this->rad);

    n = new Vector(ntemp.getCoordinate(0), ntemp.getCoordinate(1), ntemp.getCoordinate(2));

    return this->RGBtoPaint(lights, objects, p0, dir, environmentLight , n, this);
}


void Sphere::rotX(double a) {
    *this->center = (*this->center).rotX(a);
}

void Sphere::rotY(double a) {
    *this->center = (*this->center).rotY(a);
}

void Sphere::rotZ(double a) {
    *this->center = (*this->center).rotZ(a);
}

void Sphere::translation(double tx, double ty, double tz) {
    *this->center = (*this->center).translation(tx, ty, tz);
}

void Sphere::scaling(double sx, double sy, double sz) {
    *this->center = (*this->center).scaling(sx, sy, sz);
    this->setRad(std::max(std::max(sx, sy), sz) * this->getRad());
}

void Sphere::reflectionXY() {
    *this->center = (*this->center).reflectionXY();
}

void Sphere::reflectionXZ() {
    *this->center = (*this->center).reflectionXZ();
}

void Sphere::reflectionYZ() {
    *this->center = (*this->center).reflectionYZ();
}


void Sphere::doWorldToCamera(Camera* camera) {

    Vector* c = new Vector(camera->worldToCamera(*this->initial_center));
    delete this->getCenter();
    this->setCenter(c);

}


bool Sphere::inside(Vector* p) {
    double d = (*p - *this->center).getLength();

    if (d < this->getRad()) {
        return true;
    }
    else {
        return false;
    }
}


Sphere::Sphere(double rad, Vector* center, Vector* kd, Vector* ke, Vector* ka, double shininess) {
    this->rad = rad;
    this->kd = kd;
    this->ke = ke;
    this->ka = ka;
    this->center = center;
    this->shininess = shininess;
    this->setObjectType(ObjectType::SPHERE);

    this->initial_center = new Vector(*this->center);
}


Sphere::~Sphere() {
    delete this->getCenter();

    delete this->initial_center;
}
