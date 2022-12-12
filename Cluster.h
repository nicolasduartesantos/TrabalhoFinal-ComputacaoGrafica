#pragma once

#include "Cylinder.h"

class Cluster : public Cylinder {

public:

	bool intersect(Vector* p0, Vector* dir);

	bool intersect_for_shadow(Vector* p0, Vector* dir);

	Cluster();

	Cluster(double rad, Vector* center_base, Vector* direction, double height);

	~Cluster();

};
