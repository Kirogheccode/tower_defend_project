#pragma once
#include "Entity.h"
#include "MathSupport.h"
#include "Bullet.h"
#include <vector>
class Tower :
    public Entity
{	
	
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
};

