#pragma once

#include <SFML/Graphics.hpp>

class Scene
{
	public:
		virtual ~Scene() = default;

		virtual void HandleEvents(sf::Event& e)			= 0;
		virtual void HandleInput(float dt)				= 0;
		virtual void Update(float dt)					= 0;
		virtual void Render(sf::RenderTarget& renderer) = 0;
};