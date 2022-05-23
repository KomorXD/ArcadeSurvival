#include "HealEffect.hpp"
#include "../Entities/PlayerEntity.hpp"

HealEffect::HealEffect(float time, sf::Texture* icon)
	: Effect(time, icon)
{
	m_Type = EffectType::HEAL;
}

void HealEffect::BindEffect(PlayerEntity* player)
{
	player->Heal(20);
}
