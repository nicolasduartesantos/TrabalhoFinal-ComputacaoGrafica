#include "Mesh2.h"
#include "Face.h"
#include "Edge.h"
#include "Vector.h"
#include "Camera.h"
#include <iostream>
#include <cmath>

void Mesh2::addFace(Face2* face) {
	this->faces.push_back(face);
}
std::vector<Face2*> Mesh2::getFaces() {
	return this->faces;
}




void Mesh2::addVertex(Vector* vertex) {
	this->vertices.push_back(vertex);
}
std::vector<Vector*> Mesh2::getVertices() {
	return this->vertices;
}


void Mesh2::setNormal(Vector* normal) {
	this->normal = normal;
}

Vector* Mesh2::getNormal() {
	return this->normal;
}




bool Mesh2::intersect(Vector* p0, Vector* dir) {

	//this->setP0distance(std::numeric_limits<double>::infinity());

	if (this->cluster != nullptr) {
		if (!this->cluster->intersect(p0, dir) and !this->cluster->inside(p0)) {
			this->setHasIntersection(false);
			return false;
		}
	}

	this->setObjectSurface(ObjectSurface::ON_PLAN);
	this->setHasIntersection(false);
	Vector* meshNormal = new Vector();
	
	for (Face2* face : this->getFaces()) {

		Vector p1 = *this->vertices[face->idVertices[0]];
		Vector p2 = *this->vertices[face->idVertices[1]];
		Vector p3 = *this->vertices[face->idVertices[2]];

		

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


bool Mesh2::intersect_for_shadow(Vector* p0, Vector* dir) {
	//this->setP0distanceShadow(std::numeric_limits<double>::infinity());
	if (this->cluster != nullptr) {
		if (!this->cluster->intersect_for_shadow(p0, dir) and !this->cluster->inside(p0)) {
			this->setHasIntersectionShadow(false);
			return false;
		}
	}
	this->setHasIntersectionShadow(false);
	Vector* meshNormal = new Vector();

	for (Face2* face : this->getFaces()) {


		Vector p1 = *this->vertices[face->idVertices[0]];
		Vector p2 = *this->vertices[face->idVertices[1]];
		Vector p3 = *this->vertices[face->idVertices[2]];

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


Color* Mesh2::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Environment* environmentLight) {

	return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, this->normal, this);

}


void Mesh2::scaling(double sx, double sy, double sz) {
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


void Mesh2::translation(double tx, double ty, double tz) {
	for (Vector* v : this->initial_vertices) {
		*v = v->translation(tx, ty, tz);
	}

	Vector* center_base = this->cluster->initial_center_base;
	*center_base = center_base->translation(tx, ty, tz);
}


void Mesh2::rotX(double a) {
	this->translation(0, 100, -160);
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
	this->translation(0, -100, 160);
}


void Mesh2::rotY(double a) {
	this->translation(0, 100, -160);
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
	this->translation(0, -100, 160);
}


void Mesh2::rotZ(double a) {
	this->translation(0, 100, -160);
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
	this->translation(0, -100, 160);
}


void Mesh2::shearingYX(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingYX(a);
	}

	this->cluster = nullptr;
}


void Mesh2::shearingXY(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingXY(a);
	}

	this->cluster = nullptr;
}


void Mesh2::shearingYZ(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingYZ(a);
	}

	this->cluster = nullptr;
}


void Mesh2::shearingZY(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingZY(a);
	}

	this->cluster = nullptr;
}


void Mesh2::shearingXZ(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingXZ(a);
	}

	this->cluster = nullptr;
}


void Mesh2::shearingZX(double a) {
	for (Vector* v : this->initial_vertices) {
		*v = v->shearingZX(a);
	}

	this->cluster = nullptr;
}


void Mesh2::reflectionXY() {
	this->translation(0, 100, -160);
	for (Vector* v : this->initial_vertices) {
		*v = v->reflectionXY();
	}

	for (Face2* face : this->getFaces()) {
		face->idVertices[0] ^= face->idVertices[2];
		face->idVertices[2] ^= face->idVertices[0];
		face->idVertices[0] ^= face->idVertices[2];
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
	this->translation(0, -100, 160);
}


void Mesh2::reflectionXZ() {
	this->translation(0, 100, -160);
	for (Vector* v : this->initial_vertices) {
		*v = v->reflectionXZ();
	}

	for (Face2* face : this->getFaces()) {
		face->idVertices[0] ^= face->idVertices[2];
		face->idVertices[2] ^= face->idVertices[0];
		face->idVertices[0] ^= face->idVertices[2];
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
	this->translation(0, -100, 160);
}


void Mesh2::reflectionYZ() {
	this->translation(0, 100, -160);
	for (Vector* v : this->initial_vertices) {
		*v = v->reflectionYZ();
	}

	for (Face2* face : this->getFaces()) {
		face->idVertices[0] ^= face->idVertices[2];
		face->idVertices[2] ^= face->idVertices[0];
		face->idVertices[0] ^= face->idVertices[2];
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
	this->translation(0, -100, 160);
}


void Mesh2::doWorldToCamera(Camera* camera) {

	for (int i = 0; i < this->vertices.size(); i++) {
		*this->vertices[i] = Vector(camera->worldToCamera(*this->initial_vertices[i]));
		//std::cout << this->initial_vertices[i]->getCoordinate(0) << " " << this->initial_vertices[i]->getCoordinate(1) << " " << this->initial_vertices[i]->getCoordinate(2) << '\n';
	}

	this->cluster->doWorldToCamera(camera);

}


bool Mesh2::inside(Vector* p) {

	return this->cluster->inside(p);

}


Mesh2::Mesh2(Vector* kd, Vector* ke, Vector* ka, double shininess, Cluster* cluster) {
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
	this->cluster = cluster;
	this->setObjectType(ObjectType::MESH2);
}


Mesh2::~Mesh2() {
	for (Face2* f : this->getFaces()) {
		delete f;
	}

	for (Vector* v : this->getVertices()) {
		delete v;
	}

	for (Vector* iv : this->initial_vertices) {
		delete iv;
	}

	delete this->cluster;
}