#include "Application.hpp"
#include "Scenes/GameScene.hpp"

#include <filesystem>
#include <fstream>

void Application::Run()
{
	sf::Clock timer;
	sf::Event ev;
	float	  dt = 1.0f / 30.0f;

	while(m_Window.isOpen())
	{
		while(m_Window.pollEvent(ev))
		{
			m_Scenes.top()->HandleEvents(ev);

			if(ev.type == sf::Event::Closed)
				m_Window.close();
		}

		m_Window.clear({ 66, 66, 66 });

		m_Scenes.top()->HandleInput(dt);
		m_Scenes.top()->Update(dt);
		m_Scenes.top()->Render(m_Window);

		m_Window.display();

		dt = std::min(timer.restart().asSeconds(), 1.0f / 30.0f);
	}
}

void Application::PushScene(std::unique_ptr<Scene>&& scene)
{
	m_Scenes.push(std::move(scene));
}

void Application::ChangeScene(std::unique_ptr<Scene>&& scene)
{
	PopScene();
	m_Scenes.push(std::move(scene));
}

void Application::PopScene()
{
	if(!m_Scenes.empty())
		m_Scenes.pop();
}

void Application::SetUsername(const std::string& name)
{
	m_PlayerName = name;
}

void Application::SaveStats(Stats stats)
{
	std::filesystem::path cwd = std::filesystem::current_path().append("scores.dat");
	std::ofstream scoresFile(cwd.string().c_str(), std::ios::binary | std::ios::app);

	scoresFile.write((char*)m_PlayerName.c_str(), sizeof(char) * 16);
	scoresFile.write((char*)&stats.waveNo,		  sizeof(int32_t));
	scoresFile.write((char*)&stats.enemiesOnWave, sizeof(int32_t));
	scoresFile.write((char*)&stats.timeAlive,	  sizeof(float));

	scoresFile.close();
}

sf::RenderWindow& Application::GetWindow()
{
	return m_Window;
}

void Application::Init(uint32_t width, uint32_t height, const char* title)
{
	if(s_Instance)
		return;

	s_Instance = new Application(width, height, title);
}

void Application::SetWindowView(const sf::View& view)
{
	m_Window.setView(view);
}

void Application::CloseWindow()
{
	m_Window.close();
}

void Application::Destroy()
{
	if(s_Instance)
		delete s_Instance;
}

Application::Application(uint32_t width, uint32_t height, const char* title)
	: m_Window({ width, height }, title, sf::Style::Titlebar | sf::Style::Close)
{
	m_Window.setFramerateLimit(60);
}

Application::~Application()
{
	while(!m_Scenes.empty())
		m_Scenes.pop();
}
