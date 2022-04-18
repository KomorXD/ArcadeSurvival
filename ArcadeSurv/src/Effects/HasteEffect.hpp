#pragma once

#include "Effect.hpp"

class HasteEffect : public Effect
{
	public:
		HasteEffect(float time, sf::Texture* icon);
		virtual ~HasteEffect();

		virtual void BindEffect(PlayerEntity* player) override;
};