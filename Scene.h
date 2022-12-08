#pragma once

#include "Object.h"
#include "Light.h"
#include "Vector.h"
#include <vector>
#include <SDL.h>


class Scene {
private:

    double hWindow = 60.0;
    double wWindow = 60.0;

    int nLin = 500;
    int nCol = 500;

    double dWindow = 30.0;

    std::vector<Object*> objects;

    std::vector<Light*> lights;

    Vector* environmentLight = nullptr;

    Color* bgColor = nullptr;

    Camera* cameraTo = nullptr;

    void paintCanvas(SDL_Renderer* renderer);

public:

    void setEye(Vector* eye);
    Vector* getEye();

    void setHWindow(double hWindow);
    double getHWindow();

    void setWWindow(double wWindow);
    double getWWindow();

    void setNLin(int nLin);
    int getNLin();

    void setNCol(int nCol);
    int getNCol();

    void setDWindow(double dWindow);
    double getDWindow();

    void setBGColor(Color* bgColor);
    Color* getBGColor();

    void setEnvironmentLight(Vector* environmentLight);
    Vector* getEnvironmentLight();

    void addLight(Light* light);
    std::vector<Light*> getLights();

    void addObject(Object* object);
    std::vector<Object*> getObjects();

    void preparePaint();

    void camera(Vector* eye, Vector* at, Vector* up);
    
    Scene(double hWindow, double wWindow, int nLin, int nCol, double dWindow, Color* bgColor = nullptr);
};
