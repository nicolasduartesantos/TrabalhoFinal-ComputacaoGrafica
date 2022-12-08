#pragma once

#include <vector>

class Vector {
private: 
    double coordinates[3];

public:

	void setCoordinate(int index, int x);
	double getCoordinate(int index);

    double getLength();

    double scalarProd(Vector b);

	Vector product(Vector b);

	bool operator == (const Vector& b);
	Vector operator + (const Vector& b);
	Vector operator - (const Vector& b);
	Vector operator * (const Vector& b);
	Vector operator / (const Vector& b);
	Vector operator * (const double& b);
	Vector operator / (const double& b);

	Vector rotX(double a);
	Vector rotY(double a);
	Vector rotZ(double a);

	Vector translation(double tx, double ty, double tz);

	Vector scaling(double sx, double sy, double sz);

	Vector shearingYX(double a);
	Vector shearingXY(double a);
	Vector shearingYZ(double a);
	Vector shearingZY(double a);
	Vector shearingXZ(double a);
	Vector shearingZX(double a);

	Vector reflectionXY();
	Vector reflectionXZ();
	Vector reflectionYZ();

	Vector();

    Vector(double x, double y, double z);
};
