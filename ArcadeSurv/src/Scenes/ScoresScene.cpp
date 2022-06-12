#include "ScoresScene.hpp"
#include "../Application.hpp"
#include "../Utils/Resources.hpp"

#include <filesystem>
#include <fstream>

ScoresScene::ScoresScene(const sf::Sprite& background)
	: m_Background(background)
{
	m_Background.setColor({ 66, 66, 66 });

	std::filesystem::path scoresDir = std::filesystem::current_path().append("scores.dat");
	std::ifstream scoresFile(scoresDir.string().c_str(), std::ios::binary);

	if(!scoresFile)
		return;
	
	struct ScoreRecord
	{
		char	name[16];
		int32_t	waveNo;
		int32_t	enemiesOnWave;
		float	timeAlive;
	} prot;

	std::vector<ScoreRecord> temp;

	while(scoresFile.read((char*)&prot, sizeof(ScoreRecord)))
		temp.push_back(prot);

	std::ranges::sort(temp, std::ranges::greater{}, &ScoreRecord::waveNo);

	ScoreRecordToRender protToo;
	
	if(sf::Font* font = Resources::Get().GetFont("IBMPlexMonoRegular"))
	{
		protToo.playerName.SetFont(*font);
		protToo.waveNo.SetFont(*font);
		protToo.enemiesOnWave.SetFont(*font);
		protToo.timeAlive.SetFont(*font);
	}

	protToo.playerName.SetText("PLAYER NAME");
	protToo.waveNo.SetText("WAVE NO.");
	protToo.enemiesOnWave.SetText("ENEMIES LEFT");
	protToo.timeAlive.SetText("TIME ALIVE [s]");

	PrepareRecord(protToo, 1);

	m_Records.push_back(protToo);

	for(size_t i = 0; i < temp.size() && i < 10; ++i)
	{
		ScoreRecord& rec = temp[i];

		protToo.playerName.SetText(rec.name);
		protToo.waveNo.SetText(std::to_string(rec.waveNo));
		protToo.enemiesOnWave.SetText(std::to_string(rec.enemiesOnWave));
		protToo.timeAlive.SetText(std::to_string(rec.timeAlive));

		PrepareRecord(protToo, static_cast<int32_t>(i + 2));

		m_Records.push_back(protToo);
	}
}

ScoresScene::~ScoresScene()
{}

void ScoresScene::HandleEvents(sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
		Application::GetInstance().PopScene();
}

void ScoresScene::HandleInput(float dt)
{}

void ScoresScene::Update(float dt)
{}

void ScoresScene::Render(sf::RenderTarget& renderer)
{
	renderer.draw(m_Background);

	for(size_t i = 0; i < m_Records.size() && i < 10; ++i)
		RenderRecord(renderer, m_Records[i]);
}

void ScoresScene::PrepareRecord(ScoreRecordToRender& record, int32_t row)
{
	sf::Vector2f windowSize = sf::Vector2f(Application::GetInstance().GetWindowSize());

	record.playerName.SetSize({ 128.0f, 64.0f });
	record.playerName.SetColor({ 0, 0, 0, 0 });

	record.waveNo.SetSize({ 128.0f, 64.0f });
	record.waveNo.SetColor({ 0, 0, 0, 0 });

	record.enemiesOnWave.SetSize({ 128.0f, 64.0f });
	record.enemiesOnWave.SetColor({ 0, 0, 0, 0 });

	record.timeAlive.SetSize({ 128.0f, 64.0f });
	record.timeAlive.SetColor({ 0, 0, 0, 0 });

	record.playerName.SetPosition({ 1.0f / 6.0f * windowSize.x, (row / 10.0f) * windowSize.y });
	record.waveNo.SetPosition({ 2.3f / 6.0f * windowSize.x, (row / 10.0f) * windowSize.y });
	record.enemiesOnWave.SetPosition({ 3.7f / 6.0f * windowSize.x, (row / 10.0f) * windowSize.y });
	record.timeAlive.SetPosition({ 5.0f / 6.0f * windowSize.x, (row / 10.0f) * windowSize.y });
}

void ScoresScene::RenderRecord(sf::RenderTarget& renderer, ScoreRecordToRender& record)
{
	record.playerName.Render(renderer);
	record.waveNo.Render(renderer);
	record.enemiesOnWave.Render(renderer);
	record.timeAlive.Render(renderer);
}
