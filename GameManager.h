#pragma once
#include <iostream>
#include <vector>
#include "Controller.h"
#include "Components.h"
#include "ComponentsArray.h"

class GameManager
{
	Coordinator GameBehavior;

public:
	void Init()
	{
		// Initialize the game behavior
		GameBehavior.Init();
		GameBehavior.RegisterComponent<CVelocity>();

		std::vector<Entity> entities(cmpAux::MAX_ENTITIES - 1);
	}

};