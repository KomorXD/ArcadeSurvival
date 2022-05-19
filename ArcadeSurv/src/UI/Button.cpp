#include "Button.hpp"

Button::Button(const sf::Vector2f& size, const std::string& text)
	: Textbox(size, text)
{}

bool Button::HandleEvents(sf::RenderWindow& window, sf::Event e)
{
	if(m_Body.IsRolledOn(window))
	{
		m_Body.setFillColor({ 255, 255, 255 });

		if(m_Body.IsClickedOn(window, e))
		{
			m_TriggerFunc();

			return true;
		}

		return false;
	}

	m_Body.setFillColor({ 200, 200, 200 });

	return false;
}

void Button::SetFunction(std::function<void(void)> f)
{
	m_TriggerFunc = f;
}
