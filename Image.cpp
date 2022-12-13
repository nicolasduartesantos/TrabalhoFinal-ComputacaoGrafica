#include "Image.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

void Image::imageRec(std::string imgPath) {
	SDL_Surface* image = IMG_Load(imgPath.c_str());

	if (image == nullptr) { std::cout << "ERRO ao abrir arquivo da imagem.\n"; return; }

	int lockSurf = SDL_LockSurface(image);
	if (lockSurf != 0) {
		std::cout << "ERRO ao colocar textura na cena.\n";
		SDL_FreeSurface(image);
		return;
	}

	if (this->image != nullptr) SDL_FreeSurface(this->image);
	this->image = image;

}

Color Image::getColor(int x, int y) {

	int finalColor;
	int bytesColor = this->image->format->BytesPerPixel;
	Uint8* color = (Uint8*)this->image->pixels + y * this->image->pitch + x * bytesColor;

	if (bytesColor == 1) {
		finalColor = *color;
	}

	else if (bytesColor == 2) {
		finalColor = *((Uint16*)color);
	}

	else if (bytesColor == 3) {
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			finalColor = color[0] << 16 | color[1] << 8 | color[2];
		}
		else {
			finalColor = color[0] | color[1] << 8 | color[2] << 16;
		}
	}

	else if (bytesColor == 4) {
		finalColor = *((Uint32*)color);
	}
	else {
		finalColor = 0;
	}

	SDL_Color rgb;
	SDL_GetRGB(finalColor, this->image->format, &rgb.r, &rgb.g, &rgb.b);
	return Color(rgb.r, rgb.g, rgb.b);

}

int Image::getW() {
	return this->image->w;
}

int Image::getH() {
	return this->image->h;
}

Image::Image(std::string imgPath) {
	this->imageRec(imgPath);
}


Image::~Image() {
	SDL_UnlockSurface(this->image);
	SDL_FreeSurface(this->image);
}
