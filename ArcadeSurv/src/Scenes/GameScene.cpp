#include "GameScene.hpp"
#include "../Application.hpp"
#include "../Utils/Resources.hpp"
#include "../Effects/Effects.hpp"
#include "../Utils/Random.hpp"

#include <future>

static void LoadResources()
{
	Resources& res = Resources::Get();

	res.LoadTexture("player_atlas");
	res.LoadTexture("enemy_atlas");
	res.LoadTexture("basic_bullet");
	res.LoadTexture("effect_haste");
	res.LoadTexture("effect_cripple");
	res.LoadTexture("effect_quad");
	res.LoadTexture("floor");

	res.LoadSoundBuffer("shoot");
	res.LoadSoundBuffer("ambient");
	res.LoadSoundBuffer("effect_pickup");
	res.LoadSoundBuffer("enemy_death");
}

GameScene::GameScene()
	: m_Floor({ 5000.0f, 5000.0f })
{
	LoadResources();

	m_Player = std::make_unique<PlayerEntity>(this);

	m_Player->SetPosition({ 640.0f, 360.0f });
	m_Player->SetMovementSpeed(200.0f);

	if(sf::Texture* tex = Resources::Get().GetTexture("player_atlas"))
		m_Player->SetTexture(tex);

	m_Floor.setOrigin({ 2500.0f, 2500.0f });
	m_Floor.setPosition({ 640.0f, 360.0f });

	if(sf::Texture* floorText = Resources::Get().GetTexture("floor"))
	{
		floorText->setRepeated(true);
		m_Floor.setTexture(floorText);
		m_Floor.setTextureRect({ 0, 0, 2500, 2500 });
	}

	EnemyEntity prototype(this, m_Player.get());
	
	if(sf::Texture* tex = Resources::Get().GetTexture("enemy_atlas"))
		prototype.SetTexture(tex);

	prototype.SetMovementSpeed(100.0f);

	for(uint32_t i = 0; i < 10; ++i)
	{
		prototype.SetPosition({ Random::Get().FloatInRange(-1000.0f, 1000.0f), Random::Get().FloatInRange(-1000.0f, 1000.0f) });
		m_Enemies.push_back(prototype);
	}

	m_EffectHolders.emplace_back(this, sf::Vector2f(200.0f, 200.0f), EffectType::HASTE,	  10.0f, 100.0f);
	m_EffectHolders.emplace_back(this, sf::Vector2f(100.0f, 600.0f), EffectType::QUAD,	  10.0f, 100.0f);
	m_EffectHolders.emplace_back(this, sf::Vector2f(700.0f, 200.0f), EffectType::CRIPPLE, 10.0f, 100.0f);

	if(sf::SoundBuffer* sb = Resources::Get().GetSoundBuffer("ambient"))
	{
		m_Ambient.setBuffer(*sb);
		m_Ambient.setLoop(true);
		m_Ambient.setVolume(2.0f);
		m_Ambient.play();
	}

	if(sf::SoundBuffer* sb = Resources::Get().GetSoundBuffer("effect_pickup"))
	{
		m_PickupSound.setBuffer(*sb);
		m_PickupSound.setVolume(40.0f);
	}

	if(sf::SoundBuffer* sb = Resources::Get().GetSoundBuffer("enemy_death"))
	{
		m_EnemyDeathSound.setBuffer(*sb);
		m_EnemyDeathSound.setVolume(20.0f);
	}
}

GameScene::~GameScene()
{
	Resources& res = Resources::Get();

	res.DeleteTexture("player_atlas");
	res.DeleteTexture("enemy_atlas");
	res.DeleteTexture("basic_bullet");
	res.DeleteTexture("effect_haste");
	res.DeleteTexture("effect_cripple");
	res.DeleteTexture("effect_quad");
	res.DeleteTexture("floor");

	res.DeleteSoundBuffer("shoot");
	res.DeleteSoundBuffer("ambient");
	res.DeleteSoundBuffer("effect_pickup");
	res.DeleteSoundBuffer("enemy_death");
}

void GameScene::HandleEvents(sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
		Application::GetInstance().CloseWindow();
}

void GameScene::HandleInput(float dt)
{
	m_Player->Input(dt);
}

template<typename EntityType>
static void UpdateEntities(std::vector<EntityType>& entities, float dt)
{
	for(auto& entity : entities)
		entity.Update(dt);
}

static std::future<void> bulletsUpdateFuture;
static std::future<void> enemiesUpdateFuture;
static std::future<void> effectsUpdateFuture;

void GameScene::Update(float dt)
{
	CheckForPlayerCollisions(dt);
	
	m_Player->Update(dt);
	
	CheckForEnemiesShot();
	CheckForEnemiesToDespawn();
	CheckForBulletsToDespawn();
	CheckForEffectsToDespawn();
	
	enemiesUpdateFuture = std::async(std::launch::async, UpdateEntities<EnemyEntity>,  std::ref<std::vector<EnemyEntity>>(m_Enemies),		 dt);
	bulletsUpdateFuture = std::async(std::launch::async, UpdateEntities<BulletEntity>, std::ref<std::vector<BulletEntity>>(m_Bullets),		 dt);
	effectsUpdateFuture = std::async(std::launch::async, UpdateEntities<EffectEntity>, std::ref<std::vector<EffectEntity>>(m_EffectHolders), dt);
}

void GameScene::Render(sf::RenderTarget& renderer)
{
	Application::GetInstance().SetWindowView(m_Player->GetPlayerCameraView());

	renderer.draw(m_Floor);

	for(auto& bullet : m_Bullets)
		bullet.Render(renderer);
	
	for(auto& enemy : m_Enemies)
	 	enemy.Render(renderer);
	
	for(auto& effect : m_EffectHolders)
		effect.Render(renderer);

	m_Player->Render(renderer);
}

void GameScene::SpawnBullet(const sf::Vector2f& dir, const sf::Vector2f& pos, float velocity, float strength)
{
	m_Bullets.emplace_back(this, dir, pos, velocity, strength);
	m_Bullets.back().SetTexture(Resources::Get().GetTexture("basic_bullet"));
}

void GameScene::CheckForPlayerCollisions(float dt)
{
	sf::FloatRect playerCollider = m_Player->GetCollider();

	for(auto& effect : m_EffectHolders)
	{
		if(effect.GetCollider().intersects(playerCollider))
		{
			effect.OnPlayerIntersect(m_Player.get());
			
			m_PickupSound.play();
		}
	}

	if(!m_Player->IsVulnerable())
		return;

	for(auto& enemy : m_Enemies)
	{
		if(enemy.GetCollider().intersects(playerCollider))
		{
			m_Player->OnDamage(10, dt);

			break;
		}
	}
}

void GameScene::CheckForEnemiesShot()
{
	for(auto enemyItr = m_Enemies.begin(); enemyItr != m_Enemies.end(); ++enemyItr)
	{
		for(auto bulletItr = m_Bullets.begin(); bulletItr != m_Bullets.end(); ++bulletItr)
		{
			if(bulletItr->GetCollider().intersects(enemyItr->GetCollider()))
			{
				enemyItr->OnDamage(static_cast<int32_t>(bulletItr->GetStrength()));
				m_Bullets.erase(bulletItr);

				break;
			}
		}
	}
}

void GameScene::CheckForBulletsToDespawn()
{
	sf::Vector2f viewCenter = m_Player->GetPlayerCameraView().getCenter();
	sf::Vector2f viewSize = m_Player->GetPlayerCameraView().getSize();
	sf::FloatRect viewCollider(
		viewCenter.x - viewSize.x / 2.0f,
		viewCenter.y - viewSize.y / 2.0f,
		viewSize.x, viewSize.y
	);
	
	auto bulletsToRemoveRange = std::ranges::remove_if(m_Bullets, [&](const BulletEntity& bullet)
	{
		return !bullet.GetCollider().intersects(viewCollider);
	});

	m_Bullets.erase(bulletsToRemoveRange.begin(), bulletsToRemoveRange.end());
}

void GameScene::CheckForEnemiesToDespawn()
{
	auto enemiesToRemoveRange = std::ranges::remove_if(m_Enemies, [&](const EnemyEntity& enemy)
	{
		if(enemy.IsDead())
		{
			m_EnemyDeathSound.play();

			return true;
		}

		return false;
	});

	m_Enemies.erase(enemiesToRemoveRange.begin(), enemiesToRemoveRange.end());
}

void GameScene::CheckForEffectsToDespawn()
{
	auto effectsToRemoveRange = std::ranges::remove_if(m_EffectHolders, [](const EffectEntity& eff)
	{
		return eff.Expired();
	});

	m_EffectHolders.erase(effectsToRemoveRange.begin(), effectsToRemoveRange.end());
}
