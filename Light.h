#pragma once

#include "Vector.h"
#include "Camera.h"

class Light {
private:
	Vector* intensity = nullptr;

public:
    void setIntensity(Vector* intensity);
    Vector* getIntensity();

    virtual Vector calculateL(Vector pi) = 0;

    virtual double distance(Vector p) = 0;

    virtual void doWorldToCamera(Camera* camera) = 0;

    Light(Vector* intensity);

    Light();
};


class Spot : public Light {
private:
    Vector* direction = nullptr;
    Vector* coordinate = nullptr;
    double angle;

public:
    void setDirection(Vector* direction);
    Vector* getDirection();

    void setCoordinate(Vector* coordinate);
    Vector* getCoordinate();

    void setAngle(double angle);
    double getAngle();

    Vector calculateL(Vector pi);

    double distance(Vector p);

    void doWorldToCamera(Camera* camera);

    Spot(Vector* intensity, Vector* coordinate, Vector* direction, double angle);

};


class Point : public Light {
private:
    Vector* coordinate = nullptr;

public:

    void setCoordinate(Vector* coordinate);
    Vector* getCoordinate();

    Vector calculateL(Vector pi);

    double distance(Vector p);

    void doWorldToCamera(Camera* camera);

    Point(Vector* intensity, Vector* coordinate);

};


class Directional : public Light {
private:
    Vector* direction = nullptr;

public:
    void setDirection(Vector* direction);
    Vector* getDirection();

    Vector calculateL(Vector pi);

    double distance(Vector p);

    void doWorldToCamera(Camera* camera);

    Directional(Vector* intensity, Vector* direction);

};
