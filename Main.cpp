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
#include "Texture.h"
#include "Image.h"

int main(int argc, char* argv[]) {


	Image* img = new Image("C:/Users/julia/source/repos/Tarefa3/texturamadeira.png");
	
	Plan* plan1 = new Texture(img, new Vector(0., 0., 0.), new Vector(0., 1., 0.), 5.0);

	Light* light = new Point(new Vector(0.7, 0.7, 0.7), new Vector(350, 350, -250));

	Mesh* col1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	col1->meshScaling(50, 500, 30);

	Mesh* col2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	col2->meshScaling(50, 500, 30);
	col2->meshTranslation(650, 0, 0);

	Mesh* col3 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	col3->meshScaling(50, 500, 30);
	col3->meshTranslation(0, 0, -1030);

	Mesh* col4 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	col4->meshScaling(50, 500, 30);
	col4->meshTranslation(650, 0, -1030);


	Mesh* sc1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	sc1->meshScaling(300, 50, 30);
	sc1->meshShearingXY(atan(0.75));
	sc1->meshTranslation(50, 450, 0);

	Mesh* sc2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	sc2->meshScaling(300, 50, 30);
	sc2->meshShearingXY(atan(-0.75));
	sc2->meshTranslation(350, 675, 0);

	Mesh* sc3 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	sc3->meshScaling(300, 50, 30);
	sc3->meshShearingXY(atan(0.75));
	sc3->meshTranslation(50, 450, -1030);

	Mesh* sc4 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	sc4->meshScaling(300, 50, 30);
	sc4->meshShearingXY(atan(-0.75));
	sc4->meshTranslation(350, 675, -1030);


	Mesh* c1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	c1->meshScaling(450, 30, 1000);
	c1->meshShearingXY(atan(0.75));
	c1->meshTranslation(0, 450, -1030);

	Mesh* c2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	c2->meshScaling(450, 30, 1000);
	c2->meshShearingXY(atan(0.75));
	c2->meshTranslation(0, 450, -1030);


	Mesh* w1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	w1->meshScaling(20, 500, 1000);
	w1->meshTranslation(30, 0, -1000);

	Mesh* w2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	w2->meshScaling(20, 500, 1000);
	w2->meshTranslation(660, 0, -1000);

	Mesh* w3 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	w3->meshScaling(600, 500, 30);
	w3->meshTranslation(50, 0, -1060);


	Mesh* tf1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	tf1->meshScaling(150, 95, -5);
	tf1->meshTranslation(275, 0, -200);

	Mesh* tf2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	tf2->meshScaling(150, 95, -5);
	tf2->meshTranslation(275, 0, -450);


	Mesh* tt = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	tt->meshScaling(150, 5, -250);
	tt->meshTranslation(275, 95, -200);


	Cylinder* tB = new Cylinder(30., new Vector(350., 100., -325.), new Vector(0., 1., 0.), 9.0, new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), 5.0);
	Cylinder* tT = new Cylinder(6., new Vector(350., 109., -325.), new Vector(0., 1., 0.), 40.0, new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), 5.0);
	Cone* tC = new Cone(60., new Vector(350., 100., -325.), new Vector(0., 1., 0.), 150.0, new Vector(0.0, 0.9, 0.2), new Vector(0.0, 0.9, 0.2), new Vector(0.0, 0.9, 0.2), 5.0);
	Sphere* tBall = new Sphere(4.5, new Vector(350., 299., -325.), new Vector(1., 1., 0.), new Vector(1., 1., 0.), new Vector(1., 1., 0.), 5.0);

	Scene* scene = new Scene(60, 60, 500, 500, 20, new Color(100, 100, 100, 255));

	scene->setEnvironmentLight(new Vector(0.3, 0.3, 0.3));

	scene->addLight(light);
	scene->addObject(plan1);
	scene->addObject(col1);
	scene->addObject(col2);
	scene->addObject(col3);
	scene->addObject(col4);
	scene->addObject(sc1);
	scene->addObject(sc2);
	scene->addObject(sc3);
	scene->addObject(sc4);
	scene->addObject(c1);
	scene->addObject(c2);
	scene->addObject(w1);
	scene->addObject(w2);
	scene->addObject(w3);
	scene->addObject(tf1);
	scene->addObject(tf2);
	scene->addObject(tt);
	scene->addObject(tB);
	scene->addObject(tT);
	scene->addObject(tC);
	scene->addObject(tBall);

	scene->camera(new Vector(400., 400., 400.), new Vector(400., 250., 0.), new Vector(400., 400., 0.));

	scene->preparePaint();

	return 0;
}
