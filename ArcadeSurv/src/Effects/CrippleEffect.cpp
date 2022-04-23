#include "CrippleEffect.hpp"
#include "../Entities/PlayerEntity.hpp"

CrippleEffect::CrippleEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type		   = EffectType::CRIPPLE;
	m_OppositeType = EffectType::HASTE;
}

CrippleEffect::~CrippleEffect()
{
	if(m_AffectedPlayer)
	{
		m_AffectedPlayer->SetSpeedMultiplier(1.0f);
		m_AffectedPlayer->SetFireRateMultiplier(1.0f);
	}
}

void CrippleEffect::BindEffect(PlayerEntity* player)
{
	m_AffectedPlayer = player;
	m_AffectedPlayer->SetSpeedMultiplier(0.5f);
	m_AffectedPlayer->SetFireRateMultiplier(0.5f);
}
