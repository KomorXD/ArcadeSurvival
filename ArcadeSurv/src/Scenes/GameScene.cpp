#include "GameScene.hpp"
#include "PausedScene.hpp"
#include "DyingScene.hpp"
#include "../Application.hpp"
#include "../Utils/Resources.hpp"
#include "../Utils/Random.hpp"
#include "../Effects.hpp"
#include "../WeaponTypes.hpp"

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
	res.LoadTexture("effect_spread_weapon");
	res.LoadTexture("effect_explosive_weapon");
	res.LoadTexture("effect_no_weapon");
	res.LoadTexture("floor");
	res.LoadTexture("sky");

	res.LoadSoundBuffer("shoot");
	res.LoadSoundBuffer("ambient");
	res.LoadSoundBuffer("effect_pickup");
	res.LoadSoundBuffer("enemy_death");
	res.LoadSoundBuffer("player_hurt");

	res.LoadFont("IBMPlexMonoRegular");
}

GameScene::GameScene()
	: m_Floor({ 10000.0f, 10000.0f })
{
	LoadResources();

	sf::Vector2u windowSize = Application::GetInstance().GetWindowSize();

	m_SnapshotRenderTexture.create(windowSize.x, windowSize.y);

	if(sf::Font* font = Resources::Get().GetFont("IBMPlexMonoRegular"))
		m_TimeAliveText.setFont(*font);
	
	m_TimeAliveText.setString("00:00:00");
	m_TimeAliveText.setPosition({ Application::GetInstance().GetWindowSize().x / 2.0f, 5.0f });
	m_TimeAliveText.move({ -m_TimeAliveText.getLocalBounds().width / 1.6f, 0.0f});

	m_Player = std::make_shared<PlayerEntity>(this);

	m_Player->SetPosition({ 0.0f, 0.0f });
	m_Player->SetMovementSpeed(200.0f);
	m_Player->SetWeaponType(std::make_unique<BasicWeapon>());

	if(sf::Texture* tex = Resources::Get().GetTexture("player_atlas"))
		m_Player->SetTexture(tex);

	if(sf::Texture* tex = Resources::Get().GetTexture("sky"))
	{
		m_Skybox.setTexture(*tex);
		m_Skybox.scale({ 5.0f, 2.8125f });
	}
	
	m_Floor.setOrigin(m_Floor.getSize() / 2.0f);
	m_Floor.setPosition({ 0.0f, 0.0f });
	m_Floor.setOutlineThickness(20.0f);
	m_Floor.setOutlineColor(sf::Color::Black);

	if(sf::Texture* floorText = Resources::Get().GetTexture("floor"))
	{
		floorText->setRepeated(true);
		m_Floor.setTexture(floorText);
		m_Floor.setTextureRect({ 0, 0, 5000, 5000 });
	}

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

	m_WaveMan = std::make_unique<WavesManager>(this, m_Player);
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
	res.DeleteTexture("effect_spread_weapon");
	res.DeleteTexture("effect_explosive_weapon");
	res.DeleteTexture("effect_no_weapon");
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
	if(m_Player->IsDead())
	{
		m_SnapshotRenderTexture.clear();
		Render(m_SnapshotRenderTexture);

		Application::GetInstance().PushScene(std::make_unique<DyingScene>(m_SnapshotRenderTexture.getTexture(), m_Player.get()));

		return;
	}

	m_DeltaTime = dt;

	m_WaveMan->Update(dt);

	m_TimeAlive += dt;

	CheckForPlayerCollisions();
	
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

	if(m_WaveMan->WaveOver())
		m_WaveMan->NextWave();
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
	
	m_WaveMan->Render(renderer);
}

void GameScene::SpawnBullet(BulletEntity bullet)
{
	if(sf::Texture* text = Resources::Get().GetTexture("basic_bullet"))
		bullet.SetTexture(text);

	m_Bullets.push_back(bullet);
}

void GameScene::SpawnEnemy(EnemyEntity enemy)
{
	if(sf::Texture* text = Resources::Get().GetTexture("enemy_atlas"))
		enemy.SetTexture(text);

	enemy.SetPlayerPtr(m_Player.get());
	m_Enemies.push_back(enemy);
}

void GameScene::SpawnPowerUp(EffectEntity&& effect)
{
	m_EffectHolders.push_back(std::move(effect));
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

void GameScene::DealDamageInArea(const sf::Vector2f& center, float radius, int32_t damage)
{
	for(auto& enemy : m_Enemies)
	{
		sf::Vector2f enemyPos = enemy.GetPosition();

		if(std::sqrtf(std::powf(center.x - enemyPos.x, 2.0f) + std::powf(center.y - enemyPos.y, 2.0f)) <= radius)
			enemy.OnDamage(damage, m_DeltaTime);
	}
}

void GameScene::CheckForPlayerCollisions()
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
			m_Player->OnDamage(static_cast<int32_t>(enemy.GetStrength()), m_DeltaTime);

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
				enemyItr->OnDamage(static_cast<int32_t>(bulletItr->GetStrength()), m_DeltaTime);

				if(m_Player->HasEffect(EffectType::EXPLOSIVE_WEAPON))
					DealDamageInArea(bulletItr->GetPosition(), 200.0f, static_cast<int32_t>(20.0f * m_Player->GetDmgMultiplier()));

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
			m_WaveMan->OnEnemyKilled();

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
