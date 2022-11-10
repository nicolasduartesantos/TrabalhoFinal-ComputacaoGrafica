#include "Vector.h"
#include "Light.h"


void Light::setIntensity(Vector* intensity) {
    this->intensity = intensity;
}


Vector* Light::getIntensity() {
    return this->intensity;
}


void Light::setCoordinate(Vector* coordinate) {
    this->coordinate = coordinate;
}


Vector* Light::getCoordinate() {
    return this->coordinate;
}


Light::Light(Vector* intensity, Vector* coordinate) {
    this->setIntensity(intensity);
    this->setCoordinate(coordinate);
}
