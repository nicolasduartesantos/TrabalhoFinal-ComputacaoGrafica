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

	void meshScaling(double sx, double sy, double sz);
	void meshTranslation(double tx, double ty, double tz);
	void meshRotationX(double a);
	void meshRotationY(double a);
	void meshRotationZ(double a);
	void meshShearingYX(double a);
	void meshShearingXY(double a);
	void meshShearingYZ(double a);
	void meshShearingZY(double a);
	void meshShearingXZ(double a);
	void meshShearingZX(double a);

	void doWorldToCamera(Camera* camera);
	
	Mesh(Vector* kd, Vector* ke, Vector* ka, double shininess);

	~Mesh();
};
