#pragma once

#include "ResourceBar.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

ResourceBar::ResourceBar(int32_t* pResource, const sf::Vector2f& size, const sf::Vector2f& pos)
	: m_pRes(pResource), m_Outline(size), m_Bar(size)
{
	m_Outline.setPosition(pos);
	m_Bar.setPosition(pos);

	m_Outline.setOutlineThickness(3.0f);
	m_Outline.setOutlineColor(sf::Color::Black);
	m_Outline.setFillColor(sf::Color::Transparent);
}

void ResourceBar::Update(float maxVal)
{
	m_Bar.setSize({ m_Outline.getSize().x * (*m_pRes / maxVal), m_Outline.getSize().y });
}

void ResourceBar::SetColor(const sf::Color& color)
{
	m_Bar.setFillColor(color);
}

void ResourceBar::draw(sf::RenderTarget& renderer, sf::RenderStates states) const
{
	renderer.draw(m_Bar);
	renderer.draw(m_Outline);
}
