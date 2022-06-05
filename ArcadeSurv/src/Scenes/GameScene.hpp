#pragma once

#include "Scene.hpp"
#include "../WavesManager.hpp"
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

		void SpawnBullet(BulletEntity bullet);
		void SpawnEnemy(EnemyEntity enemy);
		void SpawnPowerUp(EffectEntity&& effect);
		void SpawnEnemy(const sf::Vector2f& pos, const sf::Color& color, float strength, float movementSpeed);
		void DealDamageInArea(const sf::Vector2f& center, float radius, int32_t damage);
		void ClearEffectEntities();

	private:
		void CheckForPlayerCollisions();
		void CheckForPlayerOutsideOfArena();
		void CheckForEnemiesShot();
		void CheckForBulletsToDespawn();
		void CheckForEnemiesToDespawn();
		void CheckForEffectsToDespawn();

		std::shared_ptr<PlayerEntity> m_Player;

		std::unique_ptr<WavesManager> m_WaveMan;

		std::vector<EnemyEntity>  m_Enemies;
		std::vector<BulletEntity> m_Bullets;
		std::vector<EffectEntity> m_EffectHolders;

		sf::RectangleShape m_Floor;
		sf::Sprite		   m_Skybox;

		sf::Sound m_Ambient;
		sf::Sound m_PickupSound;
		sf::Sound m_EnemyDeathSound;

		float	 m_TimeAlive;
		sf::Text m_TimeAliveText;

		std::shared_ptr<sf::RenderTexture> m_SnapshotRenderTexture;

		float m_DeltaTime = 1.0f / 60.0f;
};