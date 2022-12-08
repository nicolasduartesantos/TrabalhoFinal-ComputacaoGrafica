#include "Object.h"
#include "Sphere.h"
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


void Sphere::doWorldToCamera(Camera* camera) {

    Vector* c = new Vector(camera->worldToCamera(*this->getCenter()));
    delete this->getCenter();
    this->setCenter(c);

}


Sphere::Sphere(double rad, Vector* center, Vector* kd, Vector* ke, Vector* ka, double shininess) {
    this->rad = rad;
    this->kd = kd;
    this->ke = ke;
    this->ka = ka;
    this->center = center;
    this->shininess = shininess;
    this->setObjectType(ObjectType::SPHERE);
}
