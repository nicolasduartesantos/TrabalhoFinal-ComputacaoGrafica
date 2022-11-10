#pragma once

#include "Object.h"

class Cone : public Object {
private:

	double rad;
	Vector* center_base = nullptr;
	Vector* direction = nullptr;
	double height;
	Vector* vertex = nullptr;
	double cos;
	//cos = h/ sqrt(rad * rad + h * h)
	//vertex = center_base + direction * height

public:

	void setRad(double rad);
	double getRad();

	void setCenter_base(Vector* center_base);
	Vector* getCenter_base();

	void setDirection(Vector* direction);
	Vector* getDirection();

	void setHeight(double height);
	double getHeight();

	bool intersect(Vector* p0, Vector* dir);

	bool intersect_for_shadow(Vector* p0, Vector* dir);

	Color* getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight);

	Cone(double rad, Vector* center_base, Vector* direction, double height, Vector* kd, Vector* ke, Vector* ka, double shininess);
	Cone(double rad, Vector* center_base, Vector* direction, double height, Vector* vertex, Vector* kd, Vector* ke, Vector* ka, double shininess);
};