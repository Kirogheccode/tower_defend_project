#pragma once

#include <SFML/Graphics.hpp>
#include "ComponentManager.h"

#include <iostream>

using namespace std;
using namespace sf;

class Entity
{
	unsigned int m_id = 0;
	string m_tag = "Default";
	bool m_alive = true;

public:
	shared_ptr<CHealth> cHealth;
	shared_ptr<CMovement> cMovement;
	shared_ptr<CSet> cSet;

	Entity(const string& tag, unsigned int id);

	string getTag();

	~Entity();
};
