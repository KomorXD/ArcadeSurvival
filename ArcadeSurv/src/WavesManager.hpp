#pragma once

#include "UI/ResourceBar.hpp"

#include <memory>

class GameScene;
class PlayerEntity;

class WavesManager
{
	public:
		static constexpr int32_t MAX_WAVES = 10;

		WavesManager(GameScene* scene, std::shared_ptr<PlayerEntity>& playerPtr);
		~WavesManager() = default;

		void Update(float dt);
		void NextWave();
		void OnEnemyKilled();

		void Render(sf::RenderTarget& renderer);

		inline int32_t EnemiesLeft() const { return m_EnemiesLeft; }
		inline bool WaveOver() const { return m_EnemiesLeft == 0; }

	private:
		void SpawnEnemiesOnWave();
		void TryToSpawnPowerUp();
		void TryToSpawnWeapon();

		int32_t m_CurrWaveEnemiesSpawned = 30;
		int32_t m_EnemiesLeft			 = 30;
		int32_t m_WaveNo				 = 1;

		ResourceBar m_WaveBar;

		GameScene* m_Scene;
		std::shared_ptr<PlayerEntity> m_PlayerPtr;
};