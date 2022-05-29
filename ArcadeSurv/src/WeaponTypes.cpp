#include "WeaponTypes.hpp"
#include "Scenes/GameScene.hpp"

void BasicWeapon::Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult)
{
	BulletEntity bullet(origin);

	bullet.SetVelocityVector(dir);
	bullet.SetStrength(20.0f * dmgMult);
	bullet.SetTravelSpeed(1000.0f);
	bullet.SetSize({ 16.0f, 16.0f });

	if(dmgMult > 1.0f)
		bullet.SetColor({ 168, 71, 237 });
	else
		bullet.SetColor({ 54, 215, 247 });

	scene->SpawnBullet(bullet);
}

static constexpr float TAU = 6.283185307179586f;

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
	BulletEntity prototype(origin);

	prototype.SetStrength(20.0f * dmgMult);
	prototype.SetTravelSpeed(1000.0f);
	prototype.SetSize({ 16.0f, 16.0f });

	if(dmgMult > 1.0f)
		prototype.SetColor({ 168, 71, 237 });
	else
		prototype.SetColor({ 54, 215, 247 });

	for(auto& direction : m_Directions)
	{
		prototype.SetVelocityVector({ direction.x, direction.y });
		scene->SpawnBullet(prototype);
	}
}

void ExplosiveWeapon::Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult)
{
	BulletEntity prototype(origin);

	prototype.SetVelocityVector(dir);
	prototype.SetStrength(30.0f * dmgMult);
	prototype.SetTravelSpeed(1000.0f);
	prototype.SetSize({ 16.0f, 16.0f });

	if(dmgMult > 1.0f)
		prototype.SetColor({ 252, 3, 48 });
	else
		prototype.SetColor({ 255, 111, 0 });

	scene->SpawnBullet(prototype);
}

void NoWeapon::Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult)
{
	;
}
