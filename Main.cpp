#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include "Includes.h"



int main(int argc, char* argv[]) {

	Image* img = new Image("C:/Users/julia/source/repos/Tarefa3/texturamadeira.png");

	Image* ceu = new Image("C:/Users/julia/source/repos/Tarefa3/ceu.jpg");
	
	Plan* plan1 = new Texture(img, new Vector(0., 0., 0.), new Vector(0., 1., 0.), 5.0);

	Light* light = new Point(new Vector(0.7, 0.7, 0.7), new Vector(350., 350., -250.));
	
	Cluster* cluster = new Cluster(0.5, new Vector(0.5, 0., 0.5), new Vector(0.0, 1.0, 0.0), 1.0);

	Mesh* coluna1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	coluna1->meshScaling(50, 500, 30);

	Mesh* coluna2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	coluna2->meshScaling(50, 500, 30);
	coluna2->meshTranslation(650, 0, 0);

	Mesh* coluna3 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	coluna3->meshScaling(50, 500, 30);
	coluna3->meshTranslation(0, 0, -1030);

	Mesh* coluna4 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	coluna4->meshScaling(50, 500, 30);
	coluna4->meshTranslation(650, 0, -1030);


	Mesh* semiteto1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	semiteto1->meshScaling(300, 50, 30);
	semiteto1->meshShearingXY(atan(0.75));
	semiteto1->meshTranslation(50, 450, 0);

	Mesh* semiteto2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	semiteto2->meshScaling(300, 50, 30);
	semiteto2->meshShearingXY(atan(-0.75));
	semiteto2->meshTranslation(350, 675, 0);

	Mesh* semiteto3 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	semiteto3->meshScaling(300, 50, 30);
	semiteto3->meshShearingXY(atan(0.75));
	semiteto3->meshTranslation(50, 450, -1030);

	Mesh* semiteto4 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	semiteto4->meshScaling(300, 50, 30);
	semiteto4->meshShearingXY(atan(-0.75));
	semiteto4->meshTranslation(350, 675, -1030);


	Mesh* teto1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	teto1->meshScaling(450, 30, 1000);
	teto1->meshRotationZ(atan(0.75));
	teto1->meshTranslation(0, 450, -1030);

	Mesh* teto2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	teto2->meshScaling(450, 30, 1000);
	teto2->meshRotationZ(atan(-0.75));
	teto2->meshTranslation(320, 720, -1030);


	Mesh* parede1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	parede1->meshScaling(20, 500, 1000);
	parede1->meshTranslation(30, 0, -1000);

	Mesh* parede2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	parede2->meshScaling(20, 500, 1000);
	parede2->meshTranslation(660, 0, -1000);

	Mesh* parede3 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, cluster);
	parede3->meshScaling(600, 500, 30);
	parede3->meshTranslation(50, 0, -1060);


	Mesh* peMesa1 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), 5.0, cluster);
	peMesa1->meshScaling(150, 95, -5);
	peMesa1->meshTranslation(275, 0, -200);

	Mesh* peMesa2 = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), 5.0, cluster);
	peMesa2->meshScaling(150, 95, -5);
	peMesa2->meshTranslation(275, 0, -450);


	Mesh* mesa = Cube::create(new Vector(0.5, 0., 0.5), 1, new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), new Vector(0, 0.898, 0.898), 5.0, cluster);
	mesa->meshScaling(150, 5, -250);
	mesa->meshTranslation(275, 95, -200);


	Cylinder* baseArvore = new Cylinder(30., new Vector(350., 100., -325.), new Vector(0., 1., 0.), 9.0, new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), 5.0);
	Cylinder* troncoArvore = new Cylinder(6., new Vector(350., 109., -325.), new Vector(0., 1., 0.), 40.0, new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), new Vector(0.9, 0.6, 0.1), 5.0);
	Cone* arvore = new Cone(60., new Vector(350., 145., -325.), new Vector(0., 1., 0.), 150.0, new Vector(0.0, 0.9, 0.2), new Vector(0.0, 0.9, 0.2), new Vector(0.0, 0.9, 0.2), 5.0);
	Sphere* bolaArvore = new Sphere(4.5, new Vector(350., 299., -325.), new Vector(1., 1., 0.), new Vector(1., 1., 0.), new Vector(1., 1., 0.), 5.0);

	Scene* scene = new Scene(60, 60, 500, 500, 20, new Color(100, 100, 100, 255));

	scene->setEnvironmentLight(new Vector(0.3, 0.3, 0.3));

	scene->addLight(light);
	scene->addObject(plan1);
	/*
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
	*/
	//scene->addObject(baseArvore);
	//scene->addObject(troncoArvore);
	//scene->addObject(arvore);
	//scene->addObject(bolaArvore);

	//scene->setBGImage(ceu);

	scene->camera(new Vector(400., 300., 400.), new Vector(400., 250., 0.), new Vector(400., 300., 0.));

	scene->preparePaint();

	return 0;

}
