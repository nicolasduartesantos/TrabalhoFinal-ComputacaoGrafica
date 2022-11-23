#pragma once
#include <SDL_surface.h>
#include <string>
using namespace std;
#include "Color.h"

class Image {
private:

	SDL_Surface* image = nullptr;

public: 

	void imageRec(string imgPath);

	Color getColor(int x, int y);

	int getW();

	int getH();

	Image(string imgPath);

};
