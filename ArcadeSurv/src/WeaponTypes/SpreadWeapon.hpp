#pragma once

#include "Weapon.hpp"

#include <array>

class SpreadWeapon : public Weapon
{
	public:
		virtual void Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult) override;

	private:
		static const std::array<sf::Vector2f, 8> m_Directions;
};