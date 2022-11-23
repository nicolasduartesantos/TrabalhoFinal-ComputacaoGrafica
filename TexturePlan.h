#pragma once

#include "Plan.h"
#include "Image.h"


class TexturePlan : public Plan {
private:

	Image* texture = nullptr;

public:

	void setTexture(Image* texture);
	Image* getTexture();

	Color* getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Vector* environmentLight);

	TexturePlan(Image* texture, Vector* p_pi, Vector* normal, double shininess);
};
