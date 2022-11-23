#pragma once

#include "Object.h"
#include "Face.h"
#include "Edge.h"
#include "Vector.h"

class Mesh : public Object {
private:

	ObjectType type = ObjectType::MESH;

	std::vector<Face*> faces;
	std::vector<Edge*> edges;
	std::vector<Vector*> vertices;
	Vector* normal = nullptr;

public:

	void addFace(Face* face);
	std::vector<Face*> getFaces();

	void addEdge(Edge* edge);
	std::vector<Edge*> getEdges();

	void addVertex(Vector* vector);
	std::vector<Vector*> getVertices();

	void setNormal(Vector* normal);
	Vector* getNormal();

	bool intersect(Vector* p0, Vector* dir);

	bool intersect_for_shadow(Vector* p0, Vector* dir);

	Color* getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight);

	Mesh(Vector* kd, Vector* ke, Vector* ka, double shininess);
};
