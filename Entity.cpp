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

Vector2f Entity::GetPosition()
{
	return cPosition->position;
}

Texture Entity::GetTexture()
{
	return cSet->texture;
}

FloatRect Entity::GetRect()
{
	return (cBound->rect);
}

float Entity::GetRadius()
{
	return cBound->radius;
}

void Entity::MotionProcess(Entity& entity, Vector2f tour)
{
	entity.cSet->sprite.move(tour);
}

bool Entity::ReadyShoot()
{

	if (cCooldown->shootClock.getElapsedTime() < cCooldown->cooldownDuration)
	{
		return false;
	}

	return true;
}