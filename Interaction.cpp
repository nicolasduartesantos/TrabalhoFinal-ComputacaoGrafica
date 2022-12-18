#include "Interaction.h"
#include "Scene.h"
#include "Object.h"
#include "Light.h"
#include "Vector.h"
#include "libSDL.h"
#include "Image.h"
#include "Sphere.h"
#include "Plan.h"
#include "Texture.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Mesh.h"
#include "Scene.h"
#include <vector>
#include <SDL.h>
#include <iostream>

Object* Interaction::picking() {

    SDL_Event event;
    bool exit = false;

    while (exit == false) {

        while (SDL_PollEvent(&event) != 0) {

            if (event.type == SDL_MOUSEBUTTONDOWN) {

                int l, c;

                SDL_GetMouseState(&c, &l);

                double nLin = this->scene->getNLin();
                double nCol = this->scene->getNCol();

                double hWindow = this->scene->getHWindow();
                double wWindow = this->scene->getWWindow();
                double dWindow = this->scene->getDWindow();

                double dx = wWindow / nCol;
                double dy = hWindow / nLin;

                double y = (hWindow / 2.) - (dy / 2.) - (l * dy);
                double x = (-wWindow / 2.) + (dx / 2.) + (c * dx);

                Vector* p0 = new Vector();
                Vector* p = new Vector();

                bool perspectiveProjection = this->scene->getProjection() == ProjectionType::PERSPECTIVE;
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
                Object* closest = this->scene->getObjects()[0];
                closest->setHasIntersection(false);

                for (int i = 0; i < this->scene->getObjects().size(); i++) {

                    (this->scene->getObjects()[i])->intersect(p0, dir);

                    if ((this->scene->getObjects()[i])->getHasIntersection() &&
                        (!closest->getHasIntersection() || ((this->scene->getObjects()[i])->getP0distance() < closest->getP0distance()))) {

                        closest = this->scene->getObjects()[i];

                        iClosest = i;
                    }
                }
                //Object* closestObject = closest;
                exit = true;
                return closest;

            }
        }
    }
}
