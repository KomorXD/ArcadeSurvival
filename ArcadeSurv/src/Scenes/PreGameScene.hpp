#pragma once

#include "Scene.hpp"
#include "../UI/Textbox.hpp"

class PreGameScene : public Scene
{
	public:
		PreGameScene(const sf::Sprite& background);
		virtual ~PreGameScene();

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

		void HandleTextInput(sf::Event& e);

	private:
		void InputValidation();

		sf::Sprite m_Background;
		Textbox	   m_NameInputBox;

		bool m_IsNameValid = false;
};