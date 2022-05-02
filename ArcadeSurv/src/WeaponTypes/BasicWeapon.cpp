#include "BasicWeapon.hpp"
#include "../Scenes/GameScene.hpp"

void BasicWeapon::Shoot(GameScene* scene, const sf::Vector2f& dir, const sf::Vector2f& origin, float dmgMult)
{
	scene->SpawnBullet(dir, origin, 500.0f, 20.0f * dmgMult);
}
