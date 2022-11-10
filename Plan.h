#pragma once

#include "Object.h"

class Plan : public Object {
private:

    Vector* p_pi = nullptr;
    Vector* normal = nullptr;

    Vector* kd = nullptr;
    Vector* ke = nullptr;
    double shininess = 1.0;

public:

    void setP_PI(Vector* p_pi);
    Vector* getP_PI();

    void setNormal(Vector* normal);
    Vector* getNormal();

    bool intersect(Vector* p0, Vector* dir);

    bool intersect_for_shadow(Vector* p0, Vector* dir);

    Color* getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight);

    Plan(Vector* p_pi, Vector* normal, Vector* kd, Vector* ke, Vector* ka, double shininess);
};
