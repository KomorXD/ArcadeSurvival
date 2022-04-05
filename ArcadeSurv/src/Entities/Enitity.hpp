#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
	public:
		Entity(float size);
		virtual ~Entity() = default;

		virtual void Update(float dt)					= 0;
		virtual void Render(sf::RenderTarget& renderer) = 0;

		virtual void SetTexture(sf::Texture* texture);
		virtual void SetPosition(const sf::Vector2f& pos);
		virtual void SetMovementSpeed(float ms);

		virtual inline sf::Vector2f GetPosition() const { return m_Body.getPosition(); }

	protected:
		sf::RectangleShape m_Body;
		float m_MovementSpeed;
};