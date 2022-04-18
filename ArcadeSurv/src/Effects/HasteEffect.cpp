#include "HasteEffect.hpp"
#include "../Entities/PlayerEntity.hpp"

HasteEffect::HasteEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::HASTE;
}

HasteEffect::~HasteEffect()
{
	if(m_AffectedPlayer)
	{
		m_AffectedPlayer->SetSpeedMultiplier(1.0f);
		m_AffectedPlayer->SetFireRateMultiplier(1.0f);
	}
}

void HasteEffect::BindEffect(PlayerEntity* player)
{
	m_AffectedPlayer = player;
	m_AffectedPlayer->SetSpeedMultiplier(2.0f);
	m_AffectedPlayer->SetFireRateMultiplier(2.0f);
}
