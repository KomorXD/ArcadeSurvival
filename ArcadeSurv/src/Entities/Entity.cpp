#include "Enitity.hpp"

Entity::Entity(GameScene* scene, float size)
	: m_Scene(scene), m_Body({ size, size }), m_MovementSpeed(100.0f)
{
#ifdef AS_DEBUG
	m_Body.setOutlineThickness(1.0f);
	m_Body.setOutlineColor(sf::Color::Red);
#endif
	m_Body.setOrigin({ size / 2.0f, size / 2.0f });
}

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
