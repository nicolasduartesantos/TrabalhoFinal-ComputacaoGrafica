#pragma once

#include "Object.h"

class Plan : public Object {

public:
    Vector* p_pi = nullptr;
    Vector* normal = nullptr;

    Vector* initial_p_pi = nullptr;
    Vector* initial_normal = nullptr;

    void setP_PI(Vector* p_pi);
    Vector* getP_PI();

    void setNormal(Vector* normal);
    Vector* getNormal();

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

    Plan(Vector* p_pi, Vector* normal, Vector* kd, Vector* ke, Vector* ka, double shininess);

    Plan();

    ~Plan();
};