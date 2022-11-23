#include "Cylinder.h"
#include "Object.h"
#include "Vector.h"
#include <iostream>
#include <cmath>

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
    // VERIFICANDO INTERSEÇÃO BASE OU TOPO

    double verParallel = dir->scalarProd(*this->direction);

    double tBase;
    double tTop;

    Vector* piBase = new Vector();
    Vector* piTop = new Vector();

    double distancePiBaseP0;
    double distancePiTopP0;

    bool interceptsBase = false;
    bool interceptsTop = false;

    if (verParallel != 0) {
        tBase = (((*p0 - *this->center_base).scalarProd(*this->direction)) / verParallel) * (-1);

        Vector center_top = *this->center_base + *this->direction * this->height;
        tTop = (((*p0 - center_top).scalarProd(*this->direction)) / verParallel) * (-1);

        Vector piBaseTemp = *p0 + *dir * tBase;
        piBase = new Vector(piBaseTemp.getCoordinate(0), piBaseTemp.getCoordinate(1), piBaseTemp.getCoordinate(2));
        Vector piTopTemp = *p0 + *dir * tTop;
        piTop = new Vector(piTopTemp.getCoordinate(0), piTopTemp.getCoordinate(1), piTopTemp.getCoordinate(2));

        distancePiBaseP0 = (*piBase - *p0).getLength();
        distancePiTopP0 = (*piTop - *p0).getLength();

        if ((*piBase - *this->center_base).getLength() <= this->rad) {
            interceptsBase = true;
        }

        if ((*piTop - center_top).getLength() <= this->rad) {
            interceptsTop = true;
        }
    }


    if (interceptsBase && interceptsTop) {
        this->setHasIntersection(true);

        if (distancePiBaseP0 < distancePiTopP0) {

            if (tBase < 0) {
                this->setHasIntersection(false);
                return false;
            }

            this->setP0distance(distancePiBaseP0);
            this->setT(tBase);
            this->setIntersectionPoint(piBase);
            this->setObjectSurface(ObjectSurface::CYLINDER_BASE);

        }
        else {

            if (tTop < 0) {
                this->setHasIntersection(false);
                return false;
            }

            this->setP0distance(distancePiTopP0);
            this->setT(tTop);
            this->setIntersectionPoint(piTop);
            this->setObjectSurface(ObjectSurface::CYLINDER_TOP);

        }
        std::cout << "return true 1\n";
        return true;
    }





    // VERIFICANDO INTERSEÇÃO SUPERFÍCIE

    Vector w = *dir - (*this->direction * (dir->scalarProd(*this->direction)));
    Vector v = (*p0 - *this->center_base) - (*this->direction * ((*p0 - *this->center_base).scalarProd(*this->direction)));

    double delta, t1, t2;

    double a = w.scalarProd(w);
    double b = v.scalarProd(w);
    double c = v.scalarProd(v) - ((this->rad) * (this->rad));

    delta = (b * b) - a * c;

    // DELTA = 0
    if (delta == 0)
    {
        this->setHasIntersection(false);
        return false;

    }

    // DELTA > 0
    else if (delta > 0)
    {

        this->setHasIntersection(true);
        t1 = (-b + sqrt(delta)) / (a);
        t2 = (-b - sqrt(delta)) / (a);

        Vector pitemp1 = (*p0) + ((*dir) * t1);
        Vector* pi1 = new Vector(pitemp1.getCoordinate(0), pitemp1.getCoordinate(1), pitemp1.getCoordinate(2));

        Vector pitemp2 = (*p0) + ((*dir) * t2);
        Vector* pi2 = new Vector(pitemp2.getCoordinate(0), pitemp2.getCoordinate(1), pitemp2.getCoordinate(2));

        Vector distancePi1P0Vector = (*p0) - (*pi1);
        Vector distancePi2P0Vector = (*p0) - (*pi2);
        double distancePi1P0 = distancePi1P0Vector.getLength();
        double distancePi2P0 = distancePi2P0Vector.getLength();

        double ver1 = (*pi1 - *this->center_base).scalarProd(*this->direction);
        double ver2 = (*pi2 - *this->center_base).scalarProd(*this->direction);

        // CASO 1
        if ((ver1 >= 0 and ver1 <= this->height) and (ver2 >= 0 and ver2 <= this->height)) {

            if (distancePi1P0 < distancePi2P0) {

                if (t1 < 0) {
                    this->setHasIntersection(false);
                    return false;
                }

                this->setP0distance(distancePi1P0);
                this->setT(t1);
                this->setIntersectionPoint(pi1);
                this->setObjectSurface(ObjectSurface::CYLINDER_SURFACE);
                return true;
            }

            else {

                if (t2 < 0) {
                    this->setHasIntersection(false);
                    return false;
                }

                this->setP0distance(distancePi2P0);
                this->setT(t2);
                this->setIntersectionPoint(pi2);
                this->setObjectSurface(ObjectSurface::CYLINDER_SURFACE);
                return true;
            }

        }

        // CASO 2
        else if ((ver1 >= 0 and ver1 <= this->height) and !(ver2 >= 0 and ver2 <= this->height)) {

            if (interceptsBase) {

                if (distancePi1P0 < distancePiBaseP0) {

                    if (t1 < 0) {
                        this->setHasIntersection(false);
                        return false;
                    }

                    this->setP0distance(distancePi1P0);
                    this->setT(t1);
                    this->setIntersectionPoint(pi1);
                    this->setObjectSurface(ObjectSurface::CYLINDER_SURFACE);
                    return true;

                }

                else {

                    if (tBase < 0) {
                        this->setHasIntersection(false);
                        return false;
                    }

                    this->setP0distance(distancePiBaseP0);
                    this->setT(tBase);
                    this->setIntersectionPoint(piBase);
                    this->setObjectSurface(ObjectSurface::CYLINDER_BASE);
                    return true;

                }

            }

            else {

                if (distancePi1P0 < distancePiTopP0) {

                    if (t1 < 0) {
                        this->setHasIntersection(false);
                        return false;
                    }

                    this->setP0distance(distancePi1P0);
                    this->setT(t1);
                    this->setIntersectionPoint(pi1);
                    this->setObjectSurface(ObjectSurface::CYLINDER_SURFACE);
                    return true;

                }

                else {

                    if (tTop < 0) {
                        this->setHasIntersection(false);
                        return false;
                    }

                    this->setP0distance(distancePiTopP0);
                    this->setT(tTop);
                    this->setIntersectionPoint(piTop);
                    this->setObjectSurface(ObjectSurface::CYLINDER_TOP);
                    return true;

                }

            }

        }

        // CASO 3
        else if (!(ver1 >= 0 and ver1 <= this->height) and (ver2 >= 0 and ver2 <= this->height)) {

            if (interceptsBase) {

                if (distancePi2P0 < distancePiBaseP0) {

                    if (t2 < 0) {
                        this->setHasIntersection(false);
                        return false;
                    }

                    this->setP0distance(distancePi2P0);
                    this->setT(t2);
                    this->setIntersectionPoint(pi2);
                    this->setObjectSurface(ObjectSurface::CYLINDER_SURFACE);
                    return true;

                }

                else {

                    if (tBase < 0) {
                        this->setHasIntersection(false);
                        return false;
                    }

                    this->setP0distance(distancePiBaseP0);
                    this->setT(tBase);
                    this->setIntersectionPoint(piBase);
                    this->setObjectSurface(ObjectSurface::CYLINDER_BASE);
                    return true;

                }

            }

            else {

                if (distancePi2P0 < distancePiTopP0) {

                    if (t2 < 0) {
                        this->setHasIntersection(false);
                        return false;
                    }

                    this->setP0distance(distancePi2P0);
                    this->setT(t2);
                    this->setIntersectionPoint(pi2);
                    this->setObjectSurface(ObjectSurface::CYLINDER_SURFACE);
                    return true;

                }

                else {

                    if (tTop < 0) {
                        this->setHasIntersection(false);
                        return false;
                    }

                    this->setP0distance(distancePiTopP0);
                    this->setT(tTop);
                    this->setIntersectionPoint(piTop);
                    this->setObjectSurface(ObjectSurface::CYLINDER_TOP);
                    return true;

                }

            }

        }

        // CASO 4
        else {
            this->setHasIntersection(false);
            return false;
        }
    }

    // DELTA < 0
    else {
        this->setHasIntersection(false);
        return false;
    }
}


bool Cylinder::intersect_for_shadow(Vector* p0, Vector* dir) {
    // VERIFICANDO INTERSEÇÃO BASE OU TOPO

    double verParallel = dir->scalarProd(*this->direction);

    double tBase;
    double tTop;

    Vector* piBase = new Vector();
    Vector* piTop = new Vector();

    double distancePiBaseP0;
    double distancePiTopP0;

    bool interceptsBase = false;
    bool interceptsTop = false;

    if (verParallel != 0) {
        tBase = (((*p0 - *this->center_base).scalarProd(*this->direction)) / verParallel) * (-1);

        Vector center_top = *this->center_base + *this->direction * this->height;
        tTop = (((*p0 - center_top).scalarProd(*this->direction)) / verParallel) * (-1);

        Vector piBaseTemp = *p0 + *dir * tBase;
        piBase = new Vector(piBaseTemp.getCoordinate(0), piBaseTemp.getCoordinate(1), piBaseTemp.getCoordinate(2));
        Vector piTopTemp = *p0 + *dir * tTop;
        piTop = new Vector(piTopTemp.getCoordinate(0), piTopTemp.getCoordinate(1), piTopTemp.getCoordinate(2));

        distancePiBaseP0 = (*piBase - *p0).getLength();
        distancePiTopP0 = (*piTop - *p0).getLength();

        if ((*piBase - *this->center_base).getLength() <= this->rad) {
            interceptsBase = true;
        }

        if ((*piTop - center_top).getLength() <= this->rad) {
            interceptsTop = true;
        }
    }


    if (interceptsBase && interceptsTop) {
        this->setHasIntersectionShadow(true);

        if (distancePiBaseP0 < distancePiTopP0) {

            if (tBase < 0) {
                this->setHasIntersectionShadow(false);
                return false;
            }

            this->setP0distanceShadow(distancePiBaseP0);
            this->setTShadow(tBase);
        }
        else {

            if (tTop < 0) {
                this->setHasIntersectionShadow(false);
                return false;
            }

            this->setP0distanceShadow(distancePiTopP0);
            this->setTShadow(tTop);
        }

        return true;
    }





    // VERIFICANDO INTERSEÇÃO SUPERFÍCIE

    Vector w = *dir - (*dir * *this->direction) * *this->direction;
    Vector v = (*p0 - *this->center_base) - (((*p0 - *this->center_base) * *this->direction) * *this->direction);

    double delta, t1, t2;

    double a = w.scalarProd(w);
    double b = v.scalarProd(w);
    double c = v.scalarProd(v) - ((this->rad) * (this->rad));

    delta = (b * b) - a * c;

    // DELTA = 0
    if (delta == 0)
    {
        this->setHasIntersectionShadow(false);
        return false;

    }

    // DELTA > 0
    else if (delta > 0)
    {

        this->setHasIntersectionShadow(true);
        t1 = (-b + sqrt(delta)) / (a);
        t2 = (-b - sqrt(delta)) / (a);

        Vector pitemp1 = (*p0) + ((*dir) * t1);
        Vector* pi1 = new Vector(pitemp1.getCoordinate(0), pitemp1.getCoordinate(1), pitemp1.getCoordinate(2));

        Vector pitemp2 = (*p0) + ((*dir) * t2);
        Vector* pi2 = new Vector(pitemp2.getCoordinate(0), pitemp2.getCoordinate(1), pitemp2.getCoordinate(2));

        Vector distancePi1P0Vector = (*p0) - (*pi1);
        Vector distancePi2P0Vector = (*p0) - (*pi2);
        double distancePi1P0 = distancePi1P0Vector.getLength();
        double distancePi2P0 = distancePi2P0Vector.getLength();

        double ver1 = (*pi1 - *this->center_base).scalarProd(*this->direction);
        double ver2 = (*pi2 - *this->center_base).scalarProd(*this->direction);

        // CASO 1
        if ((ver1 >= 0 and ver1 <= this->height) and (ver2 >= 0 and ver2 <= this->height)) {

            if (distancePi1P0 < distancePi2P0) {

                if (t1 < 0) {
                    this->setHasIntersectionShadow(false);
                    return false;
                }

                this->setP0distanceShadow(distancePi1P0);
                this->setTShadow(t1);
            }

            else {

                if (t2 < 0) {
                    this->setHasIntersectionShadow(false);
                    return false;
                }

                this->setP0distanceShadow(distancePi2P0);
                this->setTShadow(t2);
            }

        }

        // CASO 2
        else if ((ver1 >= 0 and ver1 <= this->height) and !(ver2 >= 0 and ver2 <= this->height)) {

            if (interceptsBase) {

                if (distancePi1P0 < distancePiBaseP0) {

                    if (t1 < 0) {
                        this->setHasIntersectionShadow(false);
                        return false;
                    }

                    this->setP0distanceShadow(distancePi1P0);
                    this->setTShadow(t1);

                }

                else {

                    if (tBase < 0) {
                        this->setHasIntersectionShadow(false);
                        return false;
                    }

                    this->setP0distanceShadow(distancePiBaseP0);
                    this->setTShadow(tBase);

                }

            }

            else {

                if (distancePi1P0 < distancePiTopP0) {

                    if (t1 < 0) {
                        this->setHasIntersectionShadow(false);
                        return false;
                    }

                    this->setP0distanceShadow(distancePi1P0);
                    this->setTShadow(t1);

                }

                else {

                    if (tTop < 0) {
                        this->setHasIntersectionShadow(false);
                        return false;
                    }

                    this->setP0distanceShadow(distancePiTopP0);
                    this->setTShadow(tTop);

                }

            }

        }

        // CASO 3
        else if (!(ver1 >= 0 and ver1 <= this->height) and (ver2 >= 0 and ver2 <= this->height)) {

            if (interceptsBase) {

                if (distancePi2P0 < distancePiBaseP0) {

                    if (t2 < 0) {
                        this->setHasIntersectionShadow(false);
                        return false;
                    }

                    this->setP0distanceShadow(distancePi2P0);
                    this->setTShadow(t2);

                }

                else {

                    if (tBase < 0) {
                        this->setHasIntersectionShadow(false);
                        return false;
                    }

                    this->setP0distanceShadow(distancePiBaseP0);
                    this->setTShadow(tBase);

                }

            }

            else {

                if (distancePi2P0 < distancePiTopP0) {

                    if (t2 < 0) {
                        this->setHasIntersectionShadow(false);
                        return false;
                    }

                    this->setP0distanceShadow(distancePi2P0);
                    this->setTShadow(t2);

                }

                else {

                    if (tTop < 0) {
                        this->setHasIntersectionShadow(false);
                        return false;
                    }

                    this->setP0distanceShadow(distancePiTopP0);
                    this->setTShadow(tTop);

                }

            }

        }

        // CASO 4
        else {
            this->setHasIntersectionShadow(false);
            return false;
        }
    }

    // DELTA < 0
    else {
        this->setHasIntersectionShadow(false);
        return false;
    }
}


Color* Cylinder::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) {

    if (this->surface == ObjectSurface::CYLINDER_TOP) {

        return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, this->direction, this);

    }

    else if (this->surface == ObjectSurface::CYLINDER_BASE) {

        Vector* normal = new Vector(*this->direction * (-1));
        return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, normal, this);

    }

    else {

        Vector temp = (*this->getIntersectionPoint() - *this->center_base);
        double htemp = temp.scalarProd(*this->direction);
        Vector proj = *this->center_base + (*this->direction * htemp);
        Vector normaltemp = *this->getIntersectionPoint() - proj;
        normaltemp = normaltemp / normaltemp.getLength();
        Vector* normal = new Vector(normaltemp.getCoordinate(0), normaltemp.getCoordinate(1), normaltemp.getCoordinate(2));
        return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, normal, this);

    }

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
    this->setObjectType(ObjectType::CYLINDER);
}
