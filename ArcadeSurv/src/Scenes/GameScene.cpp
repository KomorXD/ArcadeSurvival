#include "GameScene.hpp"
#include "PausedScene.hpp"
#include "../Application.hpp"
#include "../Utils/Resources.hpp"
#include "../Effects/Effects.hpp"
#include "../Utils/Random.hpp"
#include "../WeaponTypes/Weapons.hpp"

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
	res.LoadTexture("effect_heal");
	res.LoadTexture("floor");
	res.LoadTexture("sky");

	res.LoadSoundBuffer("shoot");
	res.LoadSoundBuffer("ambient");
	res.LoadSoundBuffer("effect_pickup");
	res.LoadSoundBuffer("enemy_death");
	res.LoadSoundBuffer("player_hurt");

	res.LoadFont("IBMPlexMonoRegular");
}

static int32_t lol = 10;

GameScene::GameScene()
	: m_Floor({ 5000.0f, 5000.0f }), m_WaveBar(&lol, { 500.0f, 16.0f }, { 10.0f, 65.0f })
{
	lol = 10;

	LoadResources();

	m_WaveBar.SetColor(sf::Color::Cyan);

	m_SnapshotRenderTexture.create(1280, 720);

	if(sf::Font* font = Resources::Get().GetFont("IBMPlexMonoRegular"))
		m_TimeAliveText.setFont(*font);
	
	m_TimeAliveText.setString("00:00:00");
	m_TimeAliveText.setPosition({ Application::GetInstance().GetWindow().getSize().x / 2.0f, 5.0f });

	m_TimeAliveText.move({ -m_TimeAliveText.getLocalBounds().width / 1.6f, 0.0f});

	m_Player = std::make_unique<PlayerEntity>(this);

	m_Player->SetPosition({ 640.0f, 360.0f });
	m_Player->SetMovementSpeed(200.0f);
	m_Player->SetWeaponType(std::make_unique<BasicWeapon>());

	if(sf::Texture* tex = Resources::Get().GetTexture("player_atlas"))
		m_Player->SetTexture(tex);

	if(sf::Texture* tex = Resources::Get().GetTexture("sky"))
	{
		m_Skybox.setTexture(*tex);
		m_Skybox.scale({ 5.0f, 2.8125f });
	}
	
	m_Floor.setOrigin({ 2500.0f, 2500.0f });
	m_Floor.setPosition({ 640.0f, 360.0f });

	if(sf::Texture* floorText = Resources::Get().GetTexture("floor"))
	{
		floorText->setRepeated(true);
		m_Floor.setTexture(floorText);
		m_Floor.setTextureRect({ 0, 0, 2500, 2500 });
	}

	m_EffectHolders.emplace_back(EffectType::HASTE,	  10.0f, 100.0f, sf::Vector2f(200.0f,  200.0f));
	m_EffectHolders.emplace_back(EffectType::QUAD,	  10.0f, 100.0f, sf::Vector2f(100.0f,  600.0f));
	m_EffectHolders.emplace_back(EffectType::CRIPPLE, 10.0f, 100.0f, sf::Vector2f(700.0f,  200.0f));
	m_EffectHolders.emplace_back(EffectType::HEAL,	  0.0f,	 100.0f, sf::Vector2f(1000.0f, 200.0f));

	for(auto& ef : m_EffectHolders)
		ef.SetSize({ 48.0f, 48.0f });

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

	m_WaveMan = std::make_unique<WavesManager>(this);
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
	res.DeleteTexture("sky");

	res.DeleteSoundBuffer("shoot");
	res.DeleteSoundBuffer("ambient");
	res.DeleteSoundBuffer("effect_pickup");
	res.DeleteSoundBuffer("enemy_death");
	res.DeleteSoundBuffer("player_hurt");

	res.DeleteFont("IBMPlexMonoRegular");
}

void GameScene::HandleEvents(sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed)
	{
		switch(e.key.code)
		{
			case sf::Keyboard::Escape:
				m_SnapshotRenderTexture.clear();
				Render(m_SnapshotRenderTexture);
				Application::GetInstance().PushScene(std::make_unique<PausedScene>(m_SnapshotRenderTexture.getTexture()));

				break;
			default:
				break;
		}
	}
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

static std::string GetFormattedTime(float secondsPassed)
{
	int32_t minutes = static_cast<int32_t>(secondsPassed) / 60;
	int32_t seconds = static_cast<int32_t>(secondsPassed) % 60;
	
	secondsPassed -= 60.0f * minutes + seconds;

	int32_t miliseconds = static_cast<int32_t>(secondsPassed * 100.0f);

	std::string minutesStr	   = minutes < 10	  ? "0" + std::to_string(minutes)	  : std::to_string(minutes);
	std::string secondsStr	   = seconds < 10	  ? "0" + std::to_string(seconds)	  : std::to_string(seconds);
	std::string milisecondsStr = miliseconds < 10 ? "0" + std::to_string(miliseconds) : std::to_string(miliseconds);

	return minutesStr + ":" + secondsStr + ":" + milisecondsStr;
}

void GameScene::Update(float dt)
{
	m_WaveBar.Update(10.0f);

	m_TimeAlive += dt;

	CheckForPlayerCollisions(dt);
	
	m_Player->Update(dt);

	CheckForPlayerOutsideOfArena();
	CheckForEnemiesShot();
	CheckForEnemiesToDespawn();
	CheckForBulletsToDespawn();
	CheckForEffectsToDespawn();

	std::future<void> bulletsUpdateFuture = std::async(std::launch::async, UpdateEntities<EnemyEntity>,  std::ref<std::vector<EnemyEntity>>(m_Enemies),		   dt);
	std::future<void> enemiesUpdateFuture = std::async(std::launch::async, UpdateEntities<BulletEntity>, std::ref<std::vector<BulletEntity>>(m_Bullets),	   dt);
	std::future<void> effectsUpdateFuture = std::async(std::launch::async, UpdateEntities<EffectEntity>, std::ref<std::vector<EffectEntity>>(m_EffectHolders), dt);

	m_TimeAliveText.setString(GetFormattedTime(m_TimeAlive));
}

void GameScene::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Skybox);

	renderer.setView(m_Player->GetPlayerCameraView());

	renderer.draw(m_Floor);

	for(auto& bullet : m_Bullets)
		bullet.Render(renderer);
	
	for(auto& enemy : m_Enemies)
	 	enemy.Render(renderer);
	
	for(auto& effect : m_EffectHolders)
		effect.Render(renderer);

	m_Player->Render(renderer);
	
	renderer.setView(m_Player->GetInterfaceView());

	renderer.draw(m_TimeAliveText);
	m_WaveBar.draw(renderer, sf::RenderStates::Default);
}

void GameScene::SpawnBullet(BulletEntity bullet)
{
	bullet.SetTexture(Resources::Get().GetTexture("basic_bullet"));
	m_Bullets.push_back(bullet);
}

void GameScene::SpawnEnemy(const sf::Vector2f& pos, const sf::Color& color, float strength, float movementSpeed)
{
	m_Enemies.emplace_back(m_Player.get(), pos);
	m_Enemies.back().SetColor(color);
	m_Enemies.back().SetStrength(strength);
	m_Enemies.back().SetMovementSpeed(movementSpeed);

	if(sf::Texture* tex = Resources::Get().GetTexture("enemy_atlas"))
		m_Enemies.back().SetTexture(tex);
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
		if(!enemy.IsDying() && enemy.GetCollider().intersects(playerCollider))
		{
			m_Player->OnDamage(static_cast<int32_t>(enemy.GetStrength()), dt);

			break;
		}
	}
}

void GameScene::CheckForPlayerOutsideOfArena()
{
	sf::Vector2f  playerPos		  = m_Player->GetPosition();
	sf::FloatRect arenaBoundaries = m_Floor.getGlobalBounds();

	if(playerPos.x - 32.0f < arenaBoundaries.left)
		playerPos.x = arenaBoundaries.left + 32.0f;

	if(playerPos.y - 32.0f < arenaBoundaries.top)
		playerPos.y = arenaBoundaries.top + 32.0f;

	if(playerPos.x + 32.0f > arenaBoundaries.left + arenaBoundaries.width)
		playerPos.x = arenaBoundaries.left + arenaBoundaries.width - 32.0f;
	
	if(playerPos.y + 32.0f > arenaBoundaries.top + arenaBoundaries.height)
		playerPos.y = arenaBoundaries.top + arenaBoundaries.height - 32.0f;

	m_Player->SetPosition(playerPos);
}

void GameScene::CheckForEnemiesShot()
{
	for(auto enemyItr = m_Enemies.begin(); enemyItr != m_Enemies.end(); ++enemyItr)
	{
		if(enemyItr->IsDying())
			continue;

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
			m_Player->OnEnemyKilled();

			--lol;

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
