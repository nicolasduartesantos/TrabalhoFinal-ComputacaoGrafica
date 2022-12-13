#include "Scene.h"
#include "Object.h"
#include "Light.h"
#include "Vector.h"
#include "libSDL.h"
#include "Image.h"
#include "Interaction.h"
#include <vector>
#include <SDL.h>
#include <iostream>
#include "Interaction.cpp"

void Scene::setEye(Vector* eye) {
    this->cameraTo->setEye(eye);
}

Vector* Scene::getEye() {
    return this->cameraTo->getEye();
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

int Scene::getNLin() {
    return this->nLin;
}


void Scene::setNCol(int nCol) {
    this->nCol = nCol;
}

int Scene::getNCol() {
    return this->nCol;
}


void Scene::setDWindow(double dWindow) {
    this->dWindow = dWindow;
}

double Scene::getDWindow() {
    return this->dWindow;
}

void Scene::setProjection(ProjectionType projection) {
    this->projection = projection;
}

ProjectionType Scene::getProjection() {
    return this->projection;
}

void Scene::setEnvironmentLight(Vector* environmentLight) {
    this->environmentLight = environmentLight;
}

Vector* Scene::getEnvironmentLight() {
    return this->environmentLight;
}


void Scene::setBGColor(Color* bgColor) {
    this->bgColor = bgColor;
}

Color* Scene::getBGColor() {
    return this->bgColor;
}


void Scene::setBGImage(Image* bgImage) {
    this->bgImage = bgImage;
}

Image* Scene::getBGImage() {
    return this->bgImage;
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

    Image* bgImage = this->bgImage;

    for (int l = 0; l < nLin; l++) {

        double y = (hWindow / 2.) - (dy / 2.) - (l * dy);

        for (int c = 0; c < nCol; c++) {

            double x = (-wWindow / 2.) + (dx / 2.) + (c * dx);

            Vector* p0 = new Vector();
            Vector* p = new Vector();

            bool perspectiveProjection = this->getProjection() == ProjectionType::PERSPECTIVE;
            if (perspectiveProjection) {
                p0 = new Vector(0, 0, 0);
                p = new Vector(x, y, -dWindow);
            }
            else {
                p0 = new Vector(x, y, 0);
                p = new Vector(x, y, -1);
            }

            Vector dirtemp = ((*p - *p0) / ((*p - *p0).getLength()));
            Vector* dir = &dirtemp;


            int iClosest = 0;
            Object* closest = this->getObjects()[0];
            closest->setHasIntersection(false);

            for (int i = 0; i < this->getObjects().size(); i++) {

                (this->getObjects()[i])->intersect(p0, dir);

                if ((this->getObjects()[i])->getHasIntersection() &&
                    (!closest->getHasIntersection() || ((this->getObjects()[i])->getP0distance() < closest->getP0distance()))) {

                    closest = this->getObjects()[i];

                    iClosest = i;
                }

            }

            if (closest->getHasIntersection()) {
                Color* color = (this->getObjects()[iClosest])->getRGB(this->getLights(), this->getObjects(), p0, dir, this->environmentLight);
                drawColor(renderer, color->r, color->g, color->b, 255);
                drawPoint(renderer, c, l);
            }

            /*
            else if (bgImage != nullptr) {
                double x = (double(c) * double(bgImage->getW())) / this->getWWindow();
                double y = (double(l) * double(bgImage->getH())) / this->getHWindow();
                Color pixel = bgImage->getColor(x, y);
                drawColor(renderer, pixel.r, pixel.g, pixel.b, 255);
                //std::cout << "passei draw color\n";
                drawPoint(renderer, c, l);
                //std::cout << "passei draw point\n";
            }
            */
        }
    }
}


void Scene::preparePaint() {

    background(renderer, this->bgColor->r, this->bgColor->g, this->bgColor->b, 255);
    this->renderer = renderer;
    this->window = window;

    this->paintCanvas(renderer);
}

void Scene::mainLoop() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return;
    }

    // Setup window
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, nCol, nLin, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return;
    }
    //SDL_RendererInfo info;
    //SDL_GetRendererInfo(renderer, &info);
    //SDL_Log("Current SDL_Renderer: %s", info.name);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();


    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    bool change = true;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGuiColorEditFlags picker_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_Float;
        ImGuiWindowFlags window_flags = 0;

        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoSavedSettings;


        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(260, 140), ImGuiCond_Once);

        static bool show_window = true;

        ImGui::Begin("Menu", NULL, window_flags);
        ImGui::Text("Escolha o que deseja alterar:");


        if (ImGui::CollapsingHeader("Camera")) {

            Vector* e = this->cameraTo->getEye();
            float eye[3] = { (float)e->getCoordinate(0), (float)e->getCoordinate(1), (float)e->getCoordinate(2) };

            Vector* a = this->cameraTo->getAt();
            float at[3] = { (float)a->getCoordinate(0),(float)a->getCoordinate(1), (float)a->getCoordinate(2) };

            Vector* u = this->cameraTo->getUp();
            float up[3] = { (float)u->getCoordinate(0), (float)u->getCoordinate(1), (float)u->getCoordinate(2) };

            ImGui::InputFloat3("eye", eye);
            if (ImGui::IsItemDeactivatedAfterEdit()) {
                Vector* newEye = new Vector(eye[0], eye[1], eye[2]);
                Vector* newAt = new Vector(at[0], at[1], at[2]);
                Vector* newUp = new Vector(up[0], up[1], up[2]);
                this->camera(newEye, newAt, newUp);
                change = true;
            }

            ImGui::InputFloat3("at", at);
            if (ImGui::IsItemDeactivatedAfterEdit()) {
                Vector* newEye = new Vector(eye[0], eye[1], eye[2]);
                Vector* newAt = new Vector(at[0], at[1], at[2]);
                Vector* newUp = new Vector(up[0], up[1], up[2]);
                this->camera(newEye, newAt, newUp);
                change = true;
            }

            ImGui::InputFloat3("up", up);
            if (ImGui::IsItemDeactivatedAfterEdit()) {
                Vector* newEye = new Vector(eye[0], eye[1], eye[2]);
                Vector* newAt = new Vector(at[0], at[1], at[2]);
                Vector* newUp = new Vector(up[0], up[1], up[2]);
                this->camera(newEye, newAt, newUp);
                change = true;
            }
        }

        //if (ImGui::CollapsingHeader("Material")) {
            //mdmaterial
        //}

        if (ImGui::CollapsingHeader("Lights")) {
            //mdmaterial
        }

        if (ImGui::CollapsingHeader("Picking")) {
            //mdcamera
            //Object* o = this->interaction->picking();

        }

        if (ImGui::CollapsingHeader("Projection")) {

            if (ImGui::Button("Perspective")) {
                this->setProjection(ProjectionType::PERSPECTIVE);
                change = true;
            }

            ImGui::SameLine();

            if (ImGui::Button("Orthographic")) {
                this->setProjection(ProjectionType::ORTHOGRAPHIC);
                change = true;
            }
        }

        ImGui::End();

        // Rendering
        ImGui::Render();
        if (change) {
            preparePaint(); change = false;
        }
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);

    }

    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return;

}



void Scene::camera(Vector* eye, Vector* at, Vector* up) {
    delete this->cameraTo;
    this->cameraTo = new Camera(eye, at, up);

    for (Object* o : this->objects) o->doWorldToCamera(this->cameraTo);

    for (Light* l : this->lights) l->doWorldToCamera(this->cameraTo);

}


Scene::Scene(double hWindow, double wWindow, int nLin, int nCol, double dWindow, Color* bgColor) {
    this->setHWindow(hWindow);
    this->setWWindow(wWindow);
    this->setNLin(nLin);
    this->setNCol(nCol);
    this->setDWindow(dWindow);

    if (bgColor == nullptr) {
        this->setBGColor(new Color(0, 0, 0));
    }
    else {
        this->setBGColor(bgColor);
    }

    this->cameraTo = new Camera(new Vector(0, 0, 0), new Vector(0, 0, -1), new Vector(0, 1, 0));
}


Scene::~Scene() {
    delete this->getEnvironmentLight();
    delete this->getBGColor();
    delete this->getBGImage();
    delete this->cameraTo;

    for (auto o = this->objects.begin(); o != this->objects.end(); o++) { delete (*o); }

    for (auto l = this->lights.begin(); l != this->lights.end(); l++) { delete (*l); }
}