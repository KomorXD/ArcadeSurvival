#include "BulletEntity.hpp"

BulletEntity::BulletEntity(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& pos, float travelSpeed, float strength)
	: Entity(scene, 10.0f), m_TravelDir(dir), m_Strength(strength)
{
	m_MovementSpeed = travelSpeed;
	
	m_Body.setPosition(pos);
}

void BulletEntity::Update(float dt)
{
	m_Body.move(m_TravelDir * m_MovementSpeed * dt);
}

void BulletEntity::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
}