#include "EnemyEntity.hpp"
#include "PlayerEntity.hpp"

EnemyEntity::EnemyEntity(PlayerEntity* playerPtr, const sf::Vector2f& pos)
	: Entity(pos), m_PlayerPtr(playerPtr)
{
	m_Body.setTextureRect({ 0, 0, 32, 32 });
	m_Body.setFillColor({ 0, 255, 0});
}

void EnemyEntity::Update(float dt)
{
	if(m_HP == 0)
	{
		if(m_DyingAnimationFrames == 0)
		{
			m_DyingAnimationFrames = m_AnimationFrames = static_cast<int32_t>(0.5f / dt);
			m_AnimationFrames	   = m_AnimationFrames = static_cast<int32_t>(0.5f / dt);
		}
		
		DyingUpdate(dt);

		return;
	}

	sf::Vector2f wishDir = m_PlayerPtr->GetPosition() - m_Body.getPosition();

	float len = std::sqrtf(wishDir.x * wishDir.x + wishDir.y * wishDir.y);
	
	if(len != 0.0f)
		wishDir /= len;
	
	m_Body.move(wishDir * m_MovementSpeed * dt);
	
	m_AnimationFrames = std::max(m_AnimationFrames - 1, 0);
	m_DamageTakenFrames = std::max(m_DamageTakenFrames - 1, 0);

	if(m_AnimationFrames == 0)
	{
		sf::IntRect texRect = m_Body.getTextureRect();

		m_AnimationFrames = static_cast<int32_t>(0.5f / dt);
		m_Body.setTextureRect({ 32 - texRect.left, 0, 32, 32 });
	}

	if(m_DamageTakenFrames == 0 && m_Body.getFillColor() == sf::Color::Red)
		m_Body.setFillColor(m_NormalColor);
}

void EnemyEntity::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
}

void EnemyEntity::OnDamage(int32_t damage, float dt)
{
	m_HP = std::max(0, m_HP - damage);
	m_DamageTakenFrames = static_cast<int32_t>(0.1f / dt);
	m_Body.setFillColor(sf::Color::Red);
}

void EnemyEntity::SetMovementSpeed(float ms)
{
	m_MovementSpeed = ms;
}

void EnemyEntity::SetStrength(float strength)
{
	m_Strength = strength;
}

void EnemyEntity::SetPlayerPtr(PlayerEntity* ptr)
{
	m_PlayerPtr = ptr;
}

void EnemyEntity::SetColor(const sf::Color& color)
{
	m_Body.setFillColor(color);
	m_NormalColor = color;
}

void EnemyEntity::DyingUpdate(float dt)
{
	m_AnimationFrames = std::max(m_AnimationFrames - 1, 0);

	int32_t left = m_AnimationFrames < m_DyingAnimationFrames / 2 ? 32 : 0;
	
	m_Body.setTextureRect({ left, 32, 32, 32 });
}
