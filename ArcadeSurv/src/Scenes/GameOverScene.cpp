#include "GameOverScene.hpp"
#include "MainMenuScene.hpp"
#include "../Application.hpp"

GameOverScene::GameOverScene(std::shared_ptr<sf::RenderTexture>& lastFrameRenderTexture, std::shared_ptr<PlayerEntity>& player)
	: m_LastFrameRenderTexture(lastFrameRenderTexture), m_LastFrameSnapshot(lastFrameRenderTexture->getTexture()), m_Player(player)
	, m_QuitToMenuButton({ 512.0f, 64.0f }, "Quit to the main menu"), m_QuitTheGameButton({ 512.0f, 64.0f }, "Quit the game")
{
	Application::GetInstance().GetWindow().setMouseCursorVisible(true);
	m_LastFrameSnapshot.setColor({ 55, 55, 55 });

	sf::Vector2i textSize = sf::Vector2i(m_LastFrameSnapshot.getTexture()->getSize());
	sf::Vector2f windowSize = sf::Vector2f(Application::GetInstance().GetWindowSize());

	m_LastFrameSnapshot.setTextureRect({ 0, textSize.y, textSize.x, -textSize.y });

	m_QuitToMenuButton.SetPosition({ windowSize.x / 2.0f, windowSize.y * 4.0f / 7.0f });
	m_QuitToMenuButton.SetFunction([&]()
	{
		Application::GetInstance().ChangeScene(std::make_unique<MainMenuScene>());
	});

	m_QuitTheGameButton.SetPosition({ windowSize.x / 2.0f, windowSize.y * 5.0f / 7.0f });
	m_QuitTheGameButton.SetFunction([&]()
	{
		Application::GetInstance().CloseWindow();
	});
}

void GameOverScene::HandleEvents(sf::Event& e)
{
	if(m_QuitToMenuButton.HandleEvents(Application::GetInstance().GetWindow(), e))
		return;

	if(m_QuitTheGameButton.HandleEvents(Application::GetInstance().GetWindow(), e))
		return;
}

void GameOverScene::HandleInput(float dt)
{}

void GameOverScene::Update(float dt)
{}

void GameOverScene::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_LastFrameSnapshot);
	m_Player->Render(renderer);

	m_QuitToMenuButton.Render(renderer);
	m_QuitTheGameButton.Render(renderer);
}
