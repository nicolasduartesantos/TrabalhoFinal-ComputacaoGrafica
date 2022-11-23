#pragma once

#include <vector>
#include "Edge.h"

class Face {
public:

	std::vector<int> edgeIds = std::vector<int>(3);
	Face(int e1, int e2, int e3);

};
