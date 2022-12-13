#include "Vector.h"
#include "Light.h"
#include "Camera.h"


void Light::setIntensity(Vector* intensity) {
    this->intensity = intensity;
}
Vector* Light::getIntensity() {
    return this->intensity;
}


void Light::setActive(bool active) {
    this->active = active;
}
bool Light::getActive() {
    return this->active;
}


Light::Light(Vector* intensity) {
    this->setIntensity(intensity);
}


Light::Light() {

}


Light::~Light() {
    delete this->getIntensity();
}




///////////////////////////////// SPOT /////////////////////////////////

void Spot::setDirection(Vector* direction) {
    this->direction = direction;
}
Vector* Spot::getDirection() {
    return this->direction;
}


void Spot::setCoordinate(Vector* coordinate) {
    this->coordinate = coordinate;
}
Vector* Spot::getCoordinate() {
    return this->coordinate;
}


void Spot::setAngle(double angle) {
    this->angle = angle;
}
double Spot::getAngle() {
    return this->angle;
}


Vector Spot::calculateL(Vector pi) {
    Vector l = (*this->getCoordinate() * (-1));
    l = l / (l.getLength());

    return l;
}
// INTENSIDADE DO SPOT ?


double Spot::distance(Vector p) {
    Vector d = *this->coordinate - p;
    return d.getLength();
}


void Spot::doWorldToCamera(Camera* camera) {

    Vector* d = new Vector(camera->worldToCamera(*this->initial_direction) - camera->worldToCamera(Vector(0, 0, 0)));
    delete this->getDirection();
    this->setDirection(d);

    Vector* c = new Vector(camera->worldToCamera(*this->initial_coordinate));
    delete this->getCoordinate();
    this->setCoordinate(c);

}


Spot::Spot(Vector* intensity, Vector* coordinate, Vector* direction, double angle) {
    this->setIntensity(intensity);
    this->coordinate = coordinate;
    this->direction = direction;
    this->angle = angle;

    this->initial_direction = new Vector(*this->direction);
    this->initial_coordinate = new Vector(*this->coordinate);
}


Spot::~Spot() {
    delete this->getCoordinate();
    delete this->getDirection();

    delete this->initial_coordinate;
    delete this->initial_direction;
}




///////////////////////////////// POINT /////////////////////////////////

void Point::setCoordinate(Vector* coordinate) {
    this->coordinate = coordinate;
}
Vector* Point::getCoordinate() {
    return this->coordinate;
}


Vector Point::calculateL(Vector pi) {

    Vector l = (*this->getCoordinate() - pi);
    l = l / (l.getLength());

    return l;
}


double Point::distance(Vector p) {
    Vector d = *this->coordinate - p;
    return d.getLength();
}


void Point::doWorldToCamera(Camera* camera) {

    Vector* c = new Vector(camera->worldToCamera(*this->initial_coordinate));
    delete this->getCoordinate();
    this->setCoordinate(c);

}


Point::Point(Vector* intensity, Vector* coordinate) {
    this->setIntensity(intensity);
    this->coordinate = coordinate;

    this->initial_coordinate = new Vector(*this->coordinate);
}


Point::~Point() {
    delete this->getCoordinate();

    delete this->initial_coordinate;
}




///////////////////////////////// DIRECTIONAL /////////////////////////////////

void Directional::setDirection(Vector* direction) {
    this->direction = direction;
}
Vector* Directional::getDirection() {
    return this->direction;
}


Vector Directional::calculateL(Vector pi) {

    Vector l = (*this->getDirection() * (-1));
    l = l / (l.getLength());

    return l;
}


double Directional::distance(Vector p) {
    return std::numeric_limits<double>::infinity();
}


void Directional::doWorldToCamera(Camera* camera) {

    Vector* d = new Vector(camera->worldToCamera(*this->initial_direction) - camera->worldToCamera(Vector(0, 0, 0)));
    delete this->getDirection();
    this->setDirection(d);

}


Directional::Directional(Vector* intensity, Vector* direction) {
    this->setIntensity(intensity);
    this->direction = direction;

    this->initial_direction = new Vector(*this->direction);
}


Directional::~Directional() {
    delete this->getDirection();

    delete this->initial_direction;
}
