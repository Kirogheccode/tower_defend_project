#include "tower.h"
#include "Entity.h"
#include "MathSupport.h"
#include "Bullet.h"
#include <vector>

Tower::Tower(float x, float y, const sf::Texture& texture, int cost, int damage, float range, float timeToFire) 
	:Entity(PhysicsData::Type::Static)
{
	SetCirclePhysics(20.0f);
	SetPosition({ x,y });
	SetTexture(texture);
	SetScale({ 0.5f,0.5f });
	SetOrigin({ 10.0f,10.0f });
	m_iCost = cost;
	m_iDamage = damage;
	m_fRange = range;
	m_fTimeToFire = timeToFire;
}

void Tower::Attack(sf::Time deltaTime, std::vector<Enemy> vEnemySeq, std::vector<Bullet> vBulletSeq)
{
	//shooting time 
	m_fTimeToFire -= deltaTime.asSeconds();

	if (m_fTimeToFire > 0)
	return;

	float fNearestDistance = std::numeric_limits<float>::max();
	sf::Vector2f vTowerToEnemy;

	// Find the nearest enemy within range
	for (Entity& enemy : vEnemySeq)
	{
		sf::Vector2f vTowerToEnemy = enemy.GetPosition() - (*this).GetPosition();
		float fDistance = MathSupport::Length(vTowerToEnemy);
		if (fDistance < fNearestDistance)
		{
			fNearestDistance = fDistance;
			pNearestEnemy = &enemy;
		}
	}

	//no enemies in range -> return
	if (pNearestEnemy == nullptr || fNearestDistance > m_fRange)
	return;

	// Create an axe and set its velocity
	Entity& readyBullet = vBulletSeq.emplace_back();
	readyBullet.SetPosition((*this).GetPosition());
	vTowerToEnemy = MathSupport::Normalize(vTowerToEnemy);
	readyBullet.SetVelocity(vTowerToEnemy * 500.0f);

	// Reset their axe throwing timer
	(*this).m_fTimeToFire = 1.0f;
}


