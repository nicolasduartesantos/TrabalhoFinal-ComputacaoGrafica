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

	Vector();

    Vector(double x, double y, double z);
};
