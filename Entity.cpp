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

void Entity::destroy()
{
	//
}