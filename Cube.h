#pragma once

#include "Mesh.h"

class Cube {
public:
	static Mesh* create(Vector* center_base, double edgeSize, Vector* kd, Vector* ke, Vector* ka, double shininess, Cluster* cluster);
};