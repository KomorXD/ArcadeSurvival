#include "PreGameScene.hpp"
#include "GameScene.hpp"
#include "../Application.hpp"

#include <regex>

PreGameScene::PreGameScene(const sf::Sprite& background)
	: m_Background(background), m_NameInputBox({ 512.0f, 64.0f }, "")
{
	Application::GetInstance().GetWindow().setMouseCursorVisible(true);
	
	m_NameInputBox.SetPosition(sf::Vector2f(Application::GetInstance().GetWindowSize()) / 2.0f);
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
	m_NameInputBox.Render(renderer);
}

void PreGameScene::HandleTextInput(sf::Event& e)
{
	if(e.key.code > 25 || m_NameInputBox.GetString().length() > 15)
		return;

	m_NameInputBox.AppendChar(e.key.code + 65);
}

void PreGameScene::InputValidation()
{
	std::regex re("[A-Z]{4,}");

	if(std::regex_match(m_NameInputBox.GetString(), re))
	{
		m_IsNameValid = true;
		m_NameInputBox.SetTextColor(sf::Color::White);

		return;
	}

	m_IsNameValid = false;
	m_NameInputBox.SetTextColor(sf::Color::Red);
}
