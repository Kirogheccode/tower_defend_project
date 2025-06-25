#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager() {};

shared_ptr<Entity> EntityManager::addEntity(const string& tag)
{
	auto e = make_shared<Entity>(tag, m_totalEntites++);
	m_entities.push_back(e);

	m_entityMap[e->tag()].push_back(e);

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

