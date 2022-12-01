#include "Mesh.h"
#include "Face.h"
#include "Edge.h"
#include "Vector.h"
#include <iostream>

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

		double n1 = ((double)idVertex11) * ((double)idVertex12);
		double n = n1 / ((double)idVertex21);

		double v1, v2, v3;

		if (n == ((double)idVertex11) or n == ((double)idVertex12)) {
			v1 = (double)idVertex21;
			v2 = (double)idVertex22;
			v3 = n;
		}

		else {
			v1 = (double)idVertex22;
			v2 = (double)idVertex21;
			v3 = n1 / v1;
		}


		Vector p1 = *this->vertices[v1];
		Vector p2 = *this->vertices[v2];
		Vector p3 = *this->vertices[v3];

		Vector r1 = p2 - p1;
		Vector r2 = p3 - p1;

		Vector normal = r1.product(r2);
		Vector normalUnitary = normal / normal.getLength();

		Vector w = *p0 - p1;

		double drn = dir->scalarProd(normalUnitary);

		double t;

		t = (-(w.scalarProd(normalUnitary)) / drn);

		if (drn != 0 && t > 0) {

			Vector pitemp = (*p0) + ((*dir) * t);

			Vector distancePiP0Vector = (pitemp)-(*p0);
			double distancePiP0 = distancePiP0Vector.getLength();

			Vector v = pitemp - p1;

			double c1 = (v.product(r2)).scalarProd(normalUnitary) / (r1.product(r2)).scalarProd(normalUnitary);
			double c2 = (r1.product(v)).scalarProd(normalUnitary) / (r1.product(r2)).scalarProd(normalUnitary);
			double c3 = 1 - c1 - c2;

			if (c1 >= 0 && c2 >= 0 && c3 >= 0 && (this->getHasIntersection() == false || this->getP0distance() > distancePiP0)) {
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
	return this->getHasIntersection();
}


bool Mesh::intersect_for_shadow(Vector* p0, Vector* dir) {

	this->setHasIntersectionShadow(false);
	Vector* meshNormal = new Vector();

	for (Face* face : this->getFaces()) {

		int idEdge1 = face->edgeIds[0];
		int idEdge2 = face->edgeIds[1];

		int idVertex11 = this->edges[idEdge1]->vertexIds[0];
		int idVertex12 = this->edges[idEdge1]->vertexIds[1];
		int idVertex21 = this->edges[idEdge2]->vertexIds[0];
		int idVertex22 = this->edges[idEdge2]->vertexIds[1];

		double n1 = ((double)idVertex11 + 1) * ((double)idVertex12 + 1);
		double n = n1 / ((double)idVertex21 + 1);

		double v1, v2, v3;

		if (n == ((double)idVertex11 + 1) or n == ((double)idVertex12 + 1)) {
			v1 = (double)idVertex21;
			v2 = (double)idVertex22;
			v3 = n - 1;
		}

		else {
			v1 = (double)idVertex22;
			v2 = (double)idVertex21;
			v3 = (n1 / (v1 + 1)) - 1;
		}


		Vector p1 = *this->vertices[v1];
		Vector p2 = *this->vertices[v2];
		Vector p3 = *this->vertices[v3];

		Vector r1 = p2 - p1;
		Vector r2 = p3 - p1;

		Vector normal = r1.product(r2);
		Vector normalUnitary = normal / normal.getLength();

		Vector w = *p0 - p1;

		double drn = dir->scalarProd(normalUnitary);

		double t;

		t = (-(w.scalarProd(normalUnitary)) / drn);

		if (drn != 0 && t > 0) {

			Vector pitemp = (*p0) + ((*dir) * t);

			Vector distancePiP0Vector = (pitemp)-(*p0);
			double distancePiP0 = distancePiP0Vector.getLength();

			Vector v = pitemp - p1;

			double c1 = (v.product(r2)).scalarProd(normalUnitary) / (r1.product(r2)).scalarProd(normalUnitary);
			double c2 = (r1.product(v)).scalarProd(normalUnitary) / (r1.product(r2)).scalarProd(normalUnitary);
			double c3 = 1 - c1 - c2;

			if (c1 >= 0 && c2 >= 0 && c3 >= 0 && (this->getHasIntersection() == false || this->getP0distance() > distancePiP0)) {
				this->setHasIntersectionShadow(true);
				this->setP0distanceShadow(distancePiP0);
				this->setTShadow(t);

			}
		}
	}
	return true;

}


Color* Mesh::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) {

	return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, this->normal, this);

}


Mesh::Mesh(Vector* kd, Vector* ke, Vector* ka, double shininess) {
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
	this->setObjectType(ObjectType::MESH);
}