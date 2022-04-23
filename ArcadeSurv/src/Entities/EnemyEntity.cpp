#include "EnemyEntity.hpp"
#include "PlayerEntity.hpp"

EnemyEntity::EnemyEntity(GameScene* scene, PlayerEntity* playerPtr)
	: Entity(scene, 64.0f), m_PlayerPtr(playerPtr)
{
	m_Body.setTextureRect({ 0, 0, 32, 32 });
	m_Body.setFillColor({ 0, 255, 0});
}

void EnemyEntity::Update(float dt)
{
	sf::Vector2f wishDir = m_PlayerPtr->GetPosition() - m_Body.getPosition();

	float len = std::sqrtf(wishDir.x * wishDir.x + wishDir.y * wishDir.y);
	
	if(len != 0.0f)
		wishDir /= len;
	
	m_Body.move(wishDir * m_MovementSpeed * dt);
	
	m_AnimationFrames = std::max(m_AnimationFrames - 1, 0);

	if(m_AnimationFrames == 0)
	{
		int32_t texRectX = m_Body.getTextureRect().left;

		m_AnimationFrames = static_cast<int32_t>(0.5f / dt);
		m_Body.setTextureRect({ 32 - texRectX, 0, 32, 32 });
	}
}

void EnemyEntity::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
}

void EnemyEntity::OnDamage(int32_t damage)
{
	m_HP = std::max(0, m_HP - damage);
}
