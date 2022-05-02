#pragma once

class GameScene;

#include <SFML/System/Vector2.hpp>

class Weapon
{
	public:
		virtual void Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult) = 0;
};