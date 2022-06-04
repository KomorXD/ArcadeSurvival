#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
	public:
		Entity(const sf::Vector2f& pos = { 0.0f, 0.0f });
		virtual ~Entity() = default;

		virtual void Update(float dt)					= 0;
		virtual void Render(sf::RenderTarget& renderer) = 0;

		virtual void SetTexture(sf::Texture* texture);
		virtual void SetPosition(const sf::Vector2f& pos);
		virtual void SetSize(const sf::Vector2f& size);
		virtual void SetColor(const sf::Color& color);

		virtual inline sf::FloatRect GetCollider() const { return m_Body.getGlobalBounds(); }
		virtual inline sf::Vector2f GetPosition() const { return m_Body.getPosition(); }
		virtual void SetTextureRect(const sf::IntRect& rect);

	protected:
		sf::RectangleShape m_Body;
};