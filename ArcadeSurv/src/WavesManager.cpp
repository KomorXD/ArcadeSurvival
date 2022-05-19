#include "WavesManager.hpp"
#include "Scenes/GameScene.hpp"
#include "Utils/Random.hpp"

WavesManager::WavesManager(GameScene* scene)
	: m_Scene(scene), m_WaveBar(&m_EnemiesLeft, { 1280.0f, 16.0f }, { 10.0f, 65.0f })
{
	for(int32_t i = 0; i < 10; ++i)
		m_Scene->SpawnEnemy({ Random::Get().FloatInRange(-1000.0f, 1000.0f), Random::Get().FloatInRange(-1000.0f, 1000.0f) },
							  sf::Color::Green, 10.0f, 100.0f);

	m_WaveBar.SetColor(sf::Color::Cyan);
}

void WavesManager::Update(float dt)
{
	m_WaveBar.Update(m_WaveNo * 10.0f);
}

void WavesManager::NextWave()
{}
