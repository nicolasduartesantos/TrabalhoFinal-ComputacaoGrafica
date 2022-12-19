#include "Face.h"

Face::Face(int e1, int e2, int e3) {
	this->edgeIds[0] = e1;
	this->edgeIds[1] = e2;
	this->edgeIds[2] = e3;
}


Face2::Face2(int v1, int v2, int v3) {
	this->idVertices[0] = v1;
	this->idVertices[1] = v2;
	this->idVertices[2] = v3;
}




void FaceTexturized::setActive(bool active) {
	this->active = active;
}
bool FaceTexturized::getActive() {
	return this->active;
}


FaceTexturized::FaceTexturized(int e1, int e2, int e3) {
	this->edgeIdsT[0] = e1;
	this->edgeIdsT[1] = e2;
	this->edgeIdsT[2] = e3;
}
