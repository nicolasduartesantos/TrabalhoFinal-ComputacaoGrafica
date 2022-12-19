#include <iostream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include "Includes.h"



int main(int argc, char* argv[]) {

	Image* chao = new Image("C:/Users/Nicolas/source/repos/Tarefa3/chao.jpg");
	Image* pipe = new Image("C:/Users/Nicolas/source/repos/Tarefa3/image.png");
	Image* pearl = new Image("C:/Users/Nicolas/source/repos/Tarefa3/pearl.jpg");
	Image* night = new Image("C:/Users/Nicolas/source/repos/Tarefa3/night.jpg");
	Image* dog = new Image("C:/Users/Nicolas/source/repos/Tarefa3/dog.jpg");
	Image* dali = new Image("C:/Users/Nicolas/source/repos/Tarefa3/dali.jpg");


	Light* directional = new Directional(new Vector(0.7, 0.7, 0.7), new Vector(1., -1., 0.));
	Light* spot_esq = new Spot(new Vector(0.7, 0.7, 0.7), new Vector(-120., 49., 50.), new Vector(-0.13, -1., -0.1), M_PI / 18);
	Light* spot_dir = new Spot(new Vector(0.7, 0.7, 0.7), new Vector(120., 49., 50.), new Vector(0.13, -1., -0.1), M_PI / 18);
	Light* spot_meio = new Spot(new Vector(0.7, 0.7, 0.7), new Vector(0., 49., 160.), new Vector(0., -1., 0.), M_PI / 9);
	Light* pontual = new Point(new Vector(0.7, 0.7, 0.7), new Vector(0., 45., 150.));

	Environment* environmentLight = new Environment(new Vector(0.3, 0.3, 0.3));


	Plan* plan_floor = new Texture(chao, new Vector(0., -150., 0.), new Vector(0., 1., 0.), 5.0);
	Plan* plan_leftwall = new Plan(new Vector(-200., -150., 0.), new Vector(1., 0., 0.), new Vector(1., 0.829, 0.829), new Vector(0.296648, 0.296648, 0.296648), new Vector(0.25, 0.20725, 0.20725), 0.5);
	Plan* plan_rightwall = new Plan(new Vector(200., -150., 0.), new Vector(-1., 0., 0.), new Vector(1., 0.829, 0.829), new Vector(0.296648, 0.296648, 0.296648), new Vector(0.25, 0.20725, 0.20725), 0.5);
	Plan* plan_frontwall = new Plan(new Vector(200., -150., 0.), new Vector(0., 0., 1.), new Vector(1., 0.829, 0.829), new Vector(0.296648, 0.296648, 0.296648), new Vector(0.25, 0.20725, 0.20725), 0.5);
	Plan* plan_ceiling = new Plan(new Vector(0., 50., 0.), new Vector(0., -1., 0.), new Vector(1., 0.829, 0.829), new Vector(0.296648, 0.296648, 0.296648), new Vector(0.25, 0.20725, 0.20725), 0.5);
	Plan* plan_backwall = new Plan(new Vector(200., -150., 300.), new Vector(0., 0., -1.), new Vector(1., 0.829, 0.829), new Vector(0.296648, 0.296648, 0.296648), new Vector(0.25, 0.20725, 0.20725), 0.5);

	Cylinder* stand_esq = new Cylinder(17., new Vector(-140., -150., 30.), new Vector(0., 1., 0.), 60., new Vector(0.50754, 0.50754, 0.50754), new Vector(0.508273, 0.508273, 0.508273), new Vector(0.19225, 0.19225, 0.19225), 10.);
	Cylinder* stand_dir = new Cylinder(17., new Vector(140., -150., 30.), new Vector(0., 1., 0.), 60., new Vector(0.50754, 0.50754, 0.50754), new Vector(0.508273, 0.508273, 0.508273), new Vector(0.19225, 0.19225, 0.19225), 10.);
	Cylinder* stand_meio = new Cylinder(20., new Vector(0., -150., 160.), new Vector(0., 1., 0.), 50., new Vector(0.50754, 0.50754, 0.50754), new Vector(0.508273, 0.508273, 0.508273), new Vector(0.19225, 0.19225, 0.19225), 10.);

	Cone* ampulheta_debaixo = new Cone(15., new Vector(-140., -90., 30.), new Vector(0., 1., 0.), 30., new Vector(0.61424, 0.04136, 0.04136), new Vector(0.727811, 0.626959, 0.626959), new Vector(0.1745, 0.01175, 0.01175), 0.6);
	Cone* ampulheta_decima = new Cone(15., new Vector(-140., -30., 30.), new Vector(0., -1., 0.), 30., new Vector(0.61424, 0.04136, 0.04136), new Vector(0.727811, 0.626959, 0.626959), new Vector(0.1745, 0.01175, 0.01175), 0.6);

	Sphere* bola_maior = new Sphere(15., new Vector(140., -75., 30.), new Vector(0.07568, 0.61424, 0.07568), new Vector(0.633, 0.727811, 0.633), new Vector(0.0215, 0.1745, 0.0215), 0.6);
	Sphere* bola_media = new Sphere(10., new Vector(128., -53., 30.), new Vector(0.07568, 0.61424, 0.07568), new Vector(0.633, 0.727811, 0.633), new Vector(0.0215, 0.1745, 0.0215), 0.6);
	Sphere* bola_menor = new Sphere(7., new Vector(140., -43., 31.), new Vector(0.07568, 0.61424, 0.07568), new Vector(0.633, 0.727811, 0.633), new Vector(0.0215, 0.1745, 0.0215), 0.6);

	Cylinder* cilindro1 = new Cylinder(2., new Vector(-90., -149., 25.), new Vector(0., 1., 0.), 70., new Vector(0.75164, 0.60648, 0.22648), new Vector(0.628281, 0.555802, 0.366065), new Vector(0.24725, 0.1995, 0.0745), 5.);
	Cylinder* base1 = new Cylinder(5., new Vector(-90., -150., 25.), new Vector(0., 1., 0.), 1., new Vector(0.75164, 0.60648, 0.22648), new Vector(0.628281, 0.555802, 0.366065), new Vector(0.24725, 0.1995, 0.0745), 5.);
	Sphere* bola1 = new Sphere(4., new Vector(-90., -75., 25.), new Vector(0.75164, 0.60648, 0.22648), new Vector(0.628281, 0.555802, 0.366065), new Vector(0.24725, 0.1995, 0.0745), 5.0);

	Cylinder* cilindro2 = new Cylinder(2., new Vector(90., -147., 25.), new Vector(0., 1., 0.), 70., new Vector(0.75164, 0.60648, 0.22648), new Vector(0.628281, 0.555802, 0.366065), new Vector(0.24725, 0.1995, 0.0745), 5.);
	Cylinder* base2 = new Cylinder(5., new Vector(90., -150., 25.), new Vector(0., 1., 0.), 1., new Vector(0.75164, 0.60648, 0.22648), new Vector(0.628281, 0.555802, 0.366065), new Vector(0.24725, 0.1995, 0.0745), 5.);
	Sphere* bola2 = new Sphere(4., new Vector(90., -75., 25.), new Vector(0.75164, 0.60648, 0.22648), new Vector(0.628281, 0.555802, 0.366065), new Vector(0.24725, 0.1995, 0.0745), 5.0);

	Cylinder* barreira = new Cylinder(1., new Vector(-86., -75., 25.), new Vector(1., 0., 0.), 172., new Vector(0.4353, 0., 0.), new Vector(0.4353, 0., 0.), new Vector(0.4353, 0., 0.), 1.);




	// quadro do MEIO
	Cluster* cluster1 = new Cluster(70., new Vector(0.5, 0., 0.5), new Vector(0.0, 1.0, 0.0), 120.0);
	MeshTexturized* quadro_meio = Cube::createWithTexture(new Vector(0.5, 0., 0.5), 100., pipe, 5.0, cluster1);
	quadro_meio->getFaces()[0]->setActive(false);
	quadro_meio->getFaces()[1]->setActive(false);
	quadro_meio->getFaces()[2]->setActive(false);
	quadro_meio->getFaces()[3]->setActive(false);
	quadro_meio->getFaces()[4]->setActive(true);
	quadro_meio->getFaces()[5]->setActive(true);
	quadro_meio->getFaces()[6]->setActive(false);
	quadro_meio->getFaces()[7]->setActive(false);
	quadro_meio->getFaces()[8]->setActive(false);
	quadro_meio->getFaces()[9]->setActive(false);
	quadro_meio->getFaces()[10]->setActive(false);
	quadro_meio->getFaces()[11]->setActive(false);

	quadro_meio->translation(0., -80., 45.);


	// quadro 1 na parede ESQUERDA
	Cluster* cluster2 = new Cluster(70., new Vector(0.5, 0., 0.5), new Vector(0.0, 1.0, 0.0), 120.0);
	MeshTexturized* quadro_esq1 = Cube::createWithTexture(new Vector(0.5, 0., 0.5), 100., pearl, 5.0, cluster2);
	quadro_esq1->getFaces()[0]->setActive(false);
	quadro_esq1->getFaces()[1]->setActive(false);
	quadro_esq1->getFaces()[2]->setActive(false);
	quadro_esq1->getFaces()[3]->setActive(false);
	quadro_esq1->getFaces()[4]->setActive(true);
	quadro_esq1->getFaces()[5]->setActive(true);
	quadro_esq1->getFaces()[6]->setActive(false);
	quadro_esq1->getFaces()[7]->setActive(false);
	quadro_esq1->getFaces()[8]->setActive(false);
	quadro_esq1->getFaces()[9]->setActive(false);
	quadro_esq1->getFaces()[10]->setActive(false);
	quadro_esq1->getFaces()[11]->setActive(false);

	quadro_esq1->translation(0., -80., 45.);
	quadro_esq1->rotY(M_PI / 2);
	quadro_esq1->translation(-195., 0., 95.);


	// quadro 2 na parede ESQUERDA
	Cluster* cluster3 = new Cluster(70., new Vector(0.5, 0., 0.5), new Vector(0.0, 1.0, 0.0), 120.0);
	MeshTexturized* quadro_esq2 = Cube::createWithTexture(new Vector(0.5, 0., 0.5), 100., night, 5.0, cluster3);
	quadro_esq2->getFaces()[0]->setActive(false);
	quadro_esq2->getFaces()[1]->setActive(false);
	quadro_esq2->getFaces()[2]->setActive(false);
	quadro_esq2->getFaces()[3]->setActive(false);
	quadro_esq2->getFaces()[4]->setActive(true);
	quadro_esq2->getFaces()[5]->setActive(true);
	quadro_esq2->getFaces()[6]->setActive(false);
	quadro_esq2->getFaces()[7]->setActive(false);
	quadro_esq2->getFaces()[8]->setActive(false);
	quadro_esq2->getFaces()[9]->setActive(false);
	quadro_esq2->getFaces()[10]->setActive(false);
	quadro_esq2->getFaces()[11]->setActive(false);

	quadro_esq2->translation(0., -80., 45.);
	quadro_esq2->rotY(M_PI / 2);
	quadro_esq2->translation(-195., 0., 215.);


	// quadro 1 na parede DIREITA
	Cluster* cluster4 = new Cluster(70., new Vector(0.5, 0., 0.5), new Vector(0.0, 1.0, 0.0), 120.0);
	MeshTexturized* quadro_dir1 = Cube::createWithTexture(new Vector(0.5, 0., 0.5), 100., dog, 5.0, cluster4);
	quadro_dir1->getFaces()[0]->setActive(false);
	quadro_dir1->getFaces()[1]->setActive(false);
	quadro_dir1->getFaces()[2]->setActive(false);
	quadro_dir1->getFaces()[3]->setActive(false);
	quadro_dir1->getFaces()[4]->setActive(true);
	quadro_dir1->getFaces()[5]->setActive(true);
	quadro_dir1->getFaces()[6]->setActive(false);
	quadro_dir1->getFaces()[7]->setActive(false);
	quadro_dir1->getFaces()[8]->setActive(false);
	quadro_dir1->getFaces()[9]->setActive(false);
	quadro_dir1->getFaces()[10]->setActive(false);
	quadro_dir1->getFaces()[11]->setActive(false);

	quadro_dir1->translation(0., -80., 45.);
	quadro_dir1->rotY(3 * M_PI / 2);
	quadro_dir1->translation(195., 0., 95.);



	// quadro 2 na parede DIREITA
	Cluster* cluster5 = new Cluster(70., new Vector(0.5, 0., 0.5), new Vector(0.0, 1.0, 0.0), 120.0);
	MeshTexturized* quadro_dir2 = Cube::createWithTexture(new Vector(0.5, 0., 0.5), 100., dali, 5.0, cluster5);
	quadro_dir2->getFaces()[0]->setActive(false);
	quadro_dir2->getFaces()[1]->setActive(false);
	quadro_dir2->getFaces()[2]->setActive(false);
	quadro_dir2->getFaces()[3]->setActive(false);
	quadro_dir2->getFaces()[4]->setActive(true);
	quadro_dir2->getFaces()[5]->setActive(true);
	quadro_dir2->getFaces()[6]->setActive(false);
	quadro_dir2->getFaces()[7]->setActive(false);
	quadro_dir2->getFaces()[8]->setActive(false);
	quadro_dir2->getFaces()[9]->setActive(false);
	quadro_dir2->getFaces()[10]->setActive(false);
	quadro_dir2->getFaces()[11]->setActive(false);

	quadro_dir2->translation(0., -80., 45.);
	quadro_dir2->rotY(3 * M_PI / 2);
	quadro_dir2->translation(195., 0., 215.);


	Cluster* clusterteste = new Cluster(60, new Vector(0.5, 0., 0.5), new Vector(0.0, 1.0, 0.0), 120.0);
	Mesh2* cube = Cube::createComplex(new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), new Vector(0.898, 0.898, 0), 5.0, clusterteste);

	cube->translation(0, 0, 0);
	cube->scaling(20., 20., 20.);
	cube->translation(0, -100, 160);



	Scene* scene = new Scene(100, 100, 350, 350, 20, new Color(100, 100, 100, 255));


	scene->setEnvironmentLight(environmentLight);
	scene->addLight(pontual);

	scene->addLight(spot_esq);
	scene->addLight(spot_dir);
	scene->addLight(spot_meio);
	scene->addLight(directional);
	
	scene->addObject(plan_floor);
	scene->addObject(plan_leftwall);
	scene->addObject(plan_rightwall);
	scene->addObject(plan_frontwall);
	scene->addObject(plan_backwall);
	scene->addObject(plan_ceiling);

	scene->addObject(stand_esq);
	scene->addObject(stand_dir);
	scene->addObject(stand_meio);

	scene->addObject(ampulheta_debaixo);
	scene->addObject(ampulheta_decima);
	
	scene->addObject(bola_maior);
	scene->addObject(bola_media);
	scene->addObject(bola_menor);

	scene->addObject(cilindro1);
	scene->addObject(base1);
	scene->addObject(bola1);
	scene->addObject(cilindro2);
	scene->addObject(base2);
	scene->addObject(bola2);
	scene->addObject(barreira);

	scene->addObject(cube);
	
	scene->addObject(quadro_meio);
	scene->addObject(quadro_esq1);
	scene->addObject(quadro_esq2);
	scene->addObject(quadro_dir1);
	scene->addObject(quadro_dir2);



	//scene->camera(new Vector(0., 0., 299.), new Vector(0., 0., -1.), new Vector(0., 1., 0.)); // visao frontal
	//scene->camera(new Vector(100., 0., 250.), new Vector(-0.8, 0., -2.), new Vector(0., 1., 0.)); // visao para a diagonal esquerda
	//scene->camera(new Vector(150., 0., 270.), new Vector(-1.1, 0., -2.), new Vector(0., 1., 0.)); //visao grande da sala

	//scene->camera(new Vector(150., 0., 150.), new Vector(-2., 0.3, -2.), new Vector(0., 1., 0.)); // tentando olhar pra parede esquerda
	scene->camera(new Vector(100., 40., 100.), new Vector(-100., 0., 150.), new Vector(0., 30000., 0.)); // parede esquerda
	//scene->camera(new Vector(-150., 0., 150.), new Vector(100., 0., 150.), new Vector(0., 30000., 0.)); // parede direita
	//scene->camera(new Vector(-150., 0., 100.), new Vector(100., 0., 150.), new Vector(0., 30000., 0.)); // womans view
	//scene->camera(new Vector(-150., 0., 100.), new Vector(100., 0., 150.), new Vector(0., 30000., 0.))
	//scene->camera(new Vector(50., 0., 200.), new Vector(0., 0., 0.), new Vector(0., 1., 0.)); 
	//scene->camera(new Vector(0., 0., 130.), new Vector(0., 0., 0.), new Vector(0., 1., 0.)); 


	scene->interaction = new Interaction();

	scene->interaction->scene = scene;

	scene->mainLoop();

	return 0;
}