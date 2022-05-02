#pragma once

#include "Weapon.hpp"

class BasicWeapon : public Weapon
{
	public:
		virtual void Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult) override;
};