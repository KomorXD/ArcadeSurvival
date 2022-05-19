#pragma once

#include "UI/ResourceBar.hpp"

class GameScene;

class WavesManager
{
	public:
		static const int32_t MAX_WAVES = 10;

		WavesManager(GameScene* scene);
		~WavesManager() = default;

		void Update(float dt);
		void NextWave();

		inline int32_t EnemiesLeft() const { return m_EnemiesLeft; }
		inline bool WaveOver() const { return m_EnemiesLeft == 0; }

	private:
		int32_t m_EnemiesLeft = 0;
		int32_t m_WaveNo	  = 1;

		ResourceBar m_WaveBar;

		GameScene* m_Scene;
};