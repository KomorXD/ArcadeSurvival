#include "QuadDmgEffect.hpp"
#include "../Entities/PlayerEntity.hpp"

QuadDmgEffect::QuadDmgEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::QUAD;
}

QuadDmgEffect::~QuadDmgEffect()
{
	if(m_AffectedPlayer)
		m_AffectedPlayer->SetDamageMultiplier(1.0f);
}

void QuadDmgEffect::BindEffect(PlayerEntity * player)
{
	m_AffectedPlayer = player;
	m_AffectedPlayer->SetDamageMultiplier(4.0f);
}
