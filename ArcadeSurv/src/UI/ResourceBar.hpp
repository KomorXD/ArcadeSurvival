#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class ResourceBar : public sf::Drawable
{
	public:
		ResourceBar(int32_t* pResource, const sf::Vector2f& size, const sf::Vector2f& pos);

		void Update();
		void SetColor(const sf::Color& color);
		
		virtual void draw(sf::RenderTarget& renderer, sf::RenderStates states) const override;

	private:
		int32_t* m_pRes;
		
		sf::RectangleShape m_Outline;
		sf::RectangleShape m_Bar;
};