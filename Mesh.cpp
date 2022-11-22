#include "Mesh.h"
#include "Face.h"
#include "Edge.h"
#include "Vector.h"

void Mesh::addFace(Face* face) {
	this->faces.push_back(face);
}
std::vector<Face*> Mesh::getFaces() {
	return this->faces;
}


void Mesh::addEdge(Edge* edge) {
	this->edges.push_back(edge);
}
std::vector<Edge*> Mesh::getEdges() {
	return this->edges;
}


void Mesh::addVertex(Vector* vertex) {
	this->vertices.push_back(vertex);
}
std::vector<Vector*> Mesh::getVertices() {
	return this->vertices;
}


void Mesh::setNormal(Vector* normal) {
	this->normal = normal;
}

Vector* Mesh::getNormal() {
	return this->normal;
}




bool Mesh::intersect(Vector* p0, Vector* dir) {

	this->setObjectSurface(ObjectSurface::ON_PLAN);
	this->setHasIntersection(false);
	Vector* meshNormal = new Vector();

	for (Face* face : this->getFaces()) {

		int idEdge1 = face->edgeIds[0];
		int idEdge2 = face->edgeIds[1];

		int idVertex11 = this->edges[idEdge1]->vertexIds[0];
		int idVertex12 = this->edges[idEdge1]->vertexIds[1];
		int idVertex21 = this->edges[idEdge2]->vertexIds[0];
		int idVertex22 = this->edges[idEdge2]->vertexIds[1];

		int n1 = idVertex11 * idVertex12;
		int n = n1 / idVertex21;

		int v1, v2, v3;

		if (n == idVertex11 or n == idVertex12) {
			v1 = idVertex21;
			v2 = idVertex22;
			v3 = n;
		}

		else {
			v1 = idVertex22;
			v2 = idVertex21;
			v3 = n1 / v1;
		}


		Vector p1 = *this->vertices[0];
		Vector p2 = *this->vertices[1];
		Vector p3 = *this->vertices[2];

		Vector r1 = p2 - p1;
		Vector r2 = p3 - p1;

		Vector normal = r1.product(r2);
		Vector normalUnitary = normal / normal.getLength();

		Vector w = *p0 - p1;

		double drn = dir->scalarProd(normalUnitary);

		double t;

		t = -((w.scalarProd(normalUnitary)) / drn);

		if (drn != 0 && t > 0) {

			Vector pitemp = (*p0) + ((*dir) * t);

			Vector distancePiP0Vector = (*p0) - (pitemp);
			double distancePiP0 = distancePiP0Vector.getLength();

			Vector v = pitemp - p1;

			double c1 = (v.product(r2)).scalarProd(normalUnitary) / (r1.product(r2)).scalarProd(normalUnitary);
			double c2 = (r1.product(v)).scalarProd(normalUnitary) / (r1.product(r2)).scalarProd(normalUnitary);
			double c3 = 1 - c1 - c2;

			if (c1 >= 0 && c2 <= 0 && c3 >= 0 && (this->getHasIntersection() == false || this->getP0distance() > distancePiP0)) {

				this->setHasIntersection(true);
				this->setP0distance(distancePiP0);
				Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));
				this->setIntersectionPoint(pi);
				this->setT(t);
				*meshNormal = normalUnitary;
				this->setNormal(meshNormal);

			}
		}
	}
	return true;
}


bool Mesh::intersect_for_shadow(Vector* p0, Vector* dir) {

	return false;

}


Color* Mesh::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) {

	return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, this->normal, this);

}


Mesh::Mesh(Vector* kd, Vector* ke, Vector* ka, double shininess) {
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
}
