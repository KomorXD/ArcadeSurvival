#include "PausedScene.hpp"
#include "MainMenuScene.hpp"
#include "../Application.hpp"
#include "../Utils/Resources.hpp"

PausedScene::PausedScene(std::shared_ptr<sf::RenderTexture>& lastFrameRenderTexture)
	: Scene(), m_LastFrameSnapshotRenderTexture(lastFrameRenderTexture), m_ResumeButton({ 512.0f, 64.0f }, "Resume"), m_ExitButton({ 512.0f, 64.0f }, "Quit to menu")
{
	const sf::Texture& texture = m_LastFrameSnapshotRenderTexture->getTexture();
	sf::Vector2i textureSize   = sf::Vector2i(texture.getSize());

	m_LastSnapshot.setTexture(texture);
	m_LastSnapshot.setTextureRect({ 0, textureSize.y, textureSize.x, -textureSize.y });
	m_LastSnapshot.setColor({ 66, 66, 66 });
	
	m_PausedText.setString("PAUSED.");
	m_PausedText.setFont(*Resources::Get().GetFont("VT323"));
	m_PausedText.setCharacterSize(60);

	sf::FloatRect textBounds = m_PausedText.getLocalBounds();
	sf::Vector2f windowSize = sf::Vector2f(Application::GetInstance().GetWindowSize());

	m_PausedText.setPosition({ windowSize.x / 2.0f, windowSize.y * 2.0f / 7.0f });
	m_PausedText.setOrigin({ textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f });

	m_ResumeButton.SetPosition({ windowSize.x / 2.0f, windowSize.y * 4.0f / 7.0f });
	m_ResumeButton.SetFunction([&]()
	{
		Application::GetInstance().GetWindow().setMouseCursorVisible(false);
		Application::GetInstance().PopScene();
	});

	m_ExitButton.SetPosition({ windowSize.x / 2.0f, windowSize.y * 5.0f / 7.0f });
	m_ExitButton.SetFunction([&]()
	{
		Application::GetInstance().GetWindow().setMouseCursorVisible(true);
		Application::GetInstance().PopScene();
		Application::GetInstance().ChangeScene(std::make_unique<MainMenuScene>());
	});

	Application::GetInstance().GetWindow().setMouseCursorVisible(true);
}

void PausedScene::HandleEvents(sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
	{
		Application::GetInstance().PopScene();

		return;
	}

	if(m_ResumeButton.HandleEvents(Application::GetInstance().GetWindow(), e))
		return;

	if(m_ExitButton.HandleEvents(Application::GetInstance().GetWindow(), e))
		return;
}

void PausedScene::HandleInput(float dt)
{}

void PausedScene::Update(float dt)
{}

void PausedScene::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_LastSnapshot);
	renderer.draw(m_PausedText);
	
	m_ResumeButton.Render(renderer);
	m_ExitButton.Render(renderer);
}
