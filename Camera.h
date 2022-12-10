#pragma once

#include "Vector.h"

class Camera {
private:

	Vector* eye = nullptr;
	Vector* at = nullptr;
	Vector* up = nullptr;

public:

	void setEye(Vector* eye);
	Vector* getEye();

	void setAt(Vector* at);
	Vector* getAt();

	void setUp(Vector* up);
	Vector* getUp();

	Vector worldToCamera(Vector world);

	Camera(Vector* eye, Vector* at, Vector* up);

	~Camera();

};
