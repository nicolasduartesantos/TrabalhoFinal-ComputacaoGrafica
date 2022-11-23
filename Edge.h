#pragma once
#include <vector>

class Edge {
public:

	std::vector<int> vertexIds = std::vector<int>(2);

	Edge(int v1, int v2);

};
