#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"

class MainMenuScene : public Scene
{
	public:
		MainMenuScene();
		virtual ~MainMenuScene();

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

	private:
		sf::Sprite m_Background;
		
		Button m_PlayButton;
		Button m_InstructionsButton;
		Button m_ExitButton;
};