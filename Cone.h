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

public:

	Vector* initial_center_base = nullptr;
	Vector* initial_vertex = nullptr;

	void setRad(double rad);
	double getRad();

	void setCenter_base(Vector* center_base);
	Vector* getCenter_base();

	void setDirection(Vector* direction);
	Vector* getDirection();

	void setVertex(Vector* vertex);
	Vector* getVertex();

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

	Cone(double rad, Vector* center_base, Vector* direction, double height, Vector* kd, Vector* ke, Vector* ka, double shininess);
	Cone(double rad, Vector* center_base, Vector* direction, double height, Vector* vertex, Vector* kd, Vector* ke, Vector* ka, double shininess);

	~Cone();
};