#pragma once
#include "Scene.h"

class Scene;

class Interaction {

public:

	Scene* scene = nullptr;

	void picking();

	void changeProjection();



};

