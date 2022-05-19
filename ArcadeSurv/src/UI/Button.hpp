#pragma once

#include "Textbox.hpp"

#include <functional>

class Button : public Textbox
{
	public:
		Button(const sf::Vector2f& size, const std::string& text = "");
		virtual ~Button() = default;

		virtual bool HandleEvents(sf::RenderWindow & window, sf::Event e) override;

		void SetFunction(std::function<void(void)> f);

	private:
		std::function<void(void)> m_TriggerFunc;
};