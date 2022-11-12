#pragma once

#include "Vector.h"
#include "Light.h"
#include "Color.h"
#include <vector>

enum class ObjectType { SPHERE, PLAN, CYLINDER, CONE};
enum class ObjectSurface { ON_SPHERE, ON_PLAN, CYLINDER_SURFACE, CYLINDER_BASE, CYLINDER_TOP, CONE_SURFACE, CONE_BASE, UNKNOWN };


class Object {
protected:

    ObjectType type;
    ObjectSurface surface;

    Vector* kd = nullptr;
    Vector* ke = nullptr;
    Vector* ka = nullptr;
    double shininess;

    double t;
    bool hasIntersection = false;
    Vector* intersectionPoint = nullptr;
    double p0distance;

    double tShadow;
    bool hasIntersectionShadow = false;
    double p0distanceShadow;

public:

    void setKD(Vector* kd);
    Vector* getKD();

    void setKE(Vector* ke);
    Vector* getKE();

    void setKA(Vector* ka);
    Vector* getKA();

    void setShininess(double shininess);
    double getShininess();

    void setObjectType(ObjectType type);
    ObjectType getObjectType();

    void setObjectSurface(ObjectSurface surface);
    ObjectSurface getObjectSurface();

    void setT(double t);
    double getT();

    void setHasIntersection(bool hasIntersection);
    bool getHasIntersection();

    void setIntersectionPoint(Vector* intersectionPoint);
    Vector* getIntersectionPoint();

    void setP0distance(double p0distance);
    double getP0distance();

    void setTShadow(double tShadow);
    double getTShadow();

    void setHasIntersectionShadow(bool hasIntersectionShadow);
    bool getHasIntersectionShadow();

    void setP0distanceShadow(double p0distanceShadow);
    double getP0distanceShadow();

    virtual bool intersect(Vector* p0, Vector* dir) = 0;

    virtual bool intersect_for_shadow(Vector* p0, Vector* dir) = 0;

    virtual Color* getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) = 0;

    bool hasShadow(std::vector<Object*> objects, Vector* pi, Vector l, Vector* pf);

    Color* RGBtoPaint(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight, Vector* normal, Object* obj);

};
