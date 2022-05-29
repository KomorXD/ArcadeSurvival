#include "WavesManager.hpp"
#include "Scenes/GameScene.hpp"
#include "Utils/Random.hpp"

static float Distance(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
	return std::sqrtf(std::powf(vec1.x - vec2.x, 2) + std::powf(vec1.y - vec2.y, 2));
}

WavesManager::WavesManager(GameScene* scene, std::shared_ptr<PlayerEntity>& playerPtr)
	: m_Scene(scene), m_PlayerPtr(playerPtr), m_WaveBar(&m_EnemiesLeft, { 1260.0f, 16.0f }, { 10.0f, 65.0f })
{
	m_WaveBar.SetColor(sf::Color::Cyan);

	SpawnEnemiesOnWave();
}

void WavesManager::Update(float dt)
{
	m_WaveBar.Update(static_cast<float>(m_CurrWaveEnemiesSpawned));

	TryToSpawnPowerUp();
	TryToSpawnWeapon();
}

void WavesManager::NextWave()
{
	++m_WaveNo;
	m_EnemiesLeft = m_WaveNo * 30;
	m_CurrWaveEnemiesSpawned = m_EnemiesLeft;

	SpawnEnemiesOnWave();
}

void WavesManager::OnEnemyKilled()
{
	--m_EnemiesLeft;
}

void WavesManager::Render(sf::RenderTarget& renderer)
{
	m_WaveBar.draw(renderer, sf::RenderStates::Default);
}

void WavesManager::SpawnEnemiesOnWave()
{
	sf::Vector2f playerPos = m_PlayerPtr->GetPosition();

	for(int32_t i = 0; i < m_WaveNo * 30; ++i)
	{
		sf::Vector2f randomizedSpawnPosition = { Random::Get().FloatInRange(-4500.0f, 4500.0f), Random::Get().FloatInRange(-4500.0f, 4500.0f) };
		float dist = Distance(playerPos, randomizedSpawnPosition);

		if(dist < 500.0f || dist > 3000.0f)
		{
			--i;
			continue;
		}

		m_Scene->SpawnEnemy(randomizedSpawnPosition, sf::Color::Green, 10.0f, 100.0f);
	}
}

void WavesManager::TryToSpawnPowerUp()
{
	if(Random::Get().FloatInRange(0.0f, 100.0f) > 0.1f * m_WaveNo)
		return;
	
	sf::Vector2f playerPos = m_PlayerPtr->GetPosition();
	EffectType   type = static_cast<EffectType>(Random::Get().IntInRange(1, 5));
	sf::Vector2f effectPos(0.0f, 0.0f);
	float dist = 0.0f;
	
	do
	{
		effectPos = { Random::Get().FloatInRange(playerPos.x - 500.0f, playerPos.x + 500.0f), Random::Get().FloatInRange(playerPos.y - 500.0f, playerPos.y + 500.0f) };
		dist = Distance(effectPos, playerPos);
	} while(dist < 200.0f || (effectPos.x < -4500.0f || effectPos.x > 4500.0f) && (effectPos.y < -4500.0f || effectPos.y > 4500.0f));

	EffectEntity eff(type, 10.0f, 20.0f, effectPos);

	eff.SetSize({ 48.0f, 48.0f });
	m_Scene->SpawnPowerUp(std::move(eff));
}

void WavesManager::TryToSpawnWeapon()
{
	if(Random::Get().FloatInRange(0.0f, 100.0f) > 0.05f * m_WaveNo)
		return;

	sf::Vector2f playerPos = m_PlayerPtr->GetPosition();
	EffectType   type = static_cast<EffectType>(Random::Get().IntInRange(6, 7));
	sf::Vector2f effectPos(0.0f, 0.0f);
	float dist = 0.0f;

	do
	{
		effectPos = { Random::Get().FloatInRange(playerPos.x - 500.0f, playerPos.x + 500.0f), Random::Get().FloatInRange(playerPos.y - 500.0f, playerPos.y + 500.0f) };
		dist = Distance(effectPos, playerPos);
	} while((effectPos.x < -4500.0f || effectPos.x > 4500.0f) && (effectPos.y < -4500.0f || effectPos.y > 4500.0f));

	EffectEntity eff(type, 10.0f, 20.0f, effectPos);

	eff.SetSize({ 48.0f, 48.0f });
	m_Scene->SpawnPowerUp(std::move(eff));
}
