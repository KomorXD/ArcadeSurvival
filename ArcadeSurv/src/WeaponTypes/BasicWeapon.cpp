#include "BasicWeapon.hpp"
#include "../Scenes/GameScene.hpp"

void BasicWeapon::Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult)
{
	BulletEntity bullet(origin);

	bullet.SetVelocityVector(dir);
	bullet.SetStrength(20.0f * dmgMult);
	bullet.SetTravelSpeed(500.0f);
	bullet.SetSize({ 16.0f, 16.0f });

	if(dmgMult > 1.0f)
		bullet.SetColor({ 168, 71, 237 });
	else
		bullet.SetColor({ 54, 215, 247 });

	scene->SpawnBullet(bullet);
}
