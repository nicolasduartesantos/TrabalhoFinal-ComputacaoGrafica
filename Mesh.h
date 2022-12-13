#pragma once

#include "Object.h"
#include "Face.h"
#include "Edge.h"
#include "Vector.h"
#include "Cluster.h"

class Mesh : public Object {
private:

	ObjectType type = ObjectType::MESH;

	std::vector<Face*> faces;
	std::vector<Edge*> edges;
	std::vector<Vector*> vertices;
	Vector* normal = nullptr;
	Cluster* cluster = nullptr;

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

	void scaling(double sx, double sy, double sz);
	void translation(double tx, double ty, double tz);
	void rotX(double a);
	void rotY(double a);
	void rotZ(double a);
	void shearingYX(double a);
	void shearingXY(double a);
	void shearingYZ(double a);
	void shearingZY(double a);
	void shearingXZ(double a);
	void shearingZX(double a);
	void reflectionXY();
	void reflectionXZ();
	void reflectionYZ();

	void doWorldToCamera(Camera* camera);

	//void reverseFacesVertexesOrder();

	bool inside(Vector* p);

	Mesh(Vector* kd, Vector* ke, Vector* ka, double shininess, Cluster* cluster);

	~Mesh();
};
