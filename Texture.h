#pragma once

#include "Plan.h"
#include "Image.h"
#include "Vector.h"

class Texture : public Plan {
private:

	Image* texture = nullptr;

public:

	void setTexture(Image* texture);
	Image* getTexture();

	Color* getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Environment* environmentLight);

	Texture(Image* texture, Vector* p_pi, Vector* normal, double shininess);

	~Texture();
};