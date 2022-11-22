#include "Cone.h"
#include <iostream>

void Cone::setRad(double rad) {
	this->rad = rad;
}
double Cone::getRad() {
	return this->rad;
}


void Cone::setCenter_base(Vector* center_base) {
	this->center_base = center_base;
}
Vector* Cone::getCenter_base() {
	return this->center_base;
}


void Cone::setDirection(Vector* direction) {
	this->direction = direction;
}
Vector* Cone::getDirection() {
	return this->direction;
}


void Cone::setHeight(double height) {
	this->height = height;
}
double Cone::getHeight() {
	return this->height;
}


bool Cone::intersect(Vector* p0, Vector* dir) {

	// VERIFICANDO INTERSEÇÃO BASE

	double verParallel = dir->scalarProd(*this->direction);

	double tBase;
	Vector* piBase = new Vector();
	double distancePiBaseP0;
	bool interceptsBase = false;

	if (verParallel != 0) {
		tBase = (((*p0 - *this->center_base).scalarProd(*this->direction)) / verParallel) * (-1);

		Vector piBaseTemp = *p0 + *dir * tBase;
		piBase = new Vector(piBaseTemp.getCoordinate(0), piBaseTemp.getCoordinate(1), piBaseTemp.getCoordinate(2));

		distancePiBaseP0 = (*piBase - *p0).getLength();

		if ((*piBase - *this->center_base).getLength() <= this->rad) {
			interceptsBase = true;
		}
	}



	Vector v = (*this->vertex - *p0);
	double cos2 = (this->cos * this->cos);

	double delta, t1, t2;

	double a = ((dir->scalarProd(*this->direction)) * (dir->scalarProd(*this->direction))) - ( (dir->scalarProd(*dir)) * cos2 );
	double b = (v.scalarProd(*dir) * cos2) - ((v.scalarProd(*this->direction)) * (dir->scalarProd(*this->direction)));
	double c = ((v.scalarProd(*this->direction)) * (v.scalarProd(*this->direction))) - ( v.scalarProd(v) * cos2 );

	delta = (b * b) - a * c;


	if (a == 0) {

		double t = -c / (2 * b);

		Vector pitemp = (*p0) + ((*dir) * t);
		Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));

		Vector distancePiP0Vector = (*p0) - (*pi);
		double distancePiP0 = distancePiP0Vector.getLength();

		double ver = (*this->vertex - *pi).scalarProd(*this->direction);

		if (ver >= 0 and ver <= this->height) {

			if (interceptsBase && distancePiBaseP0 < distancePiP0) {
				if (tBase < 0) {
					this->setHasIntersection(false);
					return false;
				}

				this->setP0distance(distancePiBaseP0);
				this->setT(tBase);
				this->setIntersectionPoint(piBase);
				this->setObjectSurface(ObjectSurface::CONE_BASE);
				this->setHasIntersection(true);
				return true;
			}

			else {
				if (t < 0) {
					this->setHasIntersection(false);
					return false;
				}

				this->setP0distance(distancePiP0);
				this->setT(t);
				this->setIntersectionPoint(pi);
				this->setObjectSurface(ObjectSurface::CONE_SURFACE);
				this->setHasIntersection(true);
				return true;
			}
		}
	}




	// DELTA = 0
	if (delta == 0)
	{
		this->setHasIntersection(false);
		return false;
	}

	// DELTA > 0
	else if (delta > 0)
	{
		this->setHasIntersection(true);
		t1 = (-b + sqrt(delta)) / (a);
		t2 = (-b - sqrt(delta)) / (a);

		Vector pitemp1 = (*p0) + ((*dir) * t1);
		Vector* pi1 = new Vector(pitemp1.getCoordinate(0), pitemp1.getCoordinate(1), pitemp1.getCoordinate(2));

		Vector pitemp2 = (*p0) + ((*dir) * t2);
		Vector* pi2 = new Vector(pitemp2.getCoordinate(0), pitemp2.getCoordinate(1), pitemp2.getCoordinate(2));

		Vector distancePi1P0Vector = (*p0) - (*pi1);
		Vector distancePi2P0Vector = (*p0) - (*pi2);
		double distancePi1P0 = distancePi1P0Vector.getLength();
		double distancePi2P0 = distancePi2P0Vector.getLength();

		double ver1 = (*this->vertex - *pi1).scalarProd(*this->direction);
		double ver2 = (*this->vertex - *pi2).scalarProd(*this->direction);

		// CASO 1
		if ((ver1 >= 0 and ver1 <= this->height) and (ver2 >= 0 and ver2 <= this->height)) {

			if (distancePi1P0 < distancePi2P0) {

				if (t1 < 0) {
					this->setHasIntersection(false);
					return false;
				}

				this->setP0distance(distancePi1P0);
				this->setT(t1);
				this->setIntersectionPoint(pi1);
				this->setObjectSurface(ObjectSurface::CONE_SURFACE);
				return true;
			}

			else {

				if (t2 < 0) {
					this->setHasIntersection(false);
					return false;
				}

				this->setP0distance(distancePi2P0);
				this->setT(t2);
				this->setIntersectionPoint(pi2);
				this->setObjectSurface(ObjectSurface::CONE_SURFACE);
				return true;
			}

		}

		// CASO 2
		else if ((ver1 >= 0 and ver1 <= this->height) and !(ver2 >= 0 and ver2 <= this->height)) {

			if (interceptsBase) {

				if (distancePi1P0 < distancePiBaseP0) {

					if (t1 < 0) {
						this->setHasIntersection(false);
						return false;
					}

					this->setP0distance(distancePi1P0);
					this->setT(t1);
					this->setIntersectionPoint(pi1);
					this->setObjectSurface(ObjectSurface::CONE_SURFACE);
					return true;

				}

				else {

					if (tBase < 0) {
						this->setHasIntersection(false);
						return false;
					}

					this->setP0distance(distancePiBaseP0);
					this->setT(tBase);
					this->setIntersectionPoint(piBase);
					this->setObjectSurface(ObjectSurface::CONE_BASE);
					return true;

				}

			}

			else {

				if (t1 < 0) {
					this->setHasIntersection(false);
					return false;
				}

				this->setP0distance(distancePi1P0);
				this->setT(t1);
				this->setIntersectionPoint(pi1);
				this->setObjectSurface(ObjectSurface::CONE_SURFACE);
				return true;
			}

		}

		// CASO 3
		else if (!(ver1 >= 0 and ver1 <= this->height) and (ver2 >= 0 and ver2 <= this->height)) {

			if (interceptsBase) {

				if (distancePi2P0 < distancePiBaseP0) {

					if (t2 < 0) {
						this->setHasIntersection(false);
						return false;
					}

					this->setP0distance(distancePi2P0);
					this->setT(t2);
					this->setIntersectionPoint(pi2);
					this->setObjectSurface(ObjectSurface::CONE_SURFACE);
					return true;

				}

				else {

					if (tBase < 0) {
						this->setHasIntersection(false);
						return false;
					}

					this->setP0distance(distancePiBaseP0);
					this->setT(tBase);
					this->setIntersectionPoint(piBase);
					this->setObjectSurface(ObjectSurface::CONE_BASE);
					return true;

				}

			}

			else {

				if (t2 < 0) {
					this->setHasIntersection(false);
					return false;
				}

				this->setP0distance(distancePi2P0);
				this->setT(t2);
				this->setIntersectionPoint(pi2);
				this->setObjectSurface(ObjectSurface::CONE_SURFACE);
				return true;
			}

		}

		// CASO 4
		else {
			this->setHasIntersection(false);
			return false;
		}
	}

	// DELTA < 0
	else {
		this->setHasIntersection(false);
		return false;
	}
}


bool Cone::intersect_for_shadow(Vector* p0, Vector* dir) {

	double verParallel = dir->scalarProd(*this->direction);

	double tBase;

	Vector* piBase = new Vector();

	double distancePiBaseP0;

	bool interceptsBase = false;

	if (verParallel != 0) {
		tBase = (((*p0 - *this->center_base).scalarProd(*this->direction)) / verParallel) * (-1);

		Vector piBaseTemp = *p0 + *dir * tBase;
		piBase = new Vector(piBaseTemp.getCoordinate(0), piBaseTemp.getCoordinate(1), piBaseTemp.getCoordinate(2));

		distancePiBaseP0 = (*piBase - *p0).getLength();

		if ((*piBase - *this->center_base).getLength() <= this->rad) {
			interceptsBase = true;
		}

	}

	double cos2 = this->cos * this->cos;
	double a = ((dir->scalarProd(*this->direction)) * (dir->scalarProd(*this->direction))) - ((dir->scalarProd(*dir)) * cos2);
	Vector v = *this->vertex - *p0;
	double b = (v.scalarProd(*dir) * cos2) - (v.scalarProd(*this->direction) * dir->scalarProd(*this->direction));
	double c = ((v.scalarProd(*this->direction)) * (v.scalarProd(*this->direction))) - (v.scalarProd(v) * cos2);
	double delta = (b * b) - a * c;
	double t1, t2;


	if (a == 0) {

		double t = (-c) / (2 * b);

		Vector pitemp = (*p0) + ((*dir) * t);
		Vector* pi = new Vector(pitemp.getCoordinate(0), pitemp.getCoordinate(1), pitemp.getCoordinate(2));

		Vector distancePiP0Vector = (*p0) - (*pi);
		double distancePiP0 = distancePiP0Vector.getLength();

		double ver = (*this->vertex - *pi).scalarProd(*this->direction);

		if (ver >= 0 and ver <= this->height) {

			if (interceptsBase and distancePiBaseP0 < distancePiP0) {

				if (tBase < 0) {
					this->setHasIntersectionShadow(false);
					return false;
				}

				this->setP0distanceShadow(distancePiBaseP0);
				this->setTShadow(tBase);
				this->setHasIntersectionShadow(true);
				return true;
			}

			else {

				if (t < 0) {
					this->setHasIntersectionShadow(false);
					return false;
				}

				this->setP0distanceShadow(distancePiP0);
				this->setTShadow(t);
				this->setHasIntersectionShadow(true);
				return true;
			}
		}
	}



	if (delta == 0)
	{
		this->setHasIntersectionShadow(false);
		return false;
	}

	else if (delta > 0)
	{

		this->setHasIntersectionShadow(true);
		t1 = (-b + sqrt(delta)) / (a);
		t2 = (-b - sqrt(delta)) / (a);

		Vector pitemp1 = (*p0) + ((*dir) * t1);
		Vector* pi1 = new Vector(pitemp1.getCoordinate(0), pitemp1.getCoordinate(1), pitemp1.getCoordinate(2));

		Vector pitemp2 = (*p0) + ((*dir) * t2);
		Vector* pi2 = new Vector(pitemp2.getCoordinate(0), pitemp2.getCoordinate(1), pitemp2.getCoordinate(2));

		Vector distancePi1P0Vector = (*p0) - (*pi1);
		Vector distancePi2P0Vector = (*p0) - (*pi2);
		double distancePi1P0 = distancePi1P0Vector.getLength();
		double distancePi2P0 = distancePi2P0Vector.getLength();

		double ver1 = (*pi1 - *this->center_base).scalarProd(*this->direction);
		double ver2 = (*pi2 - *this->center_base).scalarProd(*this->direction);

		// CASO 1
		if ((ver1 >= 0 and ver1 <= this->height) and (ver2 >= 0 and ver2 <= this->height)) {

			if (distancePi1P0 < distancePi2P0) {

				if (t1 < 0) {
					this->setHasIntersectionShadow(false);
					return false;
				}

				this->setP0distanceShadow(distancePi1P0);
				this->setTShadow(t1);
				return true;
			}

			else {

				if (t2 < 0) {
					this->setHasIntersectionShadow(false);
					return false;
				}

				this->setP0distanceShadow(distancePi2P0);
				this->setTShadow(t2);
				return true;
			}

		}

		// CASO 2
		else if ((ver1 >= 0 and ver1 <= this->height) and !(ver2 >= 0 and ver2 <= this->height)) {

			if (interceptsBase) {

				if (distancePi1P0 < distancePiBaseP0) {

					if (t1 < 0) {
						this->setHasIntersectionShadow(false);
						return false;
					}

					this->setP0distanceShadow(distancePi1P0);
					this->setTShadow(t1);
					return true;

				}

				else {

					if (tBase < 0) {
						this->setHasIntersectionShadow(false);
						return false;
					}

					this->setP0distanceShadow(distancePiBaseP0);
					this->setTShadow(tBase);
					return true;

				}

			}

			else {

				if (t1 < 0) {
					this->setHasIntersectionShadow(false);
					return false;
				}

				this->setP0distanceShadow(distancePi1P0);
				this->setTShadow(t1);
				return true;

			}
		}

		// CASO 3
		else if (!(ver1 >= 0 and ver1 <= this->height) and (ver2 >= 0 and ver2 <= this->height)) {

			if (interceptsBase) {

				if (distancePi2P0 < distancePiBaseP0) {

					if (t2 < 0) {
						this->setHasIntersectionShadow(false);
						return false;
					}

					this->setP0distanceShadow(distancePi2P0);
					this->setTShadow(t2);
					return true;

				}

				else {

					if (tBase < 0) {
						this->setHasIntersectionShadow(false);
						return false;
					}

					this->setP0distanceShadow(distancePiBaseP0);
					this->setTShadow(tBase);
					return true;

				}

			}

			else {

				if (t2 < 0) {
					this->setHasIntersectionShadow(false);
					return false;
				}

				this->setP0distanceShadow(distancePi2P0);
				this->setTShadow(t2);
				return true;

			}
		}

		// CASO 4
		else {
			this->setHasIntersectionShadow(false);
			return false;
		}

	}

	// DELTA < 0
	else {
		this->setHasIntersectionShadow(false);
		return false;
	}

}


Color* Cone::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight) {

	if (this->surface == ObjectSurface::CONE_BASE) {

		Vector* normal = new Vector(*this->direction * (-1));
		return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, normal, this);

	}

	else {

		Vector pi = *this->getIntersectionPoint();
		Vector vertexMinusPi = (*this->vertex - pi);
		Vector result_temp = vertexMinusPi.product(*this->direction);
		Vector normaltemp = result_temp.product(vertexMinusPi);
		normaltemp = normaltemp / normaltemp.getLength();

		Vector* normal = new Vector(normaltemp.getCoordinate(0), normaltemp.getCoordinate(1), normaltemp.getCoordinate(2));
		return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, normal, this);

	}

}


Cone::Cone(double rad, Vector* center_base, Vector* direction, double height, Vector* kd, Vector* ke, Vector* ka, double shininess) {
	this->rad = rad;
	this->center_base = center_base;
	Vector directionTemp = *direction / direction->getLength();
	this->direction = new Vector(directionTemp.getCoordinate(0), directionTemp.getCoordinate(1), directionTemp.getCoordinate(2));
	this->height = height;
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
	Vector v_temp = *center_base + *direction * height;
	this->vertex = new Vector(v_temp.getCoordinate(0), v_temp.getCoordinate(1), v_temp.getCoordinate(2));
	this->cos = height / sqrt(rad * rad + height * height);
}


Cone::Cone(double rad, Vector* center_base, Vector* direction, double height, Vector* vertex, Vector* kd, Vector* ke, Vector* ka, double shininess) {
	this->rad = rad;
	this->center_base = center_base;
	Vector directionTemp = *direction / direction->getLength();
	this->direction = new Vector(directionTemp.getCoordinate(0), directionTemp.getCoordinate(1), directionTemp.getCoordinate(2));
	this->height = height;
	this->vertex = vertex;
	this->kd = kd;
	this->ke = ke;
	this->ka = ka;
	this->shininess = shininess;
	this->cos = height / sqrt(rad * rad + height * height);
}
