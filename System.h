#pragma once
#include <set>
#include "Entity.h"
#include "Components.h"
#include "ComponentsArray.h"
#include "ComponentManager.h"

class System
{
public:
	std::set<Entity> mEntities;
};
