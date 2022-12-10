#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include "Includes.h"

int main(int argc, char* argv[]) {

	
	Image* img = new Image("C:/Users/julia/source/repos/Tarefa3/texturamadeira.png");

	Image* ceu = new Image("C:/Users/julia/source/repos/Tarefa3/ceu.jpg");
	
	Plan* plan1 = new Texture(img, new Vector(0., 0., 0.), new Vector(0., 1., 0.), 5.0);

	Light* light = new Point(new Vector(0.7, 0.7, 0.7), new Vector(350, 350, -250));
	

	Mesh* coluna1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	coluna1->meshScaling(50, 500, 30);

	Mesh* coluna2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	coluna2->meshScaling(50, 500, 30);
	coluna2->meshTranslation(650, 0, 0);

	Mesh* coluna3 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	coluna3->meshScaling(50, 500, 30);
	coluna3->meshTranslation(0, 0, -1030);

	Mesh* coluna4 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	coluna4->meshScaling(50, 500, 30);
	coluna4->meshTranslation(650, 0, -1030);


	Mesh* semiteto1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	semiteto1->meshScaling(300, 50, 30);
	semiteto1->meshShearingXY(atan(0.75));
	semiteto1->meshTranslation(50, 450, 0);

	Mesh* semiteto2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	semiteto2->meshScaling(300, 50, 30);
	semiteto2->meshShearingXY(atan(-0.75));
	semiteto2->meshTranslation(350, 675, 0);

	Mesh* semiteto3 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	semiteto3->meshScaling(300, 50, 30);
	semiteto3->meshShearingXY(atan(0.75));
	semiteto3->meshTranslation(50, 450, -1030);

	Mesh* semiteto4 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	semiteto4->meshScaling(300, 50, 30);
	semiteto4->meshShearingXY(atan(-0.75));
	semiteto4->meshTranslation(350, 675, -1030);


	Mesh* teto1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	teto1->meshScaling(450, 30, 1000);
	teto1->meshRotationZ(atan(0.75));
	teto1->meshTranslation(0, 450, -1030);

	Mesh* teto2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	teto2->meshScaling(450, 30, 1000);
	teto2->meshRotationZ(atan(-0.75));
	teto2->meshTranslation(320, 720, -1030);


	Mesh* parede1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	parede1->meshScaling(20, 500, 1000);
	parede1->meshTranslation(30, 0, -1000);

	Mesh* parede2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	parede2->meshScaling(20, 500, 1000);
	parede2->meshTranslation(660, 0, -1000);

	Mesh* parede3 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0);
	parede3->meshScaling(600, 500, 30);
	parede3->meshTranslation(50, 0, -1060);


	Mesh* peMesa1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), 5.0);
	peMesa1->meshScaling(150, 95, -5);
	peMesa1->meshTranslation(275, 0, -200);

	Mesh* peMesa2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), 5.0);
	peMesa2->meshScaling(150, 95, -5);
	peMesa2->meshTranslation(275, 0, -450);


	Mesh* mesa = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), 5.0);
	mesa->meshScaling(150, 5, -250);
	mesa->meshTranslation(275, 95, -200);


	Cylinder* treeBase = new Cylinder(30., new Vector(350., 100., -325.), new Vector(0., 1., 0.), 9.0, new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), 5.0);
	Cylinder* treeTrunk = new Cylinder(6., new Vector(350., 109., -325.), new Vector(0., 1., 0.), 40.0, new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), 5.0);
	Cone* tree = new Cone(60., new Vector(350., 145., -325.), new Vector(0., 1., 0.), 150.0, new Vector(0.0, 0.9, 0.2), new Vector(0.0, 0.9, 0.2), new Vector(0.0, 0.9, 0.2), 5.0);
	Sphere* treeBall = new Sphere(4.5, new Vector(350., 299., -325.), new Vector(1., 1., 0.), new Vector(1., 1., 0.), new Vector(1., 1., 0.), 5.0);

	Scene* scene = new Scene(60, 60, 500, 500, 20, new Color(100, 100, 100, 255));

	scene->setEnvironmentLight(new Vector(0.3, 0.3, 0.3));

	scene->addLight(light);
	scene->addObject(plan1);
	
	scene->addObject(coluna1);
	scene->addObject(coluna2);
	scene->addObject(coluna3);
	scene->addObject(coluna4);
	
	scene->addObject(semiteto1);
	scene->addObject(semiteto2);
	scene->addObject(semiteto3);
	scene->addObject(semiteto4);

	scene->addObject(teto1);
	scene->addObject(teto2);

	scene->addObject(parede1);
	scene->addObject(parede2);
	scene->addObject(parede3);
	
	scene->addObject(peMesa1);
	scene->addObject(peMesa2);
	scene->addObject(mesa);
	
	scene->addObject(treeBase);
	scene->addObject(treeTrunk);
	scene->addObject(tree);
	scene->addObject(treeBall);

	//scene->setBGImage(ceu);

	scene->camera(new Vector(400., 300., 400.), new Vector(400., 250., 0.), new Vector(400., 300., 0.));

	scene->preparePaint();

	return 0;
	

	








	/*

	Image* img = new Image("C:/Users/julia/source/repos/Tarefa3/texturamadeira.png");

	Plan* plan1 = new Texture(img, new Vector(0., -150., 0.), new Vector(0., 1., 0.), 5.0);
	Plan* plan2 = new Plan(new Vector(200., -150., 0.), new Vector(-1., 0., 0.), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), 5.0);
	Plan* plan3 = new Plan(new Vector(200., -150., -400.), new Vector(0., 0., 1.), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), 5.0);
	Plan* plan4 = new Plan(new Vector(-200., -150., 0.), new Vector(1., 0., 0.), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), new Vector(0.686, 0.933, 0.933), 5.0);
	Plan* plan5 = new Plan(new Vector(0., 150., 0.), new Vector(0., -1., 0.), new Vector(0.933, 0.933, 0.933), new Vector(0.933, 0.933, 0.933), new Vector(0.933, 0.933, 0.933), 5.0);

	Cylinder* cylinder = new Cylinder(5., new Vector(0., -150., -200.), new Vector(0., 1., 0.), 90.0, new Vector(0.824, 0.706, 0.549), new Vector(0.824, 0.706, 0.549), new Vector(0.824, 0.706, 0.549), 5.0);

	Cone* cone = new Cone(90.0, new Vector(0., -60., -200.), new Vector(0., 1., 0.), 150.0, new Vector(0., 1., 0.498), new Vector(0., 1., 0.498), new Vector(0., 1., 0.498), 5.0);

	Mesh* cube = Cube::create(new Vector(0., -150., -165.), 40., new Vector(1., 0.078, 0.576), new Vector(1., 0.078, 0.576), new Vector(1., 0.078, 0.576), 5.0);

	Sphere* sphere = new Sphere(5.0, new Vector(0., 95., -200.), new Vector(0.854, 0.647, 0.125), new Vector(0.854, 0.647, 0.125), new Vector(0.854, 0.647, 0.125), 5.0);

	Light* light = new Point(new Vector(0.7, 0.7, 0.7), new Vector(-100., 140., -20.));


	Scene* scene = new Scene(60, 60, 500, 500, 30, new Color(100, 100, 100, 255));

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
	*/
}
