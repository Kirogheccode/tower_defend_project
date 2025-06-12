#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(const string& tag, unsigned int id)
{
	m_tag = tag;
	m_id = id;
}

string Entity::getTag()
{
	return m_tag;
}

Entity::~Entity() {}

EntityManager::EntityManager() {}

void EntityManager::update()
{
	for (auto& e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}

	for (auto& e : m_entities)
	{
		//remove if m_alive = false
	}

	m_toAdd.clear();
}