#include "EffectEntity.hpp"
#include "PlayerEntity.hpp"
#include "../Utils/Resources.hpp"

EffectEntity::EffectEntity(EffectType effectType, float duration, float entityLifespan, const sf::Vector2f& pos)
	: Entity(pos), m_Lifespan(entityLifespan)
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

		case EffectType::HEAL:
			m_StoredEffect = std::make_unique<HealEffect>(0.0f, nullptr);
			SetTexture(Resources::Get().GetTexture("effect_heal"));

			break;

		case EffectType::NO_WEAPON:
			m_StoredEffect = std::make_unique<NoWeaponEffect>(duration, Resources::Get().GetTexture("effect_no_weapon"));
			SetTexture(Resources::Get().GetTexture("effect_no_weapon"));

			break;

		case EffectType::SPREAD_WEAPON:
			m_StoredEffect = std::make_unique<SpreadWeaponEffect>(-1.0f, Resources::Get().GetTexture("effect_spread_weapon"));
			SetTexture(Resources::Get().GetTexture("effect_spread_weapon"));

			break;

		case EffectType::EXPLOSIVE_WEAPON:
			m_StoredEffect = std::make_unique<ExplosiveWeaponEffect>(-1.0f, Resources::Get().GetTexture("effect_explosive_weapon"));
			SetTexture(Resources::Get().GetTexture("effect_explosive_weapon"));

			break;

		default:
			break;
	}

	m_Body.setPosition(pos);
}

EffectEntity::EffectEntity(EffectEntity&& other) noexcept
	: Entity(other.m_Body.getSize())
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
