#pragma once

#include "Vector.h"

class Light {
private:
	Vector* intensity = nullptr;
	Vector* coordinate = nullptr;

public:
    void setIntensity(Vector* intensity);
    Vector* getIntensity();

    void setCoordinate(Vector* coordinate);
    Vector* getCoordinate();

    Light(Vector* intensity, Vector* coordinate);
};
