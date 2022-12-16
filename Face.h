#pragma once

#include <vector>
#include "Edge.h"

class Face {
public:

	std::vector<int> edgeIds = std::vector<int>(3);
	Face(int e1, int e2, int e3);

};



class FaceTexturized {
public:

	std::vector<int> edgeIdsT = std::vector<int>(3);
	bool active = true;

	void setActive(bool active);
	bool getActive();

	FaceTexturized(int e1, int e2, int e3);

};
