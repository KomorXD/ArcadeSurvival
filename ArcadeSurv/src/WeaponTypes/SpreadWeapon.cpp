#include "SpreadWeapon.hpp"
#include "../Scenes/GameScene.hpp"

constexpr float TAU = 6.283185307179586f;

const std::array<sf::Vector2f, 8> SpreadWeapon::m_Directions{
	sf::Vector2f(std::cosf(0.0f * TAU / 8.0f), std::sinf(0.0f * TAU / 8.0f)),
	sf::Vector2f(std::cosf(1.0f * TAU / 8.0f), std::sinf(1.0f * TAU / 8.0f)),
	sf::Vector2f(std::cosf(2.0f * TAU / 8.0f), std::sinf(2.0f * TAU / 8.0f)),
	sf::Vector2f(std::cosf(3.0f * TAU / 8.0f), std::sinf(3.0f * TAU / 8.0f)),
	sf::Vector2f(std::cosf(4.0f * TAU / 8.0f), std::sinf(4.0f * TAU / 8.0f)),
	sf::Vector2f(std::cosf(5.0f * TAU / 8.0f), std::sinf(5.0f * TAU / 8.0f)),
	sf::Vector2f(std::cosf(6.0f * TAU / 8.0f), std::sinf(6.0f * TAU / 8.0f)),
	sf::Vector2f(std::cosf(7.0f * TAU / 8.0f), std::sinf(7.0f * TAU / 8.0f))
};

void SpreadWeapon::Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult)
{
	for(auto& direction : m_Directions)
		scene->SpawnBullet(direction, origin, 500.0f, 20.0f * dmgMult);
}
