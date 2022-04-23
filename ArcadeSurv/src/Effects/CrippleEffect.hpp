#pragma once

#include "Effect.hpp"

class CrippleEffect : public Effect
{
	public:
		CrippleEffect(float time, sf::Texture* icon);
		virtual ~CrippleEffect();

		virtual void BindEffect(PlayerEntity* player) override;
};