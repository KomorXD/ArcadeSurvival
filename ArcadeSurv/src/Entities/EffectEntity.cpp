#include "EffectEntity.hpp"
#include "PlayerEntity.hpp"
#include "../Utils/Resources.hpp"
#include "../Effects/Effects.hpp"

EffectEntity::EffectEntity(GameScene* scene, const sf::Vector2f& pos, EffectType effectType, float duration, float entityLifespan)
	: Entity(scene, 50.0f), m_Lifespan(entityLifespan)
{
	switch(effectType)
	{
		case EffectType::HASTE:
			m_StoredEffect = std::make_unique<HasteEffect>(duration, Resources::Get().GetTexture("effect_haste"));
			SetTexture(Resources::Get().GetTexture("effect_haste"));
			
			break;

		case EffectType::CRIPPLE:
			m_StoredEffect = std::make_unique<CrippleEffect>(duration, Resources::Get().GetTexture("effect_cripple"));
			SetTexture(Resources::Get().GetTexture("effect_cripple"));
			
			break;
			
		case EffectType::QUAD:
			m_StoredEffect = std::make_unique<QuadDmgEffect>(duration, Resources::Get().GetTexture("effect_quad"));
			SetTexture(Resources::Get().GetTexture("effect_quad"));

			break;

		default:
			break;
	}

	m_Body.setPosition(pos);

	SetMovementSpeed(0.0f);
}

EffectEntity::EffectEntity(EffectEntity&& other) noexcept
	: Entity(other.m_Scene, other.m_MovementSpeed)
{
	*this = std::move(other);
}

EffectEntity& EffectEntity::operator=(EffectEntity&& other) noexcept
{
	if(this == &other)
		return *this;

	m_StoredEffect = std::move(other.m_StoredEffect);
	m_Body		   = std::move(other.m_Body);
	m_Lifespan	   = std::move(other.m_Lifespan);

	return *this;
}

void EffectEntity::Update(float dt)
{
	m_Lifespan = std::max(m_Lifespan - dt, 0.0f);
}

void EffectEntity::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
}

void EffectEntity::OnPlayerIntersect(PlayerEntity* player)
{
	player->ApplyEffect(std::move(m_StoredEffect));
	m_Lifespan = 0.0f;
}
