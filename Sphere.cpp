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

        double t = 0;
        if (t1 <= t2) t = t1;
        else          t = t2;

        if (t < 0)
        {
            this->setHasIntersection(false);
            return false;
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
        if (t1 <= t2) t = t1;
        else          t = t2;

        if (t < 0)
        {
            this->setHasIntersectionShadow(false);
            return false;
        }

        Vector pitemp = (*p0) + ((*dir) * t);
        Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));

        Vector distancePiP0Vector = (*p0) - (*pi);
        double distancePiP0 = distancePiP0Vector.getLength();
        this->setP0distanceShadow(distancePiP0);

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

    //Vector* pi = this->getIntersectionPoint();

    Vector pitemp = (*p0) + ((*dir) * t);
    Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));


    Vector n(0, 0, 0); Vector v(0, 0, 0); Vector l(0, 0, 0); Vector r(0, 0, 0);
        
    n = (*pi - (*this->center)) / (this->rad);

    v = (*dir * (-1)) / (dir->getLength());


    for (int i = 0; i < lights.size(); i++) {

        Vector* pf = lights[i]->getCoordinate();

        l = (*pf - *pi);
        l = l / (l.getLength());


        bool hasShadow = this->hasShadow(objects, pi, l, pf);

        //if (!hasShadow) {

            r = (n * (2 * (l.scalarProd(n)))) - l;

            double f_diffuse = std::max(0.0, (l.scalarProd(n)));
            double f_speculated = std::pow(std::max(0.0, (r.scalarProd(v))), this->shininess);

            Vector i_diffuse = (*(lights[i]->getIntensity())) * (*this->kd) * f_diffuse;
            Vector i_speculated = (*lights[i]->getIntensity()) * (*this->ke) * f_speculated;
            
            rgb = rgb + i_diffuse + i_speculated;

            //std::cout << i_speculated.getCoordinate(0) << ", " << i_speculated.getCoordinate(1) << ", " << i_speculated.getCoordinate(2) << "\n";

            //std::cout << (l.scalarProd(n)) << "\n";
        //}
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


Sphere::Sphere(double rad, Vector* kd, Vector* ke, Vector* ka, Vector* center, double shininess) {
    this->rad = rad;
    this->kd = kd;
    this->ke = ke;
    this->ka = ka;
    this->center = center;
    this->shininess = shininess;
    this->setObjectType(ObjectType::SPHERE);
}
