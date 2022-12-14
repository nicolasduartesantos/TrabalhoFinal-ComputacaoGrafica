#include "MeshTexturized.h"
#include "Face.h"
#include "Edge.h"
#include "Vector.h"
#include "Camera.h"
#include "Image.h"
#include <iostream>
#include <cmath>

void MeshTexturized::setTexture(Image* texture) {
	this->texture = texture;
}
Image* MeshTexturized::getTexture() {
	return this->texture;
}


void MeshTexturized::addFace(FaceTexturized* face) {
	this->faces.push_back(face);
}
std::vector<FaceTexturized*> MeshTexturized::getFaces() {
	return this->faces;
}


void MeshTexturized::addEdge(Edge* edge) {
	this->edges.push_back(edge);
}
std::vector<Edge*> MeshTexturized::getEdges() {
	return this->edges;
}


void MeshTexturized::addVertex(Vector* vertex) {
	this->vertices.push_back(vertex);
}
std::vector<Vector*> MeshTexturized::getVertices() {
	return this->vertices;
}


void MeshTexturized::setNormal(Vector* normal) {
	this->normal = normal;
}

Vector* MeshTexturized::getNormal() {
	return this->normal;
}




bool MeshTexturized::intersect(Vector* p0, Vector* dir) {

	this->setObjectSurface(ObjectSurface::ON_PLAN);
	this->setHasIntersection(false);
	Vector* meshNormal = new Vector();
	for (FaceTexturized* face : this->getFaces()) {

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


bool MeshTexturized::intersect_for_shadow(Vector* p0, Vector* dir) {

	this->setHasIntersectionShadow(false);
	Vector* meshNormal = new Vector();

	for (FaceTexturized* face : this->getFaces()) {

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


Color* MeshTexturized::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) {


	return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, this->normal, this);

}


void MeshTexturized::scaling(double sx, double sy, double sz) {
	for (Vector* v : this->initial_vertices) {
		*v = v->scaling(sx, sy, sz);
	}

	Vector ct = *this->cluster->initial_center_base + (*this->cluster->initial_direction * this->cluster->initial_height);
	Vector* center_top = new Vector(ct.getCoordinate(0), ct.getCoordinate(1), ct.getCoordinate(2));
	*center_top = center_top->scaling(sx, sy, sz);

	Vector* center_base = this->cluster->initial_center_base;
	*center_base = center_base->scaling(sx, sy, sz);

	Vector directionNotNormalized = (*center_top - *this->cluster->initial_center_base);
	Vector directionNormalized = directionNotNormalized / (directionNotNormalized.getLength());
	Vector* direction = new Vector(directionNormalized.getCoordinate(0), directionNormalized.getCoordinate(1), directionNormalized.getCoordinate(2));
	this->cluster->setDirection(direction);

	this->cluster->setRad(std::max(std::max(sx, sy), sz) * this->cluster->getRad());
	this->cluster->setHeight((*center_top - *this->cluster->getCenter_base()).getLength());
}


void MeshTexturized::translation(double tx, double ty, double tz) {
	for (Vector* v : this->initial_vertices) {
		*v = v->translation(tx, ty, tz);
	}

	Vector* center_base = this->cluster->initial_center_base;
	*center_base = center_base->translation(tx, ty, tz);
}


void MeshTexturized::rotX(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->rotX(a);
	}

	Vector ct = *this->cluster->initial_center_base + (*this->cluster->initial_direction * this->cluster->initial_height);
	Vector* center_top = new Vector(ct.getCoordinate(0), ct.getCoordinate(1), ct.getCoordinate(2));
	*center_top = center_top->rotX(a);

	Vector* center_base = this->cluster->initial_center_base;
	*center_base = center_base->rotX(a);

	Vector directionNotNormalized = (*center_top - *this->cluster->initial_center_base);
	Vector directionNormalized = directionNotNormalized / (directionNotNormalized.getLength());
	Vector* direction = new Vector(directionNormalized.getCoordinate(0), directionNormalized.getCoordinate(1), directionNormalized.getCoordinate(2));
	this->cluster->setDirection(direction);
}


void MeshTexturized::rotY(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->rotY(a);
	}

	Vector ct = *this->cluster->initial_center_base + (*this->cluster->initial_direction * this->cluster->initial_height);
	Vector* center_top = new Vector(ct.getCoordinate(0), ct.getCoordinate(1), ct.getCoordinate(2));
	*center_top = center_top->rotY(a);

	Vector* center_base = this->cluster->initial_center_base;
	*center_base = center_base->rotY(a);

	Vector directionNotNormalized = (*center_top - *this->cluster->initial_center_base);
	Vector directionNormalized = directionNotNormalized / (directionNotNormalized.getLength());
	Vector* direction = new Vector(directionNormalized.getCoordinate(0), directionNormalized.getCoordinate(1), directionNormalized.getCoordinate(2));
	this->cluster->setDirection(direction);
}


void MeshTexturized::rotZ(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->rotZ(a);
	}

	Vector ct = *this->cluster->initial_center_base + (*this->cluster->initial_direction * this->cluster->initial_height);
	Vector* center_top = new Vector(ct.getCoordinate(0), ct.getCoordinate(1), ct.getCoordinate(2));
	*center_top = center_top->rotZ(a);

	Vector* center_base = this->cluster->initial_center_base;
	*center_base = center_base->rotZ(a);

	Vector directionNotNormalized = (*center_top - *this->cluster->initial_center_base);
	Vector directionNormalized = directionNotNormalized / (directionNotNormalized.getLength());
	Vector* direction = new Vector(directionNormalized.getCoordinate(0), directionNormalized.getCoordinate(1), directionNormalized.getCoordinate(2));
	this->cluster->setDirection(direction);
}


void MeshTexturized::shearingYX(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingYX(a);
	}

	this->cluster = nullptr;
}


void MeshTexturized::shearingXY(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingXY(a);
	}

	this->cluster = nullptr;
}


void MeshTexturized::shearingYZ(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingYZ(a);
	}

	this->cluster = nullptr;
}


void MeshTexturized::shearingZY(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingZY(a);
	}

	this->cluster = nullptr;
}


void MeshTexturized::shearingXZ(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingXZ(a);
	}

	this->cluster = nullptr;
}


void MeshTexturized::shearingZX(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingZX(a);
	}

	this->cluster = nullptr;
}


void MeshTexturized::reflectionXY() {

	for (Vector* v : this->initial_vertices) {
		*v = v->reflectionXY();
	}

	Vector ct = *this->cluster->initial_center_base + (*this->cluster->initial_direction * this->cluster->initial_height);
	Vector* center_top = new Vector(ct.getCoordinate(0), ct.getCoordinate(1), ct.getCoordinate(2));
	*center_top = center_top->reflectionXY();

	Vector* center_base = this->cluster->initial_center_base;
	*center_base = center_base->reflectionXY();

	Vector directionNotNormalized = (*center_top - *this->cluster->initial_center_base);
	Vector directionNormalized = directionNotNormalized / (directionNotNormalized.getLength());
	Vector* direction = new Vector(directionNormalized.getCoordinate(0), directionNormalized.getCoordinate(1), directionNormalized.getCoordinate(2));
	this->cluster->setDirection(direction);
}


void MeshTexturized::reflectionXZ() {

	for (Vector* v : this->initial_vertices) {
		*v = v->reflectionXZ();
	}

	Vector ct = *this->cluster->initial_center_base + (*this->cluster->initial_direction * this->cluster->initial_height);
	Vector* center_top = new Vector(ct.getCoordinate(0), ct.getCoordinate(1), ct.getCoordinate(2));
	*center_top = center_top->reflectionXZ();

	Vector* center_base = this->cluster->initial_center_base;
	*center_base = center_base->reflectionXZ();

	Vector directionNotNormalized = (*center_top - *this->cluster->initial_center_base);
	Vector directionNormalized = directionNotNormalized / (directionNotNormalized.getLength());
	Vector* direction = new Vector(directionNormalized.getCoordinate(0), directionNormalized.getCoordinate(1), directionNormalized.getCoordinate(2));
	this->cluster->setDirection(direction);
}


void MeshTexturized::reflectionYZ() {

	for (Vector* v : this->initial_vertices) {
		*v = v->reflectionYZ();
	}

	Vector ct = *this->cluster->initial_center_base + (*this->cluster->initial_direction * this->cluster->initial_height);
	Vector* center_top = new Vector(ct.getCoordinate(0), ct.getCoordinate(1), ct.getCoordinate(2));
	*center_top = center_top->reflectionYZ();

	Vector* center_base = this->cluster->initial_center_base;
	*center_base = center_base->reflectionYZ();

	Vector directionNotNormalized = (*center_top - *this->cluster->initial_center_base);
	Vector directionNormalized = directionNotNormalized / (directionNotNormalized.getLength());
	Vector* direction = new Vector(directionNormalized.getCoordinate(0), directionNormalized.getCoordinate(1), directionNormalized.getCoordinate(2));
	this->cluster->setDirection(direction);
}


void MeshTexturized::doWorldToCamera(Camera* camera) {

	for (int i = 0; i < this->vertices.size(); i++) {
		*this->vertices[i] = Vector(camera->worldToCamera(*this->initial_vertices[i]));
	}

	this->cluster->doWorldToCamera(camera);

}


bool MeshTexturized::inside(Vector* p) {

	return this->cluster->inside(p);

}


MeshTexturized::MeshTexturized(Vector* kd, Vector* ke, Vector* ka, double shininess, Cluster* cluster) {
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
	this->cluster = cluster;
	this->setObjectType(ObjectType::MESH_TEXTURIZED);
}


MeshTexturized::~MeshTexturized() {
	for (FaceTexturized* f : this->getFaces()) {
		delete f;
	}

	for (Edge* e : this->getEdges()) {
		delete e;
	}

	for (Vector* v : this->getVertices()) {
		delete v;
	}

	for (Vector* iv : this->initial_vertices) {
		delete iv;
	}

	delete this->cluster;
}
