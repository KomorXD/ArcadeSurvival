#pragma once

#include "Scene.hpp"
#include "../Entities/PlayerEntity.hpp"

class DyingScene : public Scene
{
	public:
		DyingScene(std::shared_ptr<sf::RenderTexture>& lastFrameRenderTexture, std::shared_ptr<PlayerEntity>& player);
		virtual ~DyingScene() = default;

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

	private:
		std::shared_ptr<sf::RenderTexture> m_LastFrameRenderTexture;
		std::shared_ptr<PlayerEntity>	   m_Player;

		sf::Sprite m_LastFrameSnapshot;

		float m_DyingTime = 0.0f;
};