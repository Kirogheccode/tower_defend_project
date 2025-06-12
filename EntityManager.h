#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "ComponentManager.h"
#include "ComponentsArray.h"
#include "Components.h"

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cassert>

using namespace std;
using namespace sf;

typedef vector<shared_ptr<Entity>> EntityVec;
typedef map<string, EntityVec> EntityMap;


class EntityManager
{
	EntityVec m_entities;
	EntityVec m_toAdd;
	EntityMap m_entityMap;
	unsigned int m_totalEntites = 0;

	// Queue of unused entity IDs
	std::queue<Entity> mAvailableEntities{};

	// Array of signatures where the index corresponds to the entity ID
	std::array<cmpAux::Signature, cmpAux::MAX_ENTITIES> mSignatures{};

	uint32_t mLivingEntityCount{};


public: 
	
	// Total living entities - used to keep limits on how many exist
	EntityManager()
	{
		// Initialize the queue with all possible entity IDs
		for (cmpAux::eID curEntity = 0; curEntity < cmpAux::MAX_ENTITIES; ++curEntity)
		{
			// Create an Entity object with the ID and push it into the queue
			Entity entity("Default", curEntity);
			mAvailableEntities.push(entity);
		}
	}
	Entity CreateEntity()
	{
		assert(mLivingEntityCount < cmpAux::MAX_ENTITIES && "Too many entities in existence.");       

		// Take an ID from the front of the queue
		Entity id = mAvailableEntities.front();
		mAvailableEntities.pop();
		++mLivingEntityCount;

		return id;
	}

	void DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the destroyed entity's signature
		mSignatures[entity].reset();

		// Put the destroyed ID at the back of the queue
		mAvailableEntities.push(entity);
		--mLivingEntityCount;
	}

	void SetSignature(Entity entity, cmpAux::Signature signature)
	{
		assert(entity < cmpAux::MAX_ENTITIES && "Entity out of range.");

		// Put this entity's signature into the array
		mSignatures[entity] = signature;
	}

	cmpAux::Signature GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Get this entity's signature from the array
		return mSignatures[entity];
	}


	void update();

	EntityVec& getEntites();
	EntityVec& getEntites(const string& tag);
};

