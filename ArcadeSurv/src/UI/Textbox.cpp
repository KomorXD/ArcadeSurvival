#include "Textbox.hpp"
#include "../Utils/Resources.hpp"

Textbox::Textbox(const sf::Vector2f& size, const std::string& text)
{
	m_Body.setSize(size);
	m_Body.setFillColor({ 200, 200, 200 });
	m_Body.setOrigin(m_Body.getSize() / 2.0f);
	m_Body.setTexture(Resources::Get().GetTexture("textbox"));

	m_Text.setString(text);
	m_Text.setCharacterSize(40);
	m_Text.setFont(*Resources::Get().GetFont("VT323"));

	UpdateText();
}

bool Textbox::HandleEvents(sf::RenderWindow& window, sf::Event e)
{
	return false;
}

void Textbox::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Body);
	renderer.draw(m_Text);
}

void Textbox::SetPosition(const sf::Vector2f& pos)
{
	m_Body.setPosition(pos);
	m_Text.setPosition(pos);

	UpdateText();
}

void Textbox::SetText(const std::string& text)
{
	m_Text.setString(text);

	UpdateText();
}

void Textbox::AppendChar(char c)
{
	m_Text.setString(m_Text.getString() + c);

	UpdateText();
}

void Textbox::SetSize(const sf::Vector2f& size)
{
	m_Body.setSize(size);

	UpdateText();
}

void Textbox::SetTexture(sf::Texture* texture)
{
	m_Body.setTexture(texture);
}

void Textbox::SetColor(const sf::Color& color)
{
	m_Body.setFillColor(color);
}

void Textbox::SetTextColor(const sf::Color& color)
{
	m_Text.setFillColor(color);
}

void Textbox::SetFont(const sf::Font& font)
{
	m_Text.setFont(font);

	UpdateText();
}

void Textbox::SetFontSize(uint32_t fontSize)
{
	m_Text.SetFontSize(fontSize);
}

void Textbox::EraseLastChar()
{
	if(m_Text.getString().getSize() == 0)
		return;

	m_Text.setString(m_Text.getString().substring(0, m_Text.getString().getSize() - 1));

	UpdateText();
}

void Textbox::UpdateText()
{
	sf::FloatRect textRect = m_Text.getLocalBounds();

	m_Text.setOrigin(textRect.left + textRect.width / 2.0f,
					 textRect.top + textRect.height / 2.0f);
}

bool Textbox::Rectangle::IsRolledOn(const sf::RenderWindow& window) const
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	return getGlobalBounds().contains(sf::Vector2f(mousePos));
}

bool Textbox::Rectangle::IsClickedOn(const sf::RenderWindow& window, sf::Event e)
{
	if(IsRolledOn(window)) {
		if(e.type == sf::Event::MouseButtonPressed)
			return e.mouseButton.button == sf::Mouse::Left;
	}
	
	return false;
}

Textbox::Text::Text()
{
	setFillColor({ 255, 255, 255 });
	setOutlineColor({ 62, 62, 62 });
	setOutlineThickness(0.0f);
	setLetterSpacing(2.0f);
}

void Textbox::Text::SetFontSize(uint32_t fontSize)
{
	setCharacterSize(fontSize);
}
