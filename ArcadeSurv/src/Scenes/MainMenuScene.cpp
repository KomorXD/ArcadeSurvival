#include "MainMenuScene.hpp"
#include "PreGameScene.hpp"
#include "ScoresScene.hpp"
#include "../Utils/Resources.hpp"
#include "../Application.hpp"

MainMenuScene::MainMenuScene()
	: Scene(), m_PlayButton({ 512.0f, 64.0f }, "Play"), m_ScoresButton({ 512.0f, 64.0f }, "Highscores"), m_ExitButton({ 512.0f, 64.0f }, "Exit")
{
	Application::GetInstance().GetWindow().setMouseCursorVisible(true);
	Resources::Get().LoadFont("IBMPlexMonoRegular");

	if(sf::Font* font = Resources::Get().GetFont("IBMPlexMonoRegular"))
		m_Title.setFont(*font);

	m_Title.setString("giera xd");
	m_Title.setCharacterSize(60);
	m_Title.setLetterSpacing(3.0f);
	m_Title.setOutlineThickness(3.0f);

	sf::FloatRect textRect = m_Title.getLocalBounds();

	m_Title.setOrigin(textRect.left + textRect.width / 2.0f,
					  textRect.top + textRect.height / 2.0f);

	sf::Vector2f windowSize = sf::Vector2f(Application::GetInstance().GetWindowSize());

	m_Title.setPosition({ windowSize.x / 2.0f, windowSize.y / 7.0f });

	m_PlayButton.SetPosition({ windowSize.x / 2.0f, windowSize.y * 3.0f / 7.0f });
	m_PlayButton.SetFunction([&]()
	{
		Application::GetInstance().PushScene(std::make_unique<PreGameScene>(m_Background));
	});

	m_ScoresButton.SetPosition({ windowSize.x / 2.0f, windowSize.y * 4.0f / 7.0f });
	m_ScoresButton.SetFunction([&]()
	{
		Application::GetInstance().PushScene(std::make_unique<ScoresScene>(m_Background));
	});

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

	if(m_ScoresButton.HandleEvents(Application::GetInstance().GetWindow(), e))
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
	m_ScoresButton.Render(renderer);
	m_ExitButton.Render(renderer);
	
	renderer.draw(m_Title);
}
