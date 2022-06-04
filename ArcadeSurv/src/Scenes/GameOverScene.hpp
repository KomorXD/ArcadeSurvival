#pragma once

#include "Scene.hpp"
#include "../Entities/PlayerEntity.hpp"
#include "../UI/Button.hpp"

class GameOverScene : public Scene
{
	public:
		GameOverScene(std::shared_ptr<sf::RenderTexture>& lastFrameRenderTexture, std::shared_ptr<PlayerEntity>& player);
		virtual ~GameOverScene() = default;

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

	private:
		std::shared_ptr<sf::RenderTexture> m_LastFrameRenderTexture;
		std::shared_ptr<PlayerEntity>	   m_Player;

		sf::Sprite m_LastFrameSnapshot;
		sf::Text   m_GameOverText;

		Button m_QuitToMenuButton;
		Button m_QuitTheGameButton;
};