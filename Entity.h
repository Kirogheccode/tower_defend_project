#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "EntityManager.h"
#include "Components.h"

using namespace std;
using namespace sf;

const size_t MaxEntities = 5000;
const size_t MaxComponents = 32;

class EntityManager;

class Entity
{
	friend class EntityManager;
	size_t m_id = 0;
	string m_tag = "default";
	bool m_active = false;

public:
	Entity(const string& tag, const size_t& id);

	shared_ptr<CHealth> cHealth;
	shared_ptr<CMovement> cMovement;
	shared_ptr<CSet> cSet;
	shared_ptr<CCollision> cCollision;
	shared_ptr<CPosition> cPosition;

	bool isActive() const;
	const string& tag() const;
	const size_t& id() const;
	void active(const bool&);
	void destroy();
};
