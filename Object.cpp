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


bool Object::hasShadow(std::vector<Object*> objects, Vector* pi, Vector l, Vector* pf) {

    int iClosest = 0;
    Object* closest = objects[0];

    for (int j = 0; j < objects.size(); j++) {

        objects[j]->intersect_for_shadow(pi, &l);

        if (objects[j]->getHasIntersectionShadow() && objects[j] != this &&
            (!closest->getHasIntersectionShadow() || (objects[j]->getP0distanceShadow() < closest->getP0distanceShadow()))) {

            closest = objects[j];
            int iClosest = j;
        }

    }

    if (closest->getHasIntersectionShadow() && closest->getTShadow() < (*pf - *pi).getLength() && closest != this) {
        return true;
    }
    return false;
}
