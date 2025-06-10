#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <vector>
#include <map>
#include <memory>

class Entity;

using namespace std;
using namespace sf;

typedef vector<shared_ptr<Entity>> EntityVec;
typedef map<string, EntityVec> EntityMap;

class EntityManager
{
	EntityVec m_entities;
	EntityVec m_toAdd;
	EntityMap m_entityMap;
	size_t m_totalEntites = 0;

public: 
	EntityManager();
	void update();
	shared_ptr<Entity> addEntity(const string& tag);
	EntityVec& getEntites();
	EntityVec& getEntites(const string& tag);
};