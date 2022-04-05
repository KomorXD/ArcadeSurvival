#include "EnemyEntity.hpp"
#include "PlayerEntity.hpp"

EnemyEntity::EnemyEntity(PlayerEntity* playerPtr)
	: Entity(50.0f), m_PlayerPtr(playerPtr)
{}

void EnemyEntity::Update(float dt)
{
	sf::Vector2f wishDir = m_PlayerPtr->GetPosition() - m_Body.getPosition();

	float len = std::sqrtf(wishDir.x * wishDir.x + wishDir.y * wishDir.y);

	if(len != 0.0f)
		wishDir /= len;

	m_Body.move(wishDir * m_MovementSpeed * dt);
}

void EnemyEntity::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
}
