#include "Object.h"
#include "Vector.h"
#include <iostream>

void Object::setKD(Vector* kd) {
    this->kd = kd;
}
Vector* Object::getKD() {
    return this->kd;
}


void Object::setKE(Vector* ke) {
    this->ke = ke;
}
Vector* Object::getKE() {
    return this->ke;
}

void Object::setKA(Vector* ka) {
    this->ka = ka;
}
Vector* Object::getKA() {
    return this->ka;
}


void Object::setShininess(double shininess) {
    this->shininess = shininess;
}
double Object::getShininess() {
    return this->shininess;
}


void Object::setObjectType(ObjectType type) {
    this->type = type;
}
ObjectType Object::getObjectType() {
    return this->type;
}


void Object::setObjectSurface(ObjectSurface surface) {
    this->surface = surface;
}
ObjectSurface Object::getObjectSurface() {
    return this->surface;
}


void Object::setT(double t) {
    this->t = t;
}
double Object::getT() {
    return this->t;
}


void Object::setHasIntersection(bool hasIntersection) {
    this->hasIntersection = hasIntersection;
}
bool Object::getHasIntersection() {
    return this->hasIntersection;
}


void Object::setIntersectionPoint(Vector* intersectionPoint) {
    this->intersectionPoint = intersectionPoint;
}
Vector* Object::getIntersectionPoint() {
    return this->intersectionPoint;
}


void Object::setP0distance(double p0distance) {
    this->p0distance = p0distance;
}
double Object::getP0distance() {
    return this->p0distance;
}


void Object::setTShadow(double tShadow) {
    this->tShadow = tShadow;
}
double Object::getTShadow() {
    return this->tShadow;
}


void Object::setHasIntersectionShadow(bool hasIntersectionShadow) {
    this->hasIntersectionShadow = hasIntersectionShadow;
}
bool Object::getHasIntersectionShadow() {
    return this->hasIntersectionShadow;
}


void Object::setP0distanceShadow(double p0distanceShadow) {
    this->p0distanceShadow = p0distanceShadow;
}
double Object::getP0distanceShadow() {
    return this->p0distanceShadow;
}


bool Object::hasShadow(std::vector<Object*> objects, Vector* pi, Vector l, Light* light) {

    for (int j = 0; j < objects.size(); j++) {

        objects[j]->intersect_for_shadow(pi, &l);

        double erro = 0.00001;

        if (objects[j]->getHasIntersectionShadow() && objects[j]->tShadow > erro && objects[j]->tShadow < light->distance(*pi)) {
            return true;
        }

    }

    return false;
}


Color* Object::RGBtoPaint(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Environment* environmentLight, Vector* normal, Object* obj) {

    Vector rgb(0, 0, 0);

    Vector* pi = obj->getIntersectionPoint();

    Vector v(0, 0, 0); Vector l(0, 0, 0); Vector r(0, 0, 0);

    v = (*dir * (-1)) / (dir->getLength());


    for (int i = 0; i < lights.size(); i++) {

        if (lights[i]->getActive()) {

            l = lights[i]->calculateL(*pi);

            Vector intensity = *lights[i]->getIntensity();

            if (lights[i]->lightType == LightType::SPOT) {

                double calcspot = l.scalarProd(*((Spot*)lights[i])->getDirection() * -1);

                if (calcspot < cos((((Spot*)lights[i])->getAngle()))) {
                    intensity = Vector(0, 0, 0);
                }
                else {
                    intensity = *((Spot*)lights[i])->getIntensity() * calcspot;
                }

            }

            bool hasShadow = obj->hasShadow(objects, pi, l, lights[i]);

            if (!hasShadow) {

                r = (*normal * (2 * (l.scalarProd(*normal)))) - l;

                double f_diffuse = std::max(0.0, (l.scalarProd(*normal)));
                double f_speculated = std::pow(std::max(0.0, (r.scalarProd(v))), shininess);

                Vector i_diffuse = (intensity) * (*obj->kd) * f_diffuse;
                Vector i_speculated = (intensity) * (*obj->ke) * f_speculated;

                rgb = rgb + i_diffuse + i_speculated;

            }
        }

    }

    if (environmentLight != nullptr && environmentLight->getActive()) {
        Vector i_environment = (*environmentLight->getIntensity()) * (*obj->ka);
        rgb = rgb + i_environment;
    }

    double cor_max = std::max(std::max(rgb.getCoordinate(0), rgb.getCoordinate(1)), rgb.getCoordinate(2));
    if (cor_max > 1) {
        rgb = rgb / cor_max;
    }

    Color* result = new Color(rgb.getCoordinate(0) * 255, rgb.getCoordinate(1) * 255, rgb.getCoordinate(2) * 255, 255);
    return result;

}


Object::~Object() {
    delete this->getKD();
    delete this->getKE();
    delete this->getKA();
    delete this->getIntersectionPoint();
}