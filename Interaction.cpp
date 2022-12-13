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
#include <vector>
#include <SDL.h>
#include <iostream>





/*
void Interaction::picking() {

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
                    p = new Vector(0, 0, -1);
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

                Object* closestObject = closest;
                ObjectType closestObjectType = closest->getObjectType();
                
                switch (closestObjectType) {
                    
                    case ObjectType::SPHERE:

                        Sphere* objectSphere;
                        objectSphere = (Sphere*) closest;

                        objectSphere->setKD();
                        objectSphere->setKE();
                        objectSphere->setKA();
                        objectSphere->setShininess();
                        objectSphere->translation();
                        objectSphere->rotX();
                        objectSphere->rotY();
                        objectSphere->rotZ();
                        objectSphere->reflectionXY();
                        objectSphere->reflectionXZ();
                        objectSphere->reflectionYZ();
                        objectSphere->doWorldToCamera(this->scene->cameraTo);


                    case ObjectType::PLAN:

                        Plan* objectPlan;
                        objectPlan = (Plan*)closest;

                        objectPlan->setKD();
                        objectPlan->setKE();
                        objectPlan->setKA();
                        objectPlan->setShininess();
                        objectPlan->translation();
                        objectPlan->rotX();
                        objectPlan->rotY();
                        objectPlan->rotZ();
                        objectPlan->reflectionXY();
                        objectPlan->reflectionXZ();
                        objectPlan->reflectionYZ();
                        objectPlan->doWorldToCamera(this->scene->cameraTo);
                    

                    case ObjectType::TEXTURE: // ?

                        Texture* objectTexture;
                        objectTexture = (Texture*)closest;

                        objectTexture->setKD();
                        objectTexture->setKE();
                        objectTexture->setKA();
                        objectTexture->setShininess();
                        objectTexture->translation();
                        objectTexture->rotX();
                        objectTexture->rotY();
                        objectTexture->rotZ();
                        objectTexture->reflectionXY();
                        objectTexture->reflectionXZ();
                        objectTexture->reflectionYZ();
                        objectTexture->doWorldToCamera(this->scene->cameraTo);

                        // ativar ou desativar textura ?


                    case ObjectType::CYLINDER:

                        Cylinder* objectCylinder;
                        objectCylinder = (Cylinder*)closest;

                        objectCylinder->setKD();
                        objectCylinder->setKE();
                        objectCylinder->setKA();
                        objectCylinder->setShininess();
                        objectCylinder->translation();
                        objectCylinder->rotX();
                        objectCylinder->rotY();
                        objectCylinder->rotZ();
                        objectCylinder->reflectionXY();
                        objectCylinder->reflectionXZ();
                        objectCylinder->reflectionYZ();
                        objectCylinder->doWorldToCamera(this->scene->cameraTo);


                    case ObjectType::CONE:

                        Cone* objectCone;
                        objectCone = (Cone*)closest;

                        objectCone->setKD();
                        objectCone->setKE();
                        objectCone->setKA();
                        objectCone->setShininess();
                        objectCone->translation();
                        objectCone->rotX();
                        objectCone->rotY();
                        objectCone->rotZ();
                        objectCone->reflectionXY();
                        objectCone->reflectionXZ();
                        objectCone->reflectionYZ();
                        objectCone->doWorldToCamera(this->scene->cameraTo);


                    case ObjectType::MESH:

                        Mesh* objectMesh;
                        objectMesh = (Mesh*)closest;

                        objectMesh->setKD();
                        objectMesh->setKE();
                        objectMesh->setKA();
                        objectMesh->setShininess();
                        objectMesh->translation();
                        objectMesh->rotX();
                        objectMesh->rotY();
                        objectMesh->rotZ();
                        objectMesh->reflectionXY();
                        objectMesh->reflectionXZ();
                        objectMesh->reflectionYZ();
                        objectMesh->scaling();
                        objectMesh->doWorldToCamera(this->scene->cameraTo);


                    case ObjectType::MESH:

                        Mesh* objectMesh;
                        objectMesh = (Mesh*)closest;

                        objectMesh->setKD();
                        objectMesh->setKE();
                        objectMesh->setKA();
                        objectMesh->setShininess();
                        objectMesh->translation();
                        objectMesh->rotX();
                        objectMesh->rotY();
                        objectMesh->rotZ();
                        objectMesh->reflectionXY();
                        objectMesh->reflectionXZ();
                        objectMesh->reflectionYZ();
                        objectMesh->scaling();
                        objectMesh->doWorldToCamera(this->scene->cameraTo);


                    case ObjectType::MESH_TEXTURIZED:

                        MeshTexturized* objectMeshTexturized;
                        objectMeshTexturized = (MeshTexturized*)closest;

                        objectMeshTexturized->setKD();
                        objectMeshTexturized->setKE();
                        objectMeshTexturized->setKA();
                        objectMeshTexturized->setShininess();
                        objectMeshTexturized->translation();
                        objectMeshTexturized->rotX();
                        objectMeshTexturized->rotY();
                        objectMeshTexturized->rotZ();
                        objectMeshTexturized->reflectionXY();
                        objectMeshTexturized->reflectionXZ();
                        objectMeshTexturized->reflectionYZ();
                        objectMeshTexturized->scaling();
                        objectMeshTexturized->doWorldToCamera(this->scene->cameraTo);

                        
                //}
            }
        }
				exit = true;
	}

}



*/