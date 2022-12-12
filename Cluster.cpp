#include "Cluster.h"

bool Cluster::intersect(Vector* p0, Vector* dir) {
	return Cylinder::intersect(p0, dir);
}


bool Cluster::intersect_for_shadow(Vector* p0, Vector* dir) {
	return Cylinder::intersect_for_shadow(p0, dir);
}


Cluster::Cluster() : Cylinder() { }


Cluster::Cluster(double rad, Vector* center_base, Vector* direction, double height) : Cylinder(rad, center_base, direction, height, nullptr, nullptr, nullptr, 0.0) { }


Cluster::~Cluster() { }
