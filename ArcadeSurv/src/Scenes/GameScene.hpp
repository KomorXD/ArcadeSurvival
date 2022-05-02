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
		virtual ~GameScene();

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

		void SpawnBullet(const sf::Vector2f& dir, const sf::Vector2f& pos, float velocity, float strength);

	private:
		void CheckForPlayerCollisions(float dt);
		void CheckForPlayerOutsideOfArena();
		void CheckForEnemiesShot();
		void CheckForBulletsToDespawn();
		void CheckForEnemiesToDespawn();
		void CheckForEffectsToDespawn();

		std::unique_ptr<PlayerEntity> m_Player;

		std::vector<EnemyEntity>  m_Enemies;
		std::vector<BulletEntity> m_Bullets;
		std::vector<EffectEntity> m_EffectHolders;

		sf::RectangleShape m_Floor;
		sf::Sprite		   m_Skybox;

		sf::Sound m_Ambient;
		sf::Sound m_PickupSound;
		sf::Sound m_EnemyDeathSound;

		sf::Clock m_Clock;
		sf::Text  m_TimeAliveText;
};