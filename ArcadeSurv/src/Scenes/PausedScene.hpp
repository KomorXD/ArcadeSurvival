#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"

class PausedScene : public Scene
{
	public:
		PausedScene(const sf::Texture& lastFrame);
		virtual ~PausedScene() = default;

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

	private:
		sf::Sprite m_LastFrameSnapshot;
		sf::Text   m_PausedText;

		Button m_ResumeButton;
		Button m_ExitButton;
};