#pragma once

#include "Scene.hpp"
#include "../UI/Textbox.hpp"

class ScoresScene : public Scene
{
	public:
		ScoresScene(const sf::Sprite& background);
		virtual ~ScoresScene();

		virtual void HandleEvents(sf::Event& e)			override;
		virtual void HandleInput(float dt)				override;
		virtual void Update(float dt)					override;
		virtual void Render(sf::RenderTarget& renderer) override;

	private:
		struct ScoreRecordToRender
		{
			Textbox playerName;
			Textbox waveNo;
			Textbox enemiesOnWave;
			Textbox timeAlive;
		};

		void PrepareRecord(ScoreRecordToRender& record, int32_t row);
		void RenderRecord(sf::RenderTarget& renderer, ScoreRecordToRender& record);

		sf::Sprite m_Background;
		std::vector<ScoreRecordToRender> m_Records;
};