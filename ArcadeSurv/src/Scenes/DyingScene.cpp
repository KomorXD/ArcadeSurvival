#include "DyingScene.hpp"
#include "GameOverScene.hpp"
#include "../Application.hpp"

DyingScene::DyingScene(std::shared_ptr<sf::RenderTexture>& lastFrameRenderTexture, std::shared_ptr<PlayerEntity>& player)
	: m_LastFrameRenderTexture(lastFrameRenderTexture), m_LastFrameSnapshot(lastFrameRenderTexture->getTexture()), m_Player(player)
{
	sf::Vector2i textSize = sf::Vector2i(m_LastFrameSnapshot.getTexture()->getSize());

	m_LastFrameSnapshot.setTextureRect({ 0, textSize.y, textSize.x, -textSize.y });
}

void DyingScene::HandleEvents(sf::Event& e)
{
	;
}

void DyingScene::HandleInput(float dt)
{
	;
}

void DyingScene::Update(float dt)
{
	if(m_DyingTime >= 2.0f)
	{
		Application::GetInstance().ChangeScene(std::make_unique<GameOverScene>(m_LastFrameRenderTexture, m_Player));

		return;
	}

	float currRatio = m_DyingTime / 2.0f;
	int8_t currVal = static_cast<int8_t>(200 * currRatio);
	sf::Color currTextColor = m_LastFrameSnapshot.getColor();

	uint8_t newR = 255 - currVal;
	uint8_t newG = 255 - currVal;
	uint8_t newB = 255 - currVal;

	m_LastFrameSnapshot.setColor({ newR, newG, newB });

	m_DyingTime += dt;
}

void DyingScene::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_LastFrameSnapshot);
	m_Player->Render(renderer);
}
