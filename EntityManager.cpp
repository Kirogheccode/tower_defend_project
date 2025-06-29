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

//EntityVec& EntityManager::getEntites(const string& tag)
//{
//
//	return m_entityMap[tag];
//}

EntityVec EntityManager::getEntites(const std::string& tag)
{
    EntityVec results;

    for (const auto& [map_tag, entities] : m_entityMap)
    {
        // Now we compare the tag from the map with the tag we're searching for.
        if (map_tag.find(tag) != std::string::npos)
        {
            // If it's a match, add the vector of entities to our results.
            results.insert(results.end(), entities.begin(), entities.end());
        }
    }

    return results;
}
