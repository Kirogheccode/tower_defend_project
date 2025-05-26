#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "Tilemap.h"

class Enemy :
    public Entity
{
protected:
	int m_iHealth;
	int m_iDamage;
	float m_fSpeed;
	int m_iPathIndex;
	sf::Sprite m_sEnemySprite;

public:

	int GetHealth() const
	{
		return m_iHealth;
	}
	
	int GetDamage() const
	{
		return m_iDamage;
	}

	void Update()
	{
		if (m_bDeletionRequested)
			return;
	}

	void setPathIndex(int index)
	{
		m_iPathIndex = index;
	}

	void findPath()
	{
		// Logic to find path
	}

	void virtual setHealth() = 0;
	void virtual setDamage() = 0;
	void virtual setSpeed() = 0;
	void virtual setSprite() = 0;
};

class EnemyType1 : protected Enemy
{
	void setHealth() override
	{
		m_iHealth = 3;
	}

	void setDamage() override
	{
		m_iDamage = 1;
	}

	void setSpeed() override
	{
		m_fSpeed = 2.5f;
	}

	void setSprite() override
	{
	}
};


class EnemyType1 : protected Enemy
{
	void setHealth() override
	{
		m_iHealth = 5;
	}

	void setDamage() override
	{
		m_iDamage = 3;
	}

	void setSpeed() override
	{
		m_fSpeed = 0.5f;
	}

	void setSprite() override
	{
	}
};


