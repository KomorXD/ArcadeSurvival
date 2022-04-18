#pragma once

#include "Effect.hpp"

class QuadDmgEffect : public Effect
{
	public:
		QuadDmgEffect(float time, sf::Texture* icon);
		virtual ~QuadDmgEffect();

		virtual void BindEffect(PlayerEntity* player) override;
};