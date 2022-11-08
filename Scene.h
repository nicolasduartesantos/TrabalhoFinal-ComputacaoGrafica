#pragma once

#include "Object.h"
#include "Light.h"
#include "Vector.h"
#include <vector>
#include <SDL.h>


class Scene {
private:
    Vector* eye = nullptr;

    double hWindow = 60.0;
    double wWindow = 60.0;

    int nLin = 500;
    int nCol = 500;

    double dWindow = 30.0;

    std::vector<Object*> objects;

    std::vector<Light*> lights;

    Vector* environmentLight = nullptr;
    Vector* ka = nullptr;

    Color* bgColor = nullptr;

    void paintCanvas(SDL_Renderer* renderer);

public:

    void setEye(Vector* eye);
    Vector* getEye();

    void setHWindow(double hWindow);
    double getHWindow();

    void setWWindow(double wWindow);
    double getWWindow();

    void setNLin(int nLin);
    double getNLin();

    void setNCol(int nCol);
    double getNCol();

    void setDWindow(double dWindow);
    double getDWindow();

    void setBGColor(Color* bgColor);
    Color* getBGColor();

    void setEnvironmentLight(Vector* environmentLight);
    Vector* getEnvironmentLight();

    void setKA(Vector* ka);
    Vector* getKA();

    void addLight(Light* light);
    std::vector<Light*> getLights();

    void addObject(Object* object);
    std::vector<Object*> getObjects();

    void preparePaint();

    Scene(Vector* eye, double hWindow, double wWindow, int nLin, int nCol, double dWindow, Vector* ka, Color* bgColor = nullptr);
};
