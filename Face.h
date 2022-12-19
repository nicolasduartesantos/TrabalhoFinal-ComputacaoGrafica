#pragma once

#include <vector>
#include "Edge.h"

class Face {
public:

	std::vector<int> edgeIds = std::vector<int>(3);
	Face(int e1, int e2, int e3);

};


class Face2 {
public:
	std::vector<int> idVertices = std::vector<int>(3);
	Face2(int v1, int v2, int v3);
};



class FaceTexturized {
public:

	std::vector<int> edgeIdsT = std::vector<int>(3);
	bool active = true;

	void setActive(bool active);
	bool getActive();

	FaceTexturized(int e1, int e2, int e3);

};
