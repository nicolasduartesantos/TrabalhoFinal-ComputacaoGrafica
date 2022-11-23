#include "Face.h"

Face::Face(int e1, int e2, int e3) {
	this->edgeIds[0] = e1;
	this->edgeIds[1] = e2;
	this->edgeIds[2] = e3;
}