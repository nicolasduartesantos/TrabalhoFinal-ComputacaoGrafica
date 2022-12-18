#pragma once

#include "Object.h"

class Sphere : public Object {
private:

    double rad;
    Vector* center = nullptr;

public:

    Vector* initial_center = nullptr;

    void setRad(double rad);
    double getRad();

    void setCenter(Vector* center);
    Vector* getCenter();

    bool intersect(Vector* p0, Vector* dir);

    bool intersect_for_shadow(Vector* p0, Vector* dir);

    Color* getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Environment* environmentLight);

    void rotX(double a);
    void rotY(double a);
    void rotZ(double a);
    void translation(double tx, double ty, double tz);
    void scaling(double sx, double sy, double sz);
    void reflectionXY();
    void reflectionXZ();
    void reflectionYZ();

    void doWorldToCamera(Camera* camera);

    bool inside(Vector* p);

    Sphere(double rad, Vector* kd, Vector* ke, Vector* ka, Vector* center, double shininess);

    ~Sphere();
};