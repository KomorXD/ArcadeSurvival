#pragma once

#include "Scene.hpp"
#include "../Entities/PlayerEntity.hpp"
#include "../Entities/EnemyEntity.hpp"

#include <list>

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
		PlayerEntity m_Player;

		std::list<EnemyEntity> m_Enemies;
};