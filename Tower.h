#pragma once
#include "Entity.h"
#include "MathSupport.h"
#include "Bullet.h"
#include <vector>
class Tower :
    public Entity
{	
protected:
	float m_fTimeToFire; //time between shots
	int m_iCost; //cost to build
	int m_iDamage;	//damage per shot
	float m_fRange; //range of the tower
	sf::Sprite m_sTowerSprite;
	Bullet m_Bullet;
	Entity* pNearestEnemy = nullptr;
public:
	Tower(float, float, const sf::Texture&, int, int, float, float);

	void Attack(sf::Time, std::vector<Enemy>, std::vector<Bullet>);

	int GetCost() const
	{
		return m_iCost;
	}

	int GetDamage() const
	{
		return m_iDamage;
	}

	float GetRange() const
	{
		return m_fRange;
	}

	void virtual setCost() = 0;
	void virtual setDamage() = 0;
	void virtual setBullet() = 0;
	void virtual setRange() = 0;
	void virtual setSprite() = 0;
};
class TowerType1 : protected Tower
{
public:
	void setCost() override
	{
		m_iCost = 100;
	}

	void setDamage() override
	{
		m_iDamage = 10;
	}

	void setBullet() override
	{
	}

	void setRange() override
	{
		m_fRange = 200.0f;
	}

	void setSprite() override
	{
	}
};

