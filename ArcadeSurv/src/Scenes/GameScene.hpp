#pragma once

#include "Scene.hpp"
#include "../Entities/PlayerEntity.hpp"
#include "../Entities/EnemyEntity.hpp"

#include <vector>

class GameScene : public Scene
{
	public:
		GameScene();
		~GameScene() = default;

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

	private:
		void CheckForCollisions(float dt);

		PlayerEntity m_Player;

		std::vector<EnemyEntity> m_Enemies;
};