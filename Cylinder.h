#pragma once

#include "Object.h"

class Cylinder : public Object {
private:

	double rad;
	Vector* center_base = nullptr;
	Vector* direction = nullptr;
	double height;

public:

	Vector* initial_center_base = nullptr;
	Vector* initial_direction = nullptr;
	double initial_height;

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

	Cylinder();

	Cylinder(double rad, Vector* center_base, Vector* direction, double height, Vector* kd, Vector* ke, Vector* ka, double shininess);

	~Cylinder();
};