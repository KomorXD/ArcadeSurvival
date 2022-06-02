#pragma once

#include "Scene.hpp"
#include "../Entities/PlayerEntity.hpp"

class DyingScene : public Scene
{
	public:
		DyingScene(const sf::Texture& lastFrameTexture, PlayerEntity* player);
		virtual ~DyingScene() = default;

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

	private:
		sf::Sprite m_LastFrameSnapshot;
		PlayerEntity* m_Player = nullptr;

		float m_DyingTime = 0.0f;
};