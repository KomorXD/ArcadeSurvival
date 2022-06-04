#include "Enitity.hpp"

Entity::Entity(const sf::Vector2f& pos)
{
#ifdef AS_DEBUG
	m_Body.setOutlineThickness(1.0f);
	m_Body.setOutlineColor(sf::Color::Red);
#endif
	m_Body.setPosition(pos);
	m_Body.setSize({ 64.0f, 64.0f });
	m_Body.setOrigin({ 32.0f, 32.0f });
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

void Entity::SetSize(const sf::Vector2f& size)
{
	m_Body.setSize(size);
	m_Body.setOrigin({ size.x / 2.0f, size.y / 2.0f });
}

void Entity::SetColor(const sf::Color& color)
{
	m_Body.setFillColor(color);
}

void Entity::SetTextureRect(const sf::IntRect& rect)
{
	m_Body.setTextureRect(rect);
}
