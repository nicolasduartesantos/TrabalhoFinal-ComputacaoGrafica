#pragma once

#include "Mesh.h"
#include "MeshTexturized.h"
#include "Cluster.h"

class Cube {
public:
	static Mesh* create(Vector* center_base, double edgeSize, Vector* kd, Vector* ke, Vector* ka, double shininess, Cluster* cluster);

	static MeshTexturized* createWithTexture(Vector* center_base, double edgeSize, Image* texture, double shininess, Cluster* cluster);

};
