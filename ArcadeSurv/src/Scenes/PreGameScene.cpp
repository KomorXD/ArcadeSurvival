#include "PreGameScene.hpp"
#include "GameScene.hpp"
#include "../Application.hpp"
#include "../Utils/Resources.hpp"

#include <regex>

PreGameScene::PreGameScene(const sf::Sprite& background)
	: m_Background(background), m_NameInputBox({ 512.0f, 64.0f }, "")
{
	Application::GetInstance().GetWindow().setMouseCursorVisible(true);
	
	if(sf::Font* font = Resources::Get().GetFont("IBMPlexMonoRegular"))
		m_TextXd.setFont(*font);

	m_TextXd.setString("Enter your name");
	m_TextXd.setCharacterSize(50);
	m_TextXd.setOutlineThickness(3.0f);

	sf::FloatRect textRect = m_TextXd.getLocalBounds();

	m_TextXd.setOrigin(textRect.left + textRect.width / 2.0f,
					   textRect.top + textRect.height / 2.0f);

	sf::Vector2f windowSize = sf::Vector2f(Application::GetInstance().GetWindowSize());

	m_TextXd.setPosition({ windowSize.x / 2.0f, windowSize.y / 3.0f });
	
	m_NameInputBox.SetPosition(windowSize / 2.0f);
}

PreGameScene::~PreGameScene()
{}

void PreGameScene::HandleEvents(sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed)
	{
		switch(e.key.code)
		{
			case sf::Keyboard::Escape:
				Application::GetInstance().PopScene();
				break;

			case sf::Keyboard::Enter:
				if(m_IsNameValid)
				{
					Application::GetInstance().SetUsername(m_NameInputBox.GetString());
					Application::GetInstance().PopScene();
					Application::GetInstance().ChangeScene(std::make_unique<GameScene>());
				}

				break;

			case sf::Keyboard::Backspace:
				m_NameInputBox.EraseLastChar();
				InputValidation();
				
				break;
				
			default:
				HandleTextInput(e);
				InputValidation();

				break;
		}
	}
}

void PreGameScene::HandleInput(float dt)
{}

void PreGameScene::Update(float dt)
{}

void PreGameScene::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Background);
	renderer.draw(m_TextXd);
	
	m_NameInputBox.Render(renderer);
}

void PreGameScene::HandleTextInput(sf::Event& e)
{
	if(e.key.code > sf::Keyboard::Z || m_NameInputBox.GetString().length() > 15)
		return;

	m_NameInputBox.AppendChar(e.key.code + 65);
}

void PreGameScene::InputValidation()
{
	std::regex re("[A-Z0-9]{4,}");

	if(std::regex_match(m_NameInputBox.GetString(), re))
	{
		m_IsNameValid = true;
		m_NameInputBox.SetTextColor(sf::Color::White);

		return;
	}

	m_IsNameValid = false;
	m_NameInputBox.SetTextColor(sf::Color::Red);
}
