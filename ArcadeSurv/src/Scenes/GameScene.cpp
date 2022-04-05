#include "GameScene.hpp"
#include "../Application.hpp"
#include "../Utils/Resources.hpp"

GameScene::GameScene()
{
	m_Player.SetPosition({ 640.0f, 360.0f });
	m_Player.SetMovementSpeed(300.0f);
	m_Player.SetTexture(Resources::Get().textures.GetResource("lol"));

	EnemyEntity prototype(&m_Player);

	prototype.SetMovementSpeed(100.0f);

	prototype.SetPosition({ 200.0f, 200.0f });
	m_Enemies.push_back(prototype);

	prototype.SetPosition({ 100.0f, 600.0f });
	m_Enemies.push_back(prototype);

	prototype.SetPosition({ 700.0f, 200.0f });
	m_Enemies.push_back(prototype);
}

void GameScene::HandleEvents(sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
		Application::GetInstance().GetWindow().close();
}

void GameScene::HandleInput(float dt)
{
	m_Player.Input();
}

void GameScene::Update(float dt)
{
	m_Player.Update(dt);

	for(auto& enemy : m_Enemies)
		enemy.Update(dt);
}

void GameScene::Render(sf::RenderTarget& renderer)
{
	Application::GetInstance().GetWindow().setView(m_Player.GetPlayerCameraView());

	m_Player.Render(renderer);
	
	for(auto& enemy : m_Enemies)
		enemy.Render(renderer);
}
