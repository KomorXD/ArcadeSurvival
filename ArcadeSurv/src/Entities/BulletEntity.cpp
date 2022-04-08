#include "BulletEntity.hpp"

BulletEntity::BulletEntity(const sf::Vector2f& dir, float travelSpeed)
	: Entity(10.0f), m_TravelDir(dir)
{
	m_MovementSpeed = travelSpeed;
	
	m_Body.setFillColor(sf::Color::Red);
}

void BulletEntity::Update(float dt)
{
	m_Body.move(m_TravelDir * m_MovementSpeed * dt);
}

void BulletEntity::Render(sf::RenderTarget & renderer)
{
	renderer.draw(m_Body);
}
