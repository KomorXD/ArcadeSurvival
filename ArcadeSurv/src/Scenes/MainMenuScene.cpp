#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "../Utils/Resources.hpp"
#include "../Application.hpp"

MainMenuScene::MainMenuScene()
	: Scene(), m_PlayButton({ 512.0f, 64.0f }, "Play"), m_InstructionsButton({ 512.0f, 64.0f }, "How to play"), m_ExitButton({ 512.0f, 64.0f }, "Exit")
{
	Application::GetInstance().GetWindow().setMouseCursorVisible(true);

	sf::Vector2f windowSize = sf::Vector2f(Application::GetInstance().GetWindowSize());

	m_PlayButton.SetPosition({ windowSize.x / 2.0f, windowSize.y * 3.0f / 7.0f });
	m_PlayButton.SetFunction([&]()
	{
		Application::GetInstance().GetWindow().setMouseCursorVisible(false);
		Application::GetInstance().ChangeScene(std::make_unique<GameScene>());
	});

	m_InstructionsButton.SetPosition({ windowSize.x / 2.0f, windowSize.y * 4.0f / 7.0f });
	m_InstructionsButton.SetFunction([&]() { ; });

	m_ExitButton.SetPosition({ windowSize.x / 2.0f, windowSize.y * 5.0f / 7.0f });
	m_ExitButton.SetFunction([&]() { Application::GetInstance().CloseWindow(); });

	Resources::Get().LoadTexture("menu_background");

	m_Background.setTexture(*Resources::Get().GetTexture("menu_background"));
	m_Background.setScale({ windowSize.x / 525.0f, windowSize.x / 525.0f });
}

MainMenuScene::~MainMenuScene()
{
	Resources::Get().DeleteTexture("menu_background");
}

void MainMenuScene::HandleEvents(sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
	{
		Application::GetInstance().CloseWindow();

		return;
	}

	if(m_PlayButton.HandleEvents(Application::GetInstance().GetWindow(), e))
		return;

	if(m_InstructionsButton.HandleEvents(Application::GetInstance().GetWindow(), e))
		return;

	if(m_ExitButton.HandleEvents(Application::GetInstance().GetWindow(), e))
		return;
}

void MainMenuScene::HandleInput(float dt)
{}

void MainMenuScene::Update(float dt)
{}

void MainMenuScene::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Background);

	m_PlayButton.Render(renderer);
	m_InstructionsButton.Render(renderer);
	m_ExitButton.Render(renderer);
}
