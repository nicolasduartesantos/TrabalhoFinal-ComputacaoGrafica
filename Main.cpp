#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cmath>
#include <math.h>
#include<algorithm>
#include "libSDL.h"
#include "Vector.h"
#include "Color.h"
#include "Light.h"
#include "Object.h"
#include "Plan.h"
#include "Sphere.h"
#include "Scene.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Mesh.h"
#include "Cube.h"
#include "TexturePlan.h"
#include "Image.h"

int main(int argc, char* argv[]) {

	/*
	Sphere* sphere = new Sphere(40.0, new Vector(0.7, 0.2, 0.2), new Vector(0.7, 0.2, 0.2), new Vector(0.7, 0.2, 0.2), new Vector(0, 0, -100), 10.0);
	Cylinder* cylinder = new Cylinder((40.0 / 3), new Vector(0, 0, -100), new Vector(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)), 120.0, new Vector(0.2, 0.3, 0.8), new Vector(0.2, 0.3, 0.8), new Vector(0.2, 0.3, 0.8), 10.0);
	Vector center_top = Vector(0, 0, -100) + Vector(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)) * 120.0;
	Vector* centerTop = new Vector(center_top.getCoordinate(0), center_top.getCoordinate(1), center_top.getCoordinate(2));
	Cone* cone = new Cone(20.0, centerTop, new Vector(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)), 20.0, new Vector(0.8, 0.3, 0.2), new Vector(0.8, 0.3, 0.2), new Vector(0.8, 0.3, 0.2), 10.0);
	Plan* plan_floor = new Plan(new Vector(0., -40., 0.), new Vector(0., 1., 0.), new Vector(0.2, 0.7, 0.2), new Vector(0., 0., 0.), new Vector(0.2, 0.7, 0.2), 1.0);
	Plan* plan_back = new Plan(new Vector(0., 0., -200.), new Vector(0., 0., 1.), new Vector(0.3, 0.3, 0.7), new Vector(0., 0., 0.), new Vector(0.3, 0.3, 0.7), 1.0);
	Light* light = new Light(new Vector(0.7, 0.7, 0.7), new Vector(0., 60., -30.));
	Scene* scene = new Scene(new Vector(0., 0., 0.), 60, 60, 500, 500, 30, new Color(100, 100, 100, 255));
	scene->setEnvironmentLight(new Vector(0.3, 0.3, 0.3));
	scene->addLight(light);
	scene->addObject(plan_back);
	scene->addObject(plan_floor);
	scene->addObject(sphere);
	scene->addObject(cylinder);
	scene->addObject(cone);
	*/

	Image* img = new Image("C:/Users/julia/source/repos/Tarefa3/texturamadeira.png");
	
	//Plan* plan1 = new Plan(new Vector(0., -150., 0.), new Vector(0., 1., 0.), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), 5.0);
	
	Plan* plan1 = new TexturePlan(img, new Vector(0., -150., 0.), new Vector(0., 1., 0.), 5.0);
	Plan* plan2 = new Plan(new Vector(200., -150., 0.), new Vector(-1., 0., 0.), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), 5.0);
	Plan* plan3 = new Plan(new Vector(200., -150., -400.), new Vector(0., 0., 1.), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), 5.0);
	Plan* plan4 = new Plan(new Vector(-200., -150., 0.), new Vector(1., 0., 0.), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), 5.0);
	Plan* plan5 = new Plan(new Vector(0., 150., 0.), new Vector(0., -1., 0.), new Vector(0.933, 0.933, 0.933), new Vector(0.933, 0.933, 0.933), new Vector(0.933, 0.933, 0.933), 5.0);

	Cylinder* cylinder = new Cylinder(5., new Vector(0., -150., -200.), new Vector(0., 1., 0.), 90.0, new Vector(0.824, 0.706, 0.549), new Vector(0.824, 0.706, 0.549), new Vector(0.824, 0.706, 0.549), 5.0);

	Cone* cone = new Cone(90.0, new Vector(0., -60., -200.), new Vector(0., 1., 0.), 150.0, new Vector(0., 1., 0.498), new Vector(0., 1., 0.498), new Vector(0., 1., 0.498), 5.0);

	Mesh* cube = Cube::create(new Vector(0., -150., -165.), 40., new Vector(1., 0.078, 0.576), new Vector(1., 0.078, 0.576), new Vector(1., 0.078, 0.576), 5.0);

	Sphere* sphere = new Sphere(5.0, new Vector(0., 95., -200.), new Vector(0.854, 0.647, 0.125), new Vector(0.854, 0.647, 0.125), new Vector(0.854, 0.647, 0.125), 5.0);

	Light* light = new Light(new Vector(0.7, 0.7, 0.7), new Vector(-100., 140., -20.));

	Scene* scene = new Scene(new Vector(0., 0., 0.), 60, 60, 500, 500, 30, new Color(100, 100, 100, 255));

	scene->setEnvironmentLight(new Vector(0.3, 0.3, 0.3));

	scene->addLight(light);

	scene->addObject(plan1);
	scene->addObject(plan2);
	scene->addObject(plan3);
	scene->addObject(plan4);
	scene->addObject(plan5);
	scene->addObject(cylinder);
	scene->addObject(sphere);
	scene->addObject(cone);
	scene->addObject(cube);

	scene->preparePaint();

	return 0;
}