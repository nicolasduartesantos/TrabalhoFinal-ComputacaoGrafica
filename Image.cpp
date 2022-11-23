#include "Image.h"

void Image::imageRec(string imgPath) {
	//SDL_Surface* image = IMG_load(imgPath.c_str());
}

Color Image::getColor(int x, int y) {

}

int Image::getW() {
	return this->image->w;
}

int Image::getH() {
	return this->image->h;
}

Image::Image(string imgPath) {
	this->imageRec(imgPath);
}