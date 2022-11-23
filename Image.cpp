#include "Image.h"
#include <SDL.h>
#include <SDL_image.h>

void imageRec(std::string imgPath) {
	SDL_Surface* image = IMG_Load(imgPath.c_str());
}

Color getColor(int x, int y) {

}

int getW() {
	return this->image->w;
}

int getH() {
	return this->image->h;
}

Image(std::string imgPath) {
	this->loadImage(imgPath);
}