#pragma once

#include "Vector.h"
#include "Camera.h"

enum class LightType { POINT, DIRECTIONAL, SPOT };

class Light {
private:
    Vector* intensity = nullptr;
    bool active = true;

public:

    LightType lightType;

    void setIntensity(Vector* intensity);
    Vector* getIntensity();

    void setActive(bool active);
    bool getActive();

    virtual Vector calculateL(Vector pi) = 0;

    virtual double distance(Vector p) = 0;

    virtual void doWorldToCamera(Camera* camera) = 0;

    Light(Vector* intensity);

    Light();

    virtual ~Light();
};


class Spot : public Light {
private:
    Vector* direction = nullptr;
    Vector* coordinate = nullptr;
    double angle;

public:

    Vector* initial_direction = nullptr;
    Vector* initial_coordinate = nullptr;

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

    ~Spot();

};


class Point : public Light {
private:
    Vector* coordinate = nullptr;

public:

    Vector* initial_coordinate = nullptr;

    void setCoordinate(Vector* coordinate);
    Vector* getCoordinate();

    Vector calculateL(Vector pi);

    double distance(Vector p);

    void doWorldToCamera(Camera* camera);

    Point(Vector* intensity, Vector* coordinate);

    ~Point();

};


class Directional : public Light {
private:
    Vector* direction = nullptr;

public:

    Vector* initial_direction = nullptr;

    void setDirection(Vector* direction);
    Vector* getDirection();

    Vector calculateL(Vector pi);

    double distance(Vector p);

    void doWorldToCamera(Camera* camera);

    Directional(Vector* intensity, Vector* direction);

    ~Directional();

};


class Environment : public Light {

public:

    Vector calculateL(Vector pi);

    double distance(Vector p);

    void doWorldToCamera(Camera* camera);

    Environment(Vector* intensity);

    ~Environment();

};