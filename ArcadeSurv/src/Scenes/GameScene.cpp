#include "GameScene.hpp"
#include "../Application.hpp"
#include "../Utils/Resources.hpp"
#include "../Effects/HasteEffect.hpp"

GameScene::GameScene()
	: m_Player(this)
{
	m_Player.SetPosition({ 640.0f, 360.0f });
	m_Player.SetMovementSpeed(200.0f);
	m_Player.SetTexture(Resources::Get().textures.GetResource("player_atlas"));

	EnemyEntity prototype(this, &m_Player);
	
	prototype.SetMovementSpeed(100.0f);
	prototype.SetTexture(Resources::Get().textures.GetResource("enemy_atlas"));

	prototype.SetPosition({ 200.0f, 200.0f });
	m_Enemies.push_back(prototype);

	prototype.SetPosition({ 100.0f, 600.0f });
	m_Enemies.push_back(prototype);

	prototype.SetPosition({ 700.0f, 200.0f });
	m_Enemies.push_back(prototype);

	prototype.SetPosition({ 2.0f, 9.0f });
	m_Enemies.push_back(prototype);

	m_EffectHolders.emplace_back(this, sf::Vector2f(200.0f, 200.0f), EffectType::HASTE, 10.0f, 100.0f);
	m_EffectHolders.emplace_back(this, sf::Vector2f(100.0f, 600.0f), EffectType::QUAD,  10.0f, 100.0f);
	m_EffectHolders.emplace_back(this, sf::Vector2f(700.0f, 200.0f), EffectType::HASTE, 10.0f, 100.0f);
}

void GameScene::HandleEvents(sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
		Application::GetInstance().GetWindow().close();
}

void GameScene::HandleInput(float dt)
{
	m_Player.Input(dt);
}

void GameScene::Update(float dt)
{
	CheckForPlayerCollisions(dt);

	m_Player.Update(dt);

	CheckForEnemiesShot();
	CheckForEnemiesToDespawn();
	CheckForBulletsToDespawn();
	CheckForEffectsToDespawn();

	for(auto& bullet : m_Bullets)
		bullet.Update(dt);

	for(auto& enemy : m_Enemies)
		enemy.Update(dt);

	for(auto& effect : m_EffectHolders)
		effect.Update(dt);
}

void GameScene::Render(sf::RenderTarget& renderer)
{
	Application::GetInstance().SetWindowView(m_Player.GetPlayerCameraView());

	for(auto& bullet : m_Bullets)
		bullet.Render(renderer);

	for(auto& enemy : m_Enemies)
	 	enemy.Render(renderer);
	
	for(auto& effect : m_EffectHolders)
		effect.Render(renderer);

	m_Player.Render(renderer);
}

void GameScene::SpawnBullet(const sf::Vector2f& dir, const sf::Vector2f& pos, float velocity, float strength)
{
	m_Bullets.emplace_back(this, dir, pos, velocity, strength);
	m_Bullets.back().SetTexture(Resources::Get().textures.GetResource("basic_bullet"));
}

void GameScene::CheckForPlayerCollisions(float dt)
{
	sf::FloatRect playerCollider = m_Player.GetCollider();

	for(auto& effect : m_EffectHolders)
	{
		if(effect.GetCollider().intersects(playerCollider))
		{
			effect.OnPlayerIntersect(&m_Player);
		}
	}

	if(!m_Player.IsVulnerable())
		return;

	for(auto& enemy : m_Enemies)
	{
		if(enemy.GetCollider().intersects(playerCollider))
		{
			m_Player.OnDamage(10, dt);

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
	sf::Vector2f viewCenter = m_Player.GetPlayerCameraView().getCenter();
	sf::Vector2f viewSize = m_Player.GetPlayerCameraView().getSize();
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
	auto enemiesToRemoveRange = std::ranges::remove_if(m_Enemies, [](const EnemyEntity& enemy)
	{
		return enemy.IsDead();
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
