#include "Enitity.hpp"

Entity::Entity(float size)
	: m_Body({ size, size * 2.0f }), m_MovementSpeed(100.0f)
{ }

void Entity::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
}

void Entity::SetTexture(sf::Texture* texture)
{
	m_Body.setTexture(texture);
}

void Entity::SetPosition(const sf::Vector2f& pos)
{
	m_Body.setPosition(pos);
}

void Entity::SetMovementSpeed(float ms)
{
	m_MovementSpeed = ms;
}
