#include <iostream>
using namespace std;

#include <SDL.h>
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




int main(int argc, char* argv[]) {

	Sphere* sphere = new Sphere(40.0, new Vector(0.7, 0.2, 0.2), new Vector(0.7, 0.2, 0.2), new Vector(0.7, 0.2, 0.2), new Vector(0, 0, -100), 10.0);
	
	Cylinder* cylinder = new Cylinder((40.0 / 3), new Vector(0, 0, -100), new Vector(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)), 120.0, new Vector(0.2, 0.3, 0.8), new Vector(0.2, 0.3, 0.8), new Vector(0.2, 0.3, 0.8), 10.0);

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

	scene->preparePaint();

	return 0;
}
