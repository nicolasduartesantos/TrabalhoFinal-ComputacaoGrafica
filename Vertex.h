#pragma once

#include "Object.h"

class Vertex : public Object {
private:

	Vector vertex;

public:

	Vertex(double x, double y, double z);

	Vertex operator * (const Vertex& b);

};
