#include "Scene.h"
#include "Object.h"
#include "Light.h"
#include "Vector.h"
#include "libSDL.h"
#include <vector>
#include <SDL.h>
#include <iostream>

void Scene::setEye(Vector* eye) {
    this->eye = eye;
}

Vector* Scene::getEye() {
    return this->eye;
}


void Scene::setHWindow(double hWindow) {
    this->hWindow = hWindow;
}

double Scene::getHWindow() {
    return this->hWindow;
}


void Scene::setWWindow(double wWindow) {
    this->wWindow = wWindow;
}

double Scene::getWWindow() {
    return this->wWindow;
}


void Scene::setNLin(int nLin) {
    this->nLin = nLin;
}

double Scene::getNLin() {
    return this->nLin;
}


void Scene::setNCol(int nCol) {
    this->nCol = nCol;
}

double Scene::getNCol() {
    return this->nCol;
}


void Scene::setDWindow(double dWindow) {
    this->dWindow = dWindow;
}

double Scene::getDWindow() {
    return this->dWindow;
}


void Scene::setBGColor(Color* bgColor) {
    this->bgColor = bgColor;
}

Color* Scene::getBGColor() {
    return this->bgColor;
}


void Scene::setEnvironmentLight(Vector* environmentLight) {
    this->environmentLight = environmentLight;
}

Vector* Scene::getEnvironmentLight() {
    return this->environmentLight;
}


void Scene::setKA(Vector* ka) {
    this->ka = ka;
}
Vector* Scene::getKA() {
    return this->ka;
}


void Scene::addLight(Light* light) {
    this->lights.push_back(light);
}

std::vector<Light*> Scene::getLights() {
    return this->lights;
}


void Scene::addObject(Object* object) {
    this->objects.push_back(object);
}

std::vector<Object*> Scene::getObjects() {
    return this->objects;
}


void Scene::paintCanvas(SDL_Renderer* renderer) {

    double nLin = this->getNLin();
    double nCol = this->getNCol();

    double hWindow = this->getHWindow();
    double wWindow = this->getWWindow();
    double dWindow = this->getDWindow();

    double dx = wWindow / nCol;
    double dy = hWindow / nLin;


    for (int l = 0; l < nLin; l++) {

        double y = (hWindow / 2.) - (dy / 2.) - (l * dy);

        for (int c = 0; c < nCol; c++) {

            double x = (-wWindow / 2.) + (dx / 2.) + (c * dx);

            Vector* p0 = new Vector(*this->getEye());
            Vector* p = new Vector(x, y, -dWindow);

            Vector dirtemp = ((*p - *p0) / ((*p - *p0).getLength()));
            Vector* dir = &dirtemp;


            int iClosest = 0;
            Object* closest = this->getObjects()[0];
            closest->setHasIntersection(false);


            for (int i = 0; i < this->getObjects().size(); i++) {
                //std::cout << "antes de intersect\n";
                (this->getObjects()[i])->intersect(p0, dir);
                //std::cout << this->getObjects()[i]->getIntersectionPoint() << " " << (int)(this->getObjects()[i]->getObjectType()) << '\n';

                if ((this->getObjects()[i])->getHasIntersection() &&
                    (!closest->getHasIntersection() || ((this->getObjects()[i])->getP0distance() < closest->getP0distance()))) {

                    closest = this->getObjects()[i];

                    int iClosest = i;
                }

            }

            if (closest->getHasIntersection()) {
                Color* color = (this->getObjects()[iClosest])->getRGB(this->getLights(), this->getObjects(), p0, dir, this->environmentLight, this->getKA());
                drawColor(renderer, color->r, color->g, color->b, 255);
                drawPoint(renderer, c, l);
            }
        }
    }
}


void Scene::preparePaint() {

    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;

    init(&renderer, &window, this->getNCol(), this->getNLin());

    background(renderer, this->bgColor->r, this->bgColor->g, this->bgColor->b, 255);

    this->paintCanvas(renderer);

    present(renderer);

    destroy(window);
}


Scene::Scene(Vector* eye, double hWindow, double wWindow, int nLin, int nCol, double dWindow, Vector* ka, Color* bgColor) {
    this->setEye(eye);
    this->setHWindow(hWindow);
    this->setWWindow(wWindow);
    this->setNLin(nLin);
    this->setNCol(nCol);
    this->setDWindow(dWindow);
    this->setKA(ka);

    if (bgColor == nullptr) {
        this->setBGColor(new Color(0, 0, 0));
    }
    else {
        this->setBGColor(bgColor);
    }
}
