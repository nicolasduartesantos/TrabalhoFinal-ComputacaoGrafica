#pragma once

#include "Object.h"

class Sphere : public Object {
private:

    double rad;
    Vector* kd = nullptr;
    Vector* ke = nullptr;
    Vector* center = nullptr;
    double shininess = 1.0;

public:

    void setRad(double rad);
    double getRad();

    void setCenter(Vector* center);
    Vector* getCenter();

    bool intersect(Vector* p0, Vector* dir);

    bool intersect_for_shadow(Vector* p0, Vector* dir);

    Color* getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight, Vector* ka);

    Sphere(double rad, Vector* kd, Vector* ke, Vector* center, double shininess);
};
