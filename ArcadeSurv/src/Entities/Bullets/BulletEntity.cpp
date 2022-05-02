#include "BulletEntity.hpp"

BulletEntity::BulletEntity(const sf::Vector2f& pos)
	: Entity(pos)
{
	;
}

void BulletEntity::Update(float dt)
{
	m_Body.move(m_TravelDir * m_TravelSpeed * dt);
}

void BulletEntity::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
}

void BulletEntity::SetTravelSpeed(float ts)
{
	m_TravelSpeed = ts;
}

void BulletEntity::SetStrength(float strength)
{
	m_Strength = strength;
}

void BulletEntity::SetVelocityVector(const sf::Vector2f& velVec)
{
	m_TravelDir = velVec;
}
