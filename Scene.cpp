#include "Scene.h"
#include "Object.h"
#include "Light.h"
#include "Vector.h"
#include "libSDL.h"
#include "Image.h"
#include "Interaction.h"
#include "Sphere.h"
#include "Plan.h"
#include "Texture.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Mesh.h"
#include "Mesh2.h"
#include "MeshTexturized.h"
#include <vector>
#include <SDL.h>
#include <iostream>




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


void Scene::setEnvironmentLight(Environment* environmentLight) {
    this->environmentLight = environmentLight;
}
Environment* Scene::getEnvironmentLight() {
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
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->nCol, this->nLin, 0);
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
    bool perspective = true;
    bool orthographic = false;
    int num;

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
        ImGui::SetNextWindowSize(ImVec2(220, 110), ImGuiCond_Once);

        static bool show_window = true;
        bool show_another_window = false;

        ImGui::Begin("Menu", NULL, window_flags);


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

                if ((eye[2] <= 0 or eye[2] >= 400) or (eye[0] <= -200 or eye[0] >= 200) or (eye[1] <= -150 or eye[1] >= 50)) {
                    std::cout << "\nOBSERVADOR NAO PODE SAIR DA SALA\n\n";
                }
                else {
                    this->camera(newEye, newAt, newUp);
                }
                
            }

            ImGui::InputFloat3("at", at);
            if (ImGui::IsItemDeactivatedAfterEdit()) {
                Vector* newEye = new Vector(eye[0], eye[1], eye[2]);
                Vector* newAt = new Vector(at[0], at[1], at[2]);
                Vector* newUp = new Vector(up[0], up[1], up[2]);
                this->camera(newEye, newAt, newUp);
            }

            ImGui::InputFloat3("up", up);
            if (ImGui::IsItemDeactivatedAfterEdit()) {
                Vector* newEye = new Vector(eye[0], eye[1], eye[2]);
                Vector* newAt = new Vector(at[0], at[1], at[2]);
                Vector* newUp = new Vector(up[0], up[1], up[2]);
                this->camera(newEye, newAt, newUp);
            }

            float windowsize[2] = { (float)this->getHWindow(), (float)this->getWWindow() };
            ImGui::InputFloat2("H, W", windowsize);
            if (ImGui::IsItemDeactivatedAfterEdit()) {
                this->setHWindow(windowsize[0]);
                this->setWWindow(windowsize[1]);
                this->setNLin((this->getHWindow() / 100) * 350);
                this->setNCol((this->getWWindow() / 100) * 350);

                ImGui_ImplSDLRenderer_Shutdown();
                ImGui_ImplSDL2_Shutdown();
                ImGui::DestroyContext();
                SDL_DestroyWindow(window);
                SDL_DestroyRenderer(renderer);
                this->mainLoop();
            }

            double d = this->getDWindow();
            ImGui::InputDouble("distancia focal", &d);
            if (ImGui::IsItemDeactivatedAfterEdit()) {
                this->setDWindow(d);
            }

            if (ImGui::Button("Update")) {
                change = true;
            }

        }

        if (ImGui::CollapsingHeader("Lights")) {

            int i;

            if (ImGui::Button("Pick Light")) {
                std::cout << "\n--- LISTA DE LUZES ---\n\n";
                for (i = 0; i < this->lights.size(); i++) {

                    if (lights[i]->lightType == LightType::POINT) {
                        Point* luz = (Point*)lights[i];
                        std::cout << i << "- Pontual na posicao: (" << luz->initial_coordinate->getCoordinate(0) << ", " << luz->initial_coordinate->getCoordinate(1) << ", " << luz->initial_coordinate->getCoordinate(2) << ")\n";
                        if (luz->getActive()) std::cout << "   Luz ativa\n\n";
                        else             std::cout << "   Luz inativa\n\n";
                    }

                    else if (lights[i]->lightType == LightType::DIRECTIONAL) {
                        Directional* luz = (Directional*)lights[i];
                        std::cout << i << "- Direcional com direcao: (" << luz->initial_direction->getCoordinate(0) << ", " << luz->initial_direction->getCoordinate(1) << ", " << luz->initial_direction->getCoordinate(2) << ")\n";
                        if (luz->getActive()) std::cout << "   Luz ativa\n\n";
                        else             std::cout << "   Luz inativa\n\n";
                    }

                    else if (lights[i]->lightType == LightType::SPOT) {
                        Spot* luz = (Spot*)lights[i];
                        std::cout << i << "- Spot na posicao: (" << luz->initial_coordinate->getCoordinate(0) << ", " << luz->initial_coordinate->getCoordinate(1) << ", " << luz->initial_coordinate->getCoordinate(2) << ")\n";
                        std::cout << "- E direcao: (" << luz->initial_direction->getCoordinate(0) << ", " << luz->initial_direction->getCoordinate(1) << ", " << luz->initial_direction->getCoordinate(2) << ")\n";
                        if (luz->getActive()) std::cout << "   Luz ativa\n\n";
                        else             std::cout << "   Luz inativa\n\n";
                    }
                }

                if (this->getEnvironmentLight() != nullptr) {
                    std::cout << i << "- Luz ambiente com intensidade: (" << this->getEnvironmentLight()->getIntensity()->getCoordinate(0) << ", " << this->getEnvironmentLight()->getIntensity()->getCoordinate(1) << ", " << this->getEnvironmentLight()->getIntensity()->getCoordinate(2) << ")\n";
                    if (this->getEnvironmentLight()->getActive()) std::cout << "   Luz ativa\n";
                    else             std::cout << "   Luz inativa\n";
                }

                std::cout << "\nDigite o numero da luz que deseja: ";
                std::cin >> num;
            }

            if (ImGui::CollapsingHeader("Point")) {
                Point* point = (Point*)this->lights[num];
                float p_coord[3] = { (float)point->initial_coordinate->getCoordinate(0),(float)point->initial_coordinate->getCoordinate(1),(float)point->initial_coordinate->getCoordinate(2) };
                ImGui::InputFloat3("Coordinates - POINT", p_coord);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    Vector* new_point = new Vector(p_coord[0], p_coord[1], p_coord[2]);
                    ((Point*)this->lights[num])->initial_coordinate = new_point;
                    change = true;
                    ((Point*)this->lights[num])->doWorldToCamera(this->cameraTo);
                }

                float intensity[3] = { (float)point->getIntensity()->getCoordinate(0), (float)point->getIntensity()->getCoordinate(1), (float)point->getIntensity()->getCoordinate(2) };
                ImGui::InputFloat3("Intensity - POINT", intensity);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    Vector* new_intensity = new Vector(intensity[0], intensity[1], intensity[2]);
                    ((Point*)this->lights[num])->setIntensity(new_intensity);
                    change = true;
                }

                if (ImGui::Button("Turn ON/OFF - POINT")) {
                    if (((Point*)this->lights[num])->getActive()) {
                        ((Point*)this->lights[num])->setActive(false);
                    }
                    else ((Point*)this->lights[num])->setActive(true);
                    change = true;
                }

            }

            if (ImGui::CollapsingHeader("Directional")) {
                Directional* direct = (Directional*)this->lights[num];
                float d_coord[3] = { (float)direct->initial_direction->getCoordinate(0), (float)direct->initial_direction->getCoordinate(1), (float)direct->initial_direction->getCoordinate(2) };
                ImGui::InputFloat3("Directions - DIRECTIONAL", d_coord);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    Vector* new_direct = new Vector(d_coord[0], d_coord[1], d_coord[2]);
                    ((Directional*)this->lights[num])->initial_direction = new_direct;
                    change = true;
                    ((Directional*)this->lights[num])->doWorldToCamera(this->cameraTo);
                }

                float intensity[3] = { (float)direct->getIntensity()->getCoordinate(0),(float)direct->getIntensity()->getCoordinate(1),(float)direct->getIntensity()->getCoordinate(2) };
                ImGui::InputFloat3("Intensity - DIRECTIONAL", intensity);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    Vector* new_intensity = new Vector(intensity[0], intensity[1], intensity[2]);
                    ((Directional*)this->lights[num])->setIntensity(new_intensity);
                    change = true;
                }

                if (ImGui::Button("Turn ON/OFF - DIRECTIONAL")) {
                    if (((Directional*)this->lights[num])->getActive()) {
                        ((Directional*)this->lights[num])->setActive(false);
                    }
                    else ((Directional*)this->lights[num])->setActive(true);
                    change = true;
                }
            }

            if (ImGui::CollapsingHeader("Spot")) {
                Spot* spot = (Spot*)this->lights[num];
                float s_coord[3] = { (float)spot->initial_coordinate->getCoordinate(0), (float)spot->initial_coordinate->getCoordinate(1), (float)spot->initial_coordinate->getCoordinate(2) };
                ImGui::InputFloat3("Coordinates - SPOT", s_coord);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    Vector* new_spot = new Vector(s_coord[0], s_coord[1], s_coord[2]);
                    ((Spot*)this->lights[num])->initial_coordinate = new_spot;
                    change = true;
                    ((Spot*)this->lights[num])->doWorldToCamera(this->cameraTo);
                }

                float sd_coord[3] = { (float)spot->initial_direction->getCoordinate(0),(float)spot->initial_direction->getCoordinate(1), (float)spot->initial_direction->getCoordinate(2) };
                ImGui::InputFloat3("Directions - SPOT", sd_coord);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    Vector* new_spotdirect = new Vector(sd_coord[0], sd_coord[1], sd_coord[2]);
                    ((Spot*)this->lights[num])->initial_direction = new_spotdirect;
                    change = true;
                    ((Spot*)this->lights[num])->doWorldToCamera(this->cameraTo);
                }

                float intensity[3] = { (float)spot->getIntensity()->getCoordinate(0), (float)spot->getIntensity()->getCoordinate(1),(float)spot->getIntensity()->getCoordinate(2) };
                ImGui::InputFloat3("Intensity - SPOT", intensity);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    Vector* new_intensity = new Vector(intensity[0], intensity[1], intensity[2]);
                    ((Spot*)this->lights[num])->setIntensity(new_intensity);
                    change = true;
                }

                double angle = spot->getAngle();
                ImGui::InputDouble("Angle", &angle);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    ((Spot*)this->lights[num])->setAngle(angle);
                    change = true;
                }

                if (ImGui::Button("Turn ON/OFF - SPOT")) {
                    if (((Spot*)this->lights[num])->getActive()) {
                        ((Spot*)this->lights[num])->setActive(false);
                    }
                    else ((Spot*)this->lights[num])->setActive(true);
                    change = true;
                }
            }

            if (ImGui::CollapsingHeader("Environment")) {

                Light* environment = this->environmentLight;

                float intensity[3] = { (float)environment->getIntensity()->getCoordinate(0), (float)environment->getIntensity()->getCoordinate(1),(float)environment->getIntensity()->getCoordinate(2) };
                ImGui::InputFloat3("Intensity - ENVIRONMNENT", intensity);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    Vector* new_intensity = new Vector(intensity[0], intensity[1], intensity[2]);
                    environment->setIntensity(new_intensity);
                    change = true;
                }

                if (ImGui::Button("Turn ON/OFF - ENVIRONMNENT")) {
                    if (environment->getActive()) {
                        environment->setActive(false);
                    }
                    else environment->setActive(true);
                    change = true;
                }

            }
        }


        if (ImGui::CollapsingHeader("Picking")) {

            if (ImGui::Button("Click")) {
                Object* object = this->interaction->picking();


                if (object->getObjectType() == ObjectType::SPHERE) {

                    std::cout << "\n--- SPHERE ---\n";
                    std::cout << "1- kd\n";
                    std::cout << "2- ke\n";
                    std::cout << "3- ka\n";
                    std::cout << "4- shininess\n";
                    std::cout << "5- translation\n";
                    std::cout << "6- rotate x\n";
                    std::cout << "7- rotate y\n";
                    std::cout << "8- rotate z\n";
                    std::cout << "9- reflect XY\n";
                    std::cout << "10- reflect XZ\n";
                    std::cout << "11- reflect YZ\n";
                    std::cout << "Digite uma opcao: ";

                    std::string opc;
                    std::cin >> opc;

                    Sphere* objectSphere;
                    objectSphere = (Sphere*)object;

                    if (opc == "1") {

                        double kd1, kd2, kd3;

                        std::cout << "Digite o primeiro valor de kd (de 0 a 1): ";
                        std::cin >> kd1;
                        std::cout << "Digite o segundo valor de kd(de 0 a 1): ";
                        std::cin >> kd2;
                        std::cout << "Digite o terceiro valor de kd(de 0 a 1): ";
                        std::cin >> kd3;

                        Vector* newKD = new Vector(kd1, kd2, kd3);
                        objectSphere->setKD(newKD);
                        change = true;
                    }

                    if (opc == "2") {
                        double ke1, ke2, ke3;

                        std::cout << "Digite o primeiro valor de ke(de 0 a 1): ";
                        std::cin >> ke1;
                        std::cout << "Digite o segundo valor de ke(de 0 a 1): ";
                        std::cin >> ke2;
                        std::cout << "Digite o terceiro valor de ke(de 0 a 1): ";
                        std::cin >> ke3;

                        Vector* newKE = new Vector(ke1, ke2, ke3);
                        objectSphere->setKE(newKE);
                        change = true;
                    }

                    if (opc == "3") {
                        double ka1, ka2, ka3;

                        std::cout << "Digite o primeiro valor de ka(de 0 a 1): ";
                        std::cin >> ka1;
                        std::cout << "Digite o segundo valor de ka(de 0 a 1): ";
                        std::cin >> ka2;
                        std::cout << "Digite o terceiro valor de ka(de 0 a 1): ";
                        std::cin >> ka3;

                        Vector* newKA = new Vector(ka1, ka2, ka3);
                        objectSphere->setKA(newKA);
                        change = true;
                    }

                    if (opc == "4") {

                        double shininess;

                        std::cout << "Digite o valor de shininess: ";
                        std::cin >> shininess;

                        objectSphere->setShininess(shininess);

                    }

                    if (opc == "4") {

                        double shininess;

                        std::cout << "Digite o valor de shininess: ";
                        std::cin >> shininess;

                        objectSphere->setShininess(shininess);

                    }

                    if (opc == "5") {

                        double tx, ty, tz;

                        std::cout << "Digite o x da translacao: ";
                        std::cin >> tx;
                        std::cout << "Digite o y da translacao: ";
                        std::cin >> ty;
                        std::cout << "Digite o z da translacao: ";
                        std::cin >> tz;

                        objectSphere->translation(tx, ty, tz);
                        change = true;
                    }

                    else if (opc == "6") {

                        double ax;

                        std::cout << "Digite o angulo da rotacao no eixo X: ";
                        std::cin >> ax;

                        objectSphere->rotX(ax);
                        change = true;
                    }

                    else if (opc == "7") {

                        double ay;

                        std::cout << "Digite o angulo da rotacao no eixo Y: ";
                        std::cin >> ay;

                        objectSphere->rotY(ay);
                        change = true;
                    }

                    else if (opc == "8") {

                        double az;

                        std::cout << "Digite o angulo da rotacao no eixo Z: ";
                        std::cin >> az;

                        objectSphere->rotZ(az);
                        change = true;
                    }

                    else if (opc == "9") {

                        objectSphere->reflectionXY();
                        change = true;
                    }

                    else if (opc == "10") {

                        objectSphere->reflectionXZ();
                        change = true;
                    }

                    else if (opc == "11") {

                        objectSphere->reflectionYZ();
                        change = true;
                    }

                    objectSphere->doWorldToCamera(this->cameraTo);
                }

                else if (object->getObjectType() == ObjectType::PLAN)
                {
                    Plan* objectPlan;
                    objectPlan = (Plan*)object;

                    std::cout << "\n--- PLAN ---\n";

                    std::cout << "1- kd\n";
                    std::cout << "2- ke\n";
                    std::cout << "3- ka\n";
                    std::cout << "4- shininess\n";
                    std::cout << "5- translation\n";
                    std::cout << "6- rotate X\n";
                    std::cout << "7- rotate Y\n";
                    std::cout << "8- rotate Z\n";
                    std::cout << "9- reflect XY\n";
                    std::cout << "10- reflect XZ\n";
                    std::cout << "11- reflect YZ\n\n";

                    std::cout << "Digite a opcao escolhida: ";
                    std::string opc;
                    std::cin >> opc;


                    if (opc == "1") {

                        double kd1, kd2, kd3;

                        std::cout << "Digite o primeiro valor de kd (de 0 a 1): ";
                        std::cin >> kd1;
                        std::cout << "Digite o segundo valor de kd (de 0 a 1): ";
                        std::cin >> kd2;
                        std::cout << "Digite o terceiro valor de kd (de 0 a 1): ";
                        std::cin >> kd3;

                        Vector* newKD = new Vector(kd1, kd2, kd3);
                        objectPlan->setKD(newKD);
                        change = true;
                    }

                    else if (opc == "2") {

                        double ke1, ke2, ke3;

                        std::cout << "Digite o primeiro valor de ke (de 0 a 1): ";
                        std::cin >> ke1;
                        std::cout << "Digite o segundo valor de ke (de 0 a 1): ";
                        std::cin >> ke2;
                        std::cout << "Digite o terceiro valor de ke (de 0 a 1): ";
                        std::cin >> ke3;

                        Vector* newKE = new Vector(ke1, ke2, ke3);
                        objectPlan->setKE(newKE);
                        change = true;
                    }

                    else if (opc == "3") {

                        double ka1, ka2, ka3;

                        std::cout << "Digite o primeiro valor de ka (de 0 a 1): ";
                        std::cin >> ka1;
                        std::cout << "Digite o segundo valor de ka (de 0 a 1): ";
                        std::cin >> ka2;
                        std::cout << "Digite o terceiro valor de ka (de 0 a 1): ";
                        std::cin >> ka3;

                        Vector* newKA = new Vector(ka1, ka2, ka3);
                        objectPlan->setKA(newKA);
                        change = true;
                    }

                    else if (opc == "4") {

                        double shininess;

                        std::cout << "Digite o valor de shininess: ";
                        std::cin >> shininess;

                        objectPlan->setShininess(shininess);
                        change = true;
                    }

                    else if (opc == "5") {

                        double tx, ty, tz;

                        std::cout << "Digite o x da translacao: ";
                        std::cin >> tx;
                        std::cout << "Digite o y da translacao: ";
                        std::cin >> ty;
                        std::cout << "Digite o z da translacao: ";
                        std::cin >> tz;

                        objectPlan->translation(tx, ty, tz);
                        change = true;
                    }

                    else if (opc == "6") {

                        double ax;

                        std::cout << "Digite o angulo da rotacao no eixo X: ";
                        std::cin >> ax;

                        objectPlan->rotX(ax);
                        change = true;
                    }

                    else if (opc == "7") {

                        double ay;

                        std::cout << "Digite o angulo da rotacao no eixo Y: ";
                        std::cin >> ay;

                        objectPlan->rotY(ay);
                        change = true;
                    }

                    else if (opc == "8") {

                        double az;

                        std::cout << "Digite o angulo da rotacao no eixo Z: ";
                        std::cin >> az;

                        objectPlan->rotZ(az);
                        change = true;
                    }

                    else if (opc == "9") {

                        objectPlan->reflectionXY();
                        change = true;
                    }

                    else if (opc == "10") {

                        objectPlan->reflectionXZ();
                        change = true;
                    }

                    else if (opc == "11") {

                        objectPlan->reflectionYZ();
                        change = true;
                    }

                    objectPlan->doWorldToCamera(this->cameraTo);

                }

                else if (object->getObjectType() == ObjectType::TEXTURE)
                {
                    Texture* objectTexture;
                    objectTexture = (Texture*)object;

                    std::cout << "\n--- TEXTURE ---\n";

                    std::cout << "1- kd\n";
                    std::cout << "2- ke\n";
                    std::cout << "3- ka\n";
                    std::cout << "4- shininess\n";
                    std::cout << "5- translation\n";
                    std::cout << "6- rotate X\n";
                    std::cout << "7- rotate Y\n";
                    std::cout << "8- rotate Z\n";
                    std::cout << "9- reflect XY\n";
                    std::cout << "10- reflect XZ\n";
                    std::cout << "11- reflect YZ\n\n";

                    std::cout << "Digite a opcao escolhida: ";
                    std::string opc;
                    std::cin >> opc;


                    if (opc == "1") {

                        double kd1, kd2, kd3;

                        std::cout << "Digite o primeiro valor de kd (de 0 a 1): ";
                        std::cin >> kd1;
                        std::cout << "Digite o segundo valor de kd (de 0 a 1): ";
                        std::cin >> kd2;
                        std::cout << "Digite o terceiro valor de kd (de 0 a 1): ";
                        std::cin >> kd3;

                        Vector* newKD = new Vector(kd1, kd2, kd3);
                        objectTexture->setKD(newKD);
                        change = true;
                    }

                    else if (opc == "2") {

                        double ke1, ke2, ke3;

                        std::cout << "Digite o primeiro valor de ke (de 0 a 1): ";
                        std::cin >> ke1;
                        std::cout << "Digite o segundo valor de ke (de 0 a 1): ";
                        std::cin >> ke2;
                        std::cout << "Digite o terceiro valor de ke (de 0 a 1): ";
                        std::cin >> ke3;

                        Vector* newKE = new Vector(ke1, ke2, ke3);
                        objectTexture->setKE(newKE);
                        change = true;
                    }

                    else if (opc == "3") {

                        double ka1, ka2, ka3;

                        std::cout << "Digite o primeiro valor de ka (de 0 a 1): ";
                        std::cin >> ka1;
                        std::cout << "Digite o segundo valor de ka (de 0 a 1): ";
                        std::cin >> ka2;
                        std::cout << "Digite o terceiro valor de ka (de 0 a 1): ";
                        std::cin >> ka3;

                        Vector* newKA = new Vector(ka1, ka2, ka3);
                        objectTexture->setKA(newKA);
                        change = true;
                    }

                    else if (opc == "4") {

                        double shininess;

                        std::cout << "Digite o valor de shininess: ";
                        std::cin >> shininess;

                        objectTexture->setShininess(shininess);
                        change = true;
                    }

                    else if (opc == "5") {

                        double tx, ty, tz;

                        std::cout << "Digite o x da translacao: ";
                        std::cin >> tx;
                        std::cout << "Digite o y da translacao: ";
                        std::cin >> ty;
                        std::cout << "Digite o z da translacao: ";
                        std::cin >> tz;

                        objectTexture->translation(tx, ty, tz);
                        change = true;
                    }

                    else if (opc == "6") {

                        double ax;

                        std::cout << "Digite o angulo da rotacao no eixo X: ";
                        std::cin >> ax;

                        objectTexture->rotX(ax);
                        change = true;
                    }

                    else if (opc == "7") {

                        double ay;

                        std::cout << "Digite o angulo da rotacao no eixo Y: ";
                        std::cin >> ay;

                        objectTexture->rotY(ay);
                        change = true;
                    }

                    else if (opc == "8") {

                        double az;

                        std::cout << "Digite o angulo da rotacao no eixo Z: ";
                        std::cin >> az;

                        objectTexture->rotZ(az);
                        change = true;
                    }

                    else if (opc == "9") {

                        objectTexture->reflectionXY();
                        change = true;
                    }

                    else if (opc == "10") {

                        objectTexture->reflectionXZ();
                        change = true;
                    }

                    else if (opc == "11") {

                        objectTexture->reflectionYZ();
                        change = true;
                    }

                    objectTexture->doWorldToCamera(this->cameraTo);


                }

                else if (object->getObjectType() == ObjectType::CYLINDER)
                {
                    Cylinder* objectCylinder;
                    objectCylinder = (Cylinder*)object;

                    std::cout << "\n--- CYLINDER ---\n";

                    std::cout << "1- kd\n";
                    std::cout << "2- ke\n";
                    std::cout << "3- ka\n";
                    std::cout << "4- shininess\n";
                    std::cout << "5- translation\n";
                    std::cout << "6- rotate X\n";
                    std::cout << "7- rotate Y\n";
                    std::cout << "8- rotate Z\n";
                    std::cout << "9- reflect XY\n";
                    std::cout << "10- reflect XZ\n";
                    std::cout << "11- reflect YZ\n\n";

                    std::cout << "Digite a opcao escolhida: ";
                    std::string opc;
                    std::cin >> opc;


                    if (opc == "1") {

                        double kd1, kd2, kd3;

                        std::cout << "Digite o primeiro valor de kd (de 0 a 1): ";
                        std::cin >> kd1;
                        std::cout << "Digite o segundo valor de kd (de 0 a 1): ";
                        std::cin >> kd2;
                        std::cout << "Digite o terceiro valor de kd (de 0 a 1): ";
                        std::cin >> kd3;

                        Vector* newKD = new Vector(kd1, kd2, kd3);
                        objectCylinder->setKD(newKD);
                        change = true;
                    }

                    else if (opc == "2") {

                        double ke1, ke2, ke3;

                        std::cout << "Digite o primeiro valor de ke (de 0 a 1): ";
                        std::cin >> ke1;
                        std::cout << "Digite o segundo valor de ke (de 0 a 1): ";
                        std::cin >> ke2;
                        std::cout << "Digite o terceiro valor de ke (de 0 a 1): ";
                        std::cin >> ke3;

                        Vector* newKE = new Vector(ke1, ke2, ke3);
                        objectCylinder->setKE(newKE);
                        change = true;
                    }

                    else if (opc == "3") {

                        double ka1, ka2, ka3;

                        std::cout << "Digite o primeiro valor de ka (de 0 a 1): ";
                        std::cin >> ka1;
                        std::cout << "Digite o segundo valor de ka (de 0 a 1): ";
                        std::cin >> ka2;
                        std::cout << "Digite o terceiro valor de ka (de 0 a 1): ";
                        std::cin >> ka3;

                        Vector* newKA = new Vector(ka1, ka2, ka3);
                        objectCylinder->setKA(newKA);
                        change = true;
                    }

                    else if (opc == "4") {

                        double shininess;

                        std::cout << "Digite o valor de shininess: ";
                        std::cin >> shininess;

                        objectCylinder->setShininess(shininess);
                        change = true;
                    }

                    else if (opc == "5") {

                        double tx, ty, tz;

                        std::cout << "Digite o x da translacao: ";
                        std::cin >> tx;
                        std::cout << "Digite o y da translacao: ";
                        std::cin >> ty;
                        std::cout << "Digite o z da translacao: ";
                        std::cin >> tz;

                        objectCylinder->translation(tx, ty, tz);
                        change = true;
                    }

                    else if (opc == "6") {

                        double ax;

                        std::cout << "Digite o angulo da rotacao no eixo X: ";
                        std::cin >> ax;

                        objectCylinder->rotX(ax);
                        change = true;
                    }

                    else if (opc == "7") {

                        double ay;

                        std::cout << "Digite o angulo da rotacao no eixo Y: ";
                        std::cin >> ay;

                        objectCylinder->rotY(ay);
                        change = true;
                    }

                    else if (opc == "8") {

                        double az;

                        std::cout << "Digite o angulo da rotacao no eixo Z: ";
                        std::cin >> az;

                        objectCylinder->rotZ(az);
                        change = true;
                    }

                    else if (opc == "9") {

                        objectCylinder->reflectionXY();
                        change = true;
                    }

                    else if (opc == "10") {

                        objectCylinder->reflectionXZ();
                        change = true;
                    }

                    else if (opc == "11") {

                        objectCylinder->reflectionYZ();
                        change = true;
                    }

                    objectCylinder->doWorldToCamera(this->cameraTo);

                }

                else if (object->getObjectType() == ObjectType::CONE)
                {
                    Cone* objectCone;
                    objectCone = (Cone*)object;

                    std::cout << "\n--- CONE ---\n";

                    std::cout << "1- kd\n";
                    std::cout << "2- ke\n";
                    std::cout << "3- ka\n";
                    std::cout << "4- shininess\n";
                    std::cout << "5- translation\n";
                    std::cout << "6- rotate X\n";
                    std::cout << "7- rotate Y\n";
                    std::cout << "8- rotate Z\n";
                    std::cout << "9- reflect XY\n";
                    std::cout << "10- reflect XZ\n";
                    std::cout << "11- reflect YZ\n\n";

                    std::cout << "Digite a opcao escolhida: ";
                    std::string opc;
                    std::cin >> opc;


                    if (opc == "1") {

                        double kd1, kd2, kd3;

                        std::cout << "Digite o primeiro valor de kd (de 0 a 1): ";
                        std::cin >> kd1;
                        std::cout << "Digite o segundo valor de kd (de 0 a 1): ";
                        std::cin >> kd2;
                        std::cout << "Digite o terceiro valor de kd (de 0 a 1): ";
                        std::cin >> kd3;

                        Vector* newKD = new Vector(kd1, kd2, kd3);
                        objectCone->setKD(newKD);
                        change = true;
                    }

                    else if (opc == "2") {

                        double ke1, ke2, ke3;

                        std::cout << "Digite o primeiro valor de ke (de 0 a 1): ";
                        std::cin >> ke1;
                        std::cout << "Digite o segundo valor de ke (de 0 a 1): ";
                        std::cin >> ke2;
                        std::cout << "Digite o terceiro valor de ke (de 0 a 1): ";
                        std::cin >> ke3;

                        Vector* newKE = new Vector(ke1, ke2, ke3);
                        objectCone->setKE(newKE);
                        change = true;
                    }

                    else if (opc == "3") {

                        double ka1, ka2, ka3;

                        std::cout << "Digite o primeiro valor de ka (de 0 a 1): ";
                        std::cin >> ka1;
                        std::cout << "Digite o segundo valor de ka (de 0 a 1): ";
                        std::cin >> ka2;
                        std::cout << "Digite o terceiro valor de ka (de 0 a 1): ";
                        std::cin >> ka3;

                        Vector* newKA = new Vector(ka1, ka2, ka3);
                        objectCone->setKA(newKA);
                        change = true;
                    }

                    else if (opc == "4") {

                        double shininess;

                        std::cout << "Digite o valor de shininess: ";
                        std::cin >> shininess;

                        objectCone->setShininess(shininess);
                        change = true;
                    }

                    else if (opc == "5") {

                        double tx, ty, tz;

                        std::cout << "Digite o x da translacao: ";
                        std::cin >> tx;
                        std::cout << "Digite o y da translacao: ";
                        std::cin >> ty;
                        std::cout << "Digite o z da translacao: ";
                        std::cin >> tz;

                        objectCone->translation(tx, ty, tz);
                        change = true;
                    }

                    else if (opc == "6") {

                        double ax;

                        std::cout << "Digite o angulo da rotacao no eixo X: ";
                        std::cin >> ax;

                        objectCone->rotX(ax);
                        change = true;
                    }

                    else if (opc == "7") {

                        double ay;

                        std::cout << "Digite o angulo da rotacao no eixo Y: ";
                        std::cin >> ay;

                        objectCone->rotY(ay);
                        change = true;
                    }

                    else if (opc == "8") {

                        double az;

                        std::cout << "Digite o angulo da rotacao no eixo Z: ";
                        std::cin >> az;

                        objectCone->rotZ(az);
                        change = true;
                    }

                    else if (opc == "9") {

                        objectCone->reflectionXY();
                        change = true;
                    }

                    else if (opc == "10") {

                        objectCone->reflectionXZ();
                        change = true;
                    }

                    else if (opc == "11") {

                        objectCone->reflectionYZ();
                        change = true;
                    }

                    objectCone->doWorldToCamera(this->cameraTo);

                }

                else if (object->getObjectType() == ObjectType::MESH)
                {
                    Mesh* objectMesh;
                    objectMesh = (Mesh*)object;

                    std::cout << "\n--- MESH ---\n";

                    std::cout << "1- kd\n";
                    std::cout << "2- ke\n";
                    std::cout << "3- ka\n";
                    std::cout << "4- shininess\n";
                    std::cout << "5- translation\n";
                    std::cout << "6- rotate X\n";
                    std::cout << "7- rotate Y\n";
                    std::cout << "8- rotate Z\n";
                    std::cout << "9- reflect XY\n";
                    std::cout << "10- reflect XZ\n";
                    std::cout << "11- reflect YZ\n\n";

                    std::cout << "Digite a opcao escolhida: ";
                    std::string opc;
                    std::cin >> opc;


                    if (opc == "1") {

                        double kd1, kd2, kd3;

                        std::cout << "Digite o primeiro valor de kd (de 0 a 1): ";
                        std::cin >> kd1;
                        std::cout << "Digite o segundo valor de kd (de 0 a 1): ";
                        std::cin >> kd2;
                        std::cout << "Digite o terceiro valor de kd (de 0 a 1): ";
                        std::cin >> kd3;

                        Vector* newKD = new Vector(kd1, kd2, kd3);
                        objectMesh->setKD(newKD);
                        change = true;
                    }

                    else if (opc == "2") {

                        double ke1, ke2, ke3;

                        std::cout << "Digite o primeiro valor de ke (de 0 a 1): ";
                        std::cin >> ke1;
                        std::cout << "Digite o segundo valor de ke (de 0 a 1): ";
                        std::cin >> ke2;
                        std::cout << "Digite o terceiro valor de ke (de 0 a 1): ";
                        std::cin >> ke3;

                        Vector* newKE = new Vector(ke1, ke2, ke3);
                        objectMesh->setKE(newKE);
                        change = true;
                    }

                    else if (opc == "3") {

                        double ka1, ka2, ka3;

                        std::cout << "Digite o primeiro valor de ka (de 0 a 1): ";
                        std::cin >> ka1;
                        std::cout << "Digite o segundo valor de ka (de 0 a 1): ";
                        std::cin >> ka2;
                        std::cout << "Digite o terceiro valor de ka (de 0 a 1): ";
                        std::cin >> ka3;

                        Vector* newKA = new Vector(ka1, ka2, ka3);
                        objectMesh->setKA(newKA);
                        change = true;
                    }

                    else if (opc == "4") {

                        double shininess;

                        std::cout << "Digite o valor de shininess: ";
                        std::cin >> shininess;

                        objectMesh->setShininess(shininess);
                        change = true;
                    }

                    else if (opc == "5") {

                        double tx, ty, tz;

                        std::cout << "Digite o x da translacao: ";
                        std::cin >> tx;
                        std::cout << "Digite o y da translacao: ";
                        std::cin >> ty;
                        std::cout << "Digite o z da translacao: ";
                        std::cin >> tz;

                        objectMesh->translation(tx, ty, tz);
                        change = true;
                    }

                    else if (opc == "6") {

                        double ax;

                        std::cout << "Digite o angulo da rotacao no eixo X: ";
                        std::cin >> ax;

                        objectMesh->rotX(ax);
                        change = true;
                    }

                    else if (opc == "7") {

                        double ay;

                        std::cout << "Digite o angulo da rotacao no eixo Y: ";
                        std::cin >> ay;

                        objectMesh->rotY(ay);
                        change = true;
                    }

                    else if (opc == "8") {

                        double az;

                        std::cout << "Digite o angulo da rotacao no eixo Z: ";
                        std::cin >> az;

                        objectMesh->rotZ(az);
                        change = true;
                    }

                    else if (opc == "9") {

                        objectMesh->reflectionXY();
                        change = true;
                    }

                    else if (opc == "10") {

                        objectMesh->reflectionXZ();
                        change = true;
                    }

                    else if (opc == "11") {

                        objectMesh->reflectionYZ();
                        change = true;
                    }

                    objectMesh->doWorldToCamera(this->cameraTo);

                }

                else if (object->getObjectType() == ObjectType::MESH_TEXTURIZED)
                {
                    MeshTexturized* objectMeshTexturized;
                    objectMeshTexturized = (MeshTexturized*)object;

                    std::cout << "\n--- MESH_TEXTURE ---\n";

                    std::cout << "1- kd\n";
                    std::cout << "2- ke\n";
                    std::cout << "3- ka\n";
                    std::cout << "4- shininess\n";
                    std::cout << "5- translation\n";
                    std::cout << "6- rotate X\n";
                    std::cout << "7- rotate Y\n";
                    std::cout << "8- rotate Z\n";
                    std::cout << "9- reflect XY\n";
                    std::cout << "10- reflect XZ\n";
                    std::cout << "11- reflect YZ\n\n";

                    std::cout << "Digite a opcao escolhida: ";
                    std::string opc;
                    std::cin >> opc;


                    if (opc == "1") {

                        double kd1, kd2, kd3;

                        std::cout << "Digite o primeiro valor de kd (de 0 a 1): ";
                        std::cin >> kd1;
                        std::cout << "Digite o segundo valor de kd (de 0 a 1): ";
                        std::cin >> kd2;
                        std::cout << "Digite o terceiro valor de kd (de 0 a 1): ";
                        std::cin >> kd3;

                        Vector* newKD = new Vector(kd1, kd2, kd3);
                        objectMeshTexturized->setKD(newKD);
                        change = true;
                    }

                    else if (opc == "2") {

                        double ke1, ke2, ke3;

                        std::cout << "Digite o primeiro valor de ke (de 0 a 1): ";
                        std::cin >> ke1;
                        std::cout << "Digite o segundo valor de ke (de 0 a 1): ";
                        std::cin >> ke2;
                        std::cout << "Digite o terceiro valor de ke (de 0 a 1): ";
                        std::cin >> ke3;

                        Vector* newKE = new Vector(ke1, ke2, ke3);
                        objectMeshTexturized->setKE(newKE);
                        change = true;
                    }

                    else if (opc == "3") {

                        double ka1, ka2, ka3;

                        std::cout << "Digite o primeiro valor de ka (de 0 a 1): ";
                        std::cin >> ka1;
                        std::cout << "Digite o segundo valor de ka (de 0 a 1): ";
                        std::cin >> ka2;
                        std::cout << "Digite o terceiro valor de ka (de 0 a 1): ";
                        std::cin >> ka3;

                        Vector* newKA = new Vector(ka1, ka2, ka3);
                        objectMeshTexturized->setKA(newKA);
                        change = true;
                    }

                    else if (opc == "4") {

                        double shininess;

                        std::cout << "Digite o valor de shininess: ";
                        std::cin >> shininess;

                        objectMeshTexturized->setShininess(shininess);
                        change = true;
                    }

                    else if (opc == "5") {

                        double tx, ty, tz;

                        std::cout << "Digite o x da translacao: ";
                        std::cin >> tx;
                        std::cout << "Digite o y da translacao: ";
                        std::cin >> ty;
                        std::cout << "Digite o z da translacao: ";
                        std::cin >> tz;

                        objectMeshTexturized->translation(tx, ty, tz);
                        change = true;
                    }

                    else if (opc == "6") {

                        double ax;

                        std::cout << "Digite o angulo da rotacao no eixo X: ";
                        std::cin >> ax;

                        objectMeshTexturized->rotX(ax);
                        change = true;
                    }

                    else if (opc == "7") {

                        double ay;

                        std::cout << "Digite o angulo da rotacao no eixo Y: ";
                        std::cin >> ay;

                        objectMeshTexturized->rotY(ay);
                        change = true;
                    }

                    else if (opc == "8") {

                        double az;

                        std::cout << "Digite o angulo da rotacao no eixo Z: ";
                        std::cin >> az;

                        objectMeshTexturized->rotZ(az);
                        change = true;
                    }

                    else if (opc == "9") {

                        objectMeshTexturized->reflectionXY();
                        change = true;
                    }

                    else if (opc == "10") {

                        objectMeshTexturized->reflectionXZ();
                        change = true;
                    }

                    else if (opc == "11") {

                        objectMeshTexturized->reflectionYZ();
                        change = true;
                    }

                    objectMeshTexturized->doWorldToCamera(this->cameraTo);

                }

                else if (object->getObjectType() == ObjectType::MESH2)
                {
                    Mesh2* objectMesh;
                    objectMesh = (Mesh2*)object;

                    std::cout << "\n--- MESH2 ---\n";

                    std::cout << "1- kd\n";
                    std::cout << "2- ke\n";
                    std::cout << "3- ka\n";
                    std::cout << "4- shininess\n";
                    std::cout << "5- translation\n";
                    std::cout << "6- rotate X\n";
                    std::cout << "7- rotate Y\n";
                    std::cout << "8- rotate Z\n";
                    std::cout << "9- reflect XY\n";
                    std::cout << "10- reflect XZ\n";
                    std::cout << "11- reflect YZ\n\n";

                    std::cout << "Digite a opcao escolhida: ";
                    std::string opc;
                    std::cin >> opc;


                    if (opc == "1") {

                        double kd1, kd2, kd3;

                        std::cout << "Digite o primeiro valor de kd (de 0 a 1): ";
                        std::cin >> kd1;
                        std::cout << "Digite o segundo valor de kd (de 0 a 1): ";
                        std::cin >> kd2;
                        std::cout << "Digite o terceiro valor de kd (de 0 a 1): ";
                        std::cin >> kd3;

                        Vector* newKD = new Vector(kd1, kd2, kd3);
                        objectMesh->setKD(newKD);
                        change = true;
                    }

                    else if (opc == "2") {

                        double ke1, ke2, ke3;

                        std::cout << "Digite o primeiro valor de ke (de 0 a 1): ";
                        std::cin >> ke1;
                        std::cout << "Digite o segundo valor de ke (de 0 a 1): ";
                        std::cin >> ke2;
                        std::cout << "Digite o terceiro valor de ke (de 0 a 1): ";
                        std::cin >> ke3;

                        Vector* newKE = new Vector(ke1, ke2, ke3);
                        objectMesh->setKE(newKE);
                        change = true;
                    }

                    else if (opc == "3") {

                        double ka1, ka2, ka3;

                        std::cout << "Digite o primeiro valor de ka (de 0 a 1): ";
                        std::cin >> ka1;
                        std::cout << "Digite o segundo valor de ka (de 0 a 1): ";
                        std::cin >> ka2;
                        std::cout << "Digite o terceiro valor de ka (de 0 a 1): ";
                        std::cin >> ka3;

                        Vector* newKA = new Vector(ka1, ka2, ka3);
                        objectMesh->setKA(newKA);
                        change = true;
                    }

                    else if (opc == "4") {

                        double shininess;

                        std::cout << "Digite o valor de shininess: ";
                        std::cin >> shininess;

                        objectMesh->setShininess(shininess);
                        change = true;
                    }

                    else if (opc == "5") {

                        double tx, ty, tz;

                        std::cout << "Digite o x da translacao: ";
                        std::cin >> tx;
                        std::cout << "Digite o y da translacao: ";
                        std::cin >> ty;
                        std::cout << "Digite o z da translacao: ";
                        std::cin >> tz;

                        objectMesh->translation(tx, ty, tz);
                        change = true;
                    }

                    else if (opc == "6") {

                        double ax;

                        std::cout << "Digite o angulo da rotacao no eixo X: ";
                        std::cin >> ax;

                        objectMesh->rotX(ax);
                        change = true;
                    }

                    else if (opc == "7") {

                        double ay;

                        std::cout << "Digite o angulo da rotacao no eixo Y: ";
                        std::cin >> ay;

                        objectMesh->rotY(ay);
                        change = true;
                    }

                    else if (opc == "8") {

                        double az;

                        std::cout << "Digite o angulo da rotacao no eixo Z: ";
                        std::cin >> az;

                        objectMesh->rotZ(az);
                        change = true;
                    }

                    else if (opc == "9") {

                        objectMesh->reflectionXY();
                        change = true;
                    }

                    else if (opc == "10") {

                        objectMesh->reflectionXZ();
                        change = true;
                    }

                    else if (opc == "11") {

                        objectMesh->reflectionYZ();
                        change = true;
                    }

                    objectMesh->doWorldToCamera(this->cameraTo);

                }
            }
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

    this->cameraTo = new Camera(new Vector(0., 0., 0.), new Vector(0., 0., -1.), new Vector(0., 1., 0.));
}


Scene::~Scene() {
    delete this->getEnvironmentLight();
    delete this->getBGColor();
    delete this->getBGImage();
    delete this->cameraTo;

    for (auto o = this->objects.begin(); o != this->objects.end(); o++) { delete (*o); }

    for (auto l = this->lights.begin(); l != this->lights.end(); l++) { delete (*l); }
}
