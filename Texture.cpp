#include "Texture.h"
#include "Vector.h"
#include <iostream>

void Texture::setTexture(Image* texture) {
    this->texture = texture;
}
Image* Texture::getTexture() {
    return this->texture;
}


Color* Texture::getRGB(std::vector<Light*> lights, std::vector<Object*> objects, Vector* p0, Vector* dir, Environment* environmentLight) {

    Vector* normal = this->getNormal();
    Vector* pi = this->getIntersectionPoint();
    Vector piMinusp_pi = *pi - *this->getP_PI();
    Vector piMinusp_pi2 = piMinusp_pi;

    if (normal->getCoordinate(0) != 0 || normal->getCoordinate(2) != 0) {

        Vector normalWithYRotated = normal->rotY(-asin(normal->getCoordinate(0) / (sqrt(pow(normal->getCoordinate(0), 2.0) + pow(normal->getCoordinate(2), 2.0)))));

        Vector piMinusp_piWithYRotated = piMinusp_pi.rotY(-asin(normal->getCoordinate(0) / (sqrt(pow(normal->getCoordinate(0), 2.0) + pow(normal->getCoordinate(2), 2.0)))));

        piMinusp_pi2 = piMinusp_piWithYRotated.rotX(-acos(normalWithYRotated.getCoordinate(1)));

    }

    int x = (int)piMinusp_pi2.getCoordinate(0);
    int z = (int)piMinusp_pi2.getCoordinate(2);

    int posPixelX;
    int posPixelY;

    if (x < 0) {
        posPixelX = this->texture->getW() - (abs(x) % this->texture->getW());
    }
    else {
        posPixelX = (abs(x) % this->texture->getW());
    }

    if (z < 0) {
        posPixelY = this->texture->getH() - (abs(z) % this->texture->getH());
    }
    else {
        posPixelY = (abs(z) % this->texture->getH());
    }

    Color pixel = this->texture->getColor(posPixelX, posPixelY);

    double r = (pixel.r / 255.0);
    double g = (pixel.g / 255.0);
    double b = (pixel.b / 255.0);

    Vector* pixelColor = new Vector(r, g, b);

    this->kd = pixelColor;
    this->ke = pixelColor;
    this->ka = pixelColor;

    return this->RGBtoPaint(lights, objects, p0, dir, environmentLight, this->normal, this);
}


Texture::Texture(Image* texture, Vector* p_pi, Vector* normal, double shininess) {
    this->texture = texture;
    this->setP_PI(p_pi);
    this->setNormal(normal);
    this->setShininess(shininess);

    this->setObjectType(ObjectType::TEXTURE);

    this->initial_p_pi = new Vector(*this->p_pi);
    this->initial_normal = new Vector(*this->normal);
}


Texture::~Texture() {
    delete this->getTexture();
}