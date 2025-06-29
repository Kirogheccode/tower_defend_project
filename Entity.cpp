#include "Entity.h"

Entity::Entity(const string& tag, const size_t& id)
{
	m_tag = tag;
	m_id = id;
}

bool Entity::isActive() const
{
	return m_active;
}

const string& Entity::tag() const
{
	return m_tag;
}

const size_t& Entity::id() const
{
	return m_id;
}

void Entity::active(const bool& A)
{
	m_active = A;
}

void Entity::destroy()
{
	m_active = false;
}


sf::Vector2f Entity::GetPosition()
{
	return cPosition->position;
}

sf::Texture Entity::GetTexture()
{
	return cSet->texture;
}

sf::FloatRect Entity::GetRect()
{
	return (cBound->rect);
}

float Entity::GetRadius()
{
	return cBound->radius;
}


//bool Entity::OnCollision(Entity& bullet, Entity& enemy)
//{
//	if (bullet.tag().find("Bullet") == std::string::npos) //not a bullet
//		return false;
//
//	// find the clostest point on the rectangle to the circle (limited by the rectangle edges)
//	float fClosestX = std::clamp(GetPosition(bullet).x, GetPosition(bullet).x - GetRect(enemy).width / 2, GetPosition(enemy).x + GetRect(enemy).width / 2);
//	float fClosestY = std::clamp(GetPosition(bullet).y, GetPosition(bullet).y - GetRect(enemy).height / 2, GetPosition(enemy).y + GetRect(enemy).height / 2);
//
//	sf::Vector2f vClosestPoint(fClosestX, fClosestY);
//	sf::Vector2f vCircleToClosestPoint = vClosestPoint - GetPosition(bullet);
//
//	float fDistance = MathSupport::Length(vCircleToClosestPoint);
//
//	// in case of collision
//	if (fDistance < GetRadius(bullet))
//	{
//		bullet.m_active = false;
//		SetHp(enemy, enemy.cHealth->hp - bullet.cDamage->damage); // reduce the enemy health
//		if (enemy.cHealth->hp <= 0)
//		{
//			enemy.m_active = false; // deactivate the enemy if health is zero or less
//		}
//	}
//}

void Entity::MotionProcess(Entity& entity, sf::Vector2f tour)
{
	entity.cSet->sprite.move(tour);
}

bool Entity::ReadyShoot()
{

	if (cCooldown->shootClock.getElapsedTime() < cCooldown->cooldownDuration)
	{
		return false;
	}

	// All checks passed, the tower is ready to shoot!
	return true;
}

