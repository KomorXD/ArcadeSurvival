#include "Effect.hpp"

#include <algorithm>
#include <SFML/Graphics/RenderTarget.hpp>

Effect::Effect(float time, sf::Texture* icon)
	: m_TimeLeft(time)
{
	if(icon)
		m_Icon.setTexture(*icon);
}

void Effect::RefreshEffect(float time)
{
	m_TimeLeft = time;
}

void Effect::ClearEffect()
{
	m_TimeLeft = 0.0f;
}

void Effect::Update(float dt)
{
	if(m_AffectedPlayer)
		m_TimeLeft = std::max(m_TimeLeft - dt, 0.0f);
}

void Effect::RenderIcon(sf::RenderTarget& renderer)
{
	renderer.draw(m_Icon);
}

void Effect::SetIconPosition(const sf::Vector2f& pos)
{
	m_Icon.setPosition(pos);
}
