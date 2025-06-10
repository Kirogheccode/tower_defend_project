#include "EntityManager.h"

EntityManager::EntityManager() {};

void EntityManager::update()
{
	for (auto& e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}

	for (auto& e : m_entities)
	{
		//remove if m_alive = false
	}

	m_toAdd.clear();
}

shared_ptr<Entity> EntityManager::addEntity(const string& tag)
{
	auto e = make_shared<Entity>(tag, m_totalEntites++);
	m_toAdd.push_back(e);
	return e;
}

EntityVec& EntityManager::getEntites()
{
	return m_entities;
}

EntityVec& EntityManager::getEntites(const string& tag)
{
	return m_entityMap[tag];
}