#pragma once

#include <string>
#include "Color.h"
#include <SDL_image.h>

class Image {
private:
	SDL_Surface* image = nullptr;

public:
	void imageRec(std::string imgPath);

	Color getColor(int x, int y);

	int getW();
	int getH();

	Image(std::string imgPath);

	~Image();
};
