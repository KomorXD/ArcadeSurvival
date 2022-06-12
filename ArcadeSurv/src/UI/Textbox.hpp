#pragma once

#include <SFML/Graphics.hpp>

class Textbox
{
	public:
		Textbox() = default;
		Textbox(const sf::Vector2f& size, const std::string& text = "");
		virtual ~Textbox() = default;
		
		virtual bool HandleEvents(sf::RenderWindow& window, sf::Event e);
		virtual void Render(sf::RenderTarget& renderer);

		virtual void SetPosition(const sf::Vector2f& pos);
		virtual void SetText(const std::string& text);
		virtual void AppendChar(char c);
		virtual void SetSize(const sf::Vector2f& size);
		virtual void SetTexture(sf::Texture* texture);
		virtual void SetColor(const sf::Color& color);
		virtual void SetTextColor(const sf::Color& color);
		virtual void SetFont(const sf::Font& font);
		virtual void SetFontSize(uint32_t fontSize);

		virtual void EraseLastChar();

		virtual inline sf::Vector2f GetPosition() const { return m_Body.getPosition(); }
		virtual inline sf::Vector2f GetSize() const { return m_Body.getSize(); }
		virtual inline std::string GetString() const { return m_Text.getString(); }

	protected:
		class Rectangle : public sf::RectangleShape
		{
			public:
				bool IsRolledOn(const sf::RenderWindow& window) const;
				bool IsClickedOn(const sf::RenderWindow& window, sf::Event e);
		};

		class Text : public sf::Text
		{
			public:
				Text();

				void SetFontSize(uint32_t fontSize);
		};

		virtual void UpdateText();

		Rectangle m_Body;
		Text	  m_Text;
};