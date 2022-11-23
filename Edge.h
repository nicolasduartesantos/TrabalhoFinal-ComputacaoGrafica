#pragma once
#include <vector>

class Edge {
public:

	std::vector<int> vertexIds = std::vector<int>(2); // tamanho 2

	Edge(int v1, int v2);

};
