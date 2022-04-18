#pragma once

#include "Scene.hpp"
#include "../Entities/PlayerEntity.hpp"
#include "../Entities/BulletEntity.hpp"
#include "../Entities/EnemyEntity.hpp"
#include "../Entities/EffectEntity.hpp"

#include <vector>

class GameScene : public Scene
{
	public:
		GameScene();
		virtual ~GameScene() = default;

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

		void SpawnBullet(const sf::Vector2f& dir, const sf::Vector2f& pos, float velocity, float strength);

	private:
		void CheckForPlayerCollisions(float dt);
		void CheckForEnemiesShot();
		void CheckForBulletsToDespawn();
		void CheckForEnemiesToDespawn();
		void CheckForEffectsToDespawn();

		PlayerEntity m_Player;

		std::vector<EnemyEntity>  m_Enemies;
		std::vector<BulletEntity> m_Bullets;
		std::vector<EffectEntity> m_EffectHolders;
};