#pragma once

class GameScene;

#include <SFML/System/Vector2.hpp>
#include <array>

class Weapon
{
	public:
		virtual void Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult) = 0;
};

class BasicWeapon : public Weapon
{
	public:
		virtual void Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult) override;
};

class SpreadWeapon : public Weapon
{
	public:
		virtual void Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult) override;

	private:
		static const std::array<sf::Vector2f, 8> m_Directions;
};

class ExplosiveWeapon : public Weapon
{
	public:
		virtual void Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult) override;
};

class NoWeapon : public Weapon
{
	public:
		virtual void Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult) override;
};