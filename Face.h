#pragma once

#include <vector>
#include "Edge.h"

class Face {
public:

	std::vector<int> edgeIds; // tamanho 3

	Face(int e1, int e2, int e3);

};
