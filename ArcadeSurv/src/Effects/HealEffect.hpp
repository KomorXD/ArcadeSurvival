#pragma once

#include "Effect.hpp"

class HealEffect : public Effect
{
	public:
		HealEffect(float time, sf::Texture* icon);
		virtual ~HealEffect() = default;

		virtual void BindEffect(PlayerEntity* player) override;
};