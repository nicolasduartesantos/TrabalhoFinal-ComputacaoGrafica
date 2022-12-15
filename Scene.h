#pragma once

#include "Object.h"
#include "Light.h"
#include "Vector.h"
#include "Camera.h"
#include "Image.h"
#include <vector>
#include <SDL.h>
#include "Interaction.h"

enum class ProjectionType { ORTHOGRAPHIC, PERSPECTIVE };

class Interaction;

class Scene {
private:

    ProjectionType projection = ProjectionType::PERSPECTIVE;

    double hWindow = 100.0;
    double wWindow = 100.0;

    int nLin = 500;
    int nCol = 500;

    double dWindow = 30.0;

    std::vector<Object*> objects;

    std::vector<Light*> lights;

    Environment* environmentLight = nullptr;

    Color* bgColor = nullptr;

    Image* bgImage = nullptr;

    void paintCanvas(SDL_Renderer* renderer);

public:
    Interaction* interaction = nullptr;

    Camera* cameraTo = nullptr;

    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;

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

    void setProjection(ProjectionType projection);
    ProjectionType getProjection();

    void setEnvironmentLight(Environment* environmentLight);
    Environment* getEnvironmentLight();

    void setBGColor(Color* bgColor);
    Color* getBGColor();

    void setBGImage(Image* bgImage);
    Image* getBGImage();

    void addLight(Light* light);
    std::vector<Light*> getLights();

    void addObject(Object* object);
    std::vector<Object*> getObjects();

    void preparePaint();

    void mainLoop();

    void camera(Vector* eye, Vector* at, Vector* up);

    Scene(double hWindow, double wWindow, int nLin, int nCol, double dWindow, Color* bgColor = nullptr);

    ~Scene();
};