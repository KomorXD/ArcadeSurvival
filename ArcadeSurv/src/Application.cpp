#include "Application.hpp"

#include "Scenes/GameScene.hpp"

void Application::Run()
{
	sf::Clock timer;
	sf::Event ev;
	float	  dt = 1.0f / 30.0f;

	while(m_Window.isOpen())
	{
		while(m_Window.pollEvent(ev))
		{
			m_Scene->HandleEvents(ev);

			if(ev.type == sf::Event::Closed)
				m_Window.close();
		}

		m_Window.clear({ 66, 66, 66 });

		m_Scene->HandleInput(dt);
		m_Scene->Update(dt);
		m_Scene->Render(m_Window);

		m_Window.display();

		dt = std::min(timer.restart().asSeconds(), 1.0f / 30.0f);
	}
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

void Application::SetScene(Scene* scene)
{
	m_Scene = scene;
}

void Application::SetWindowView(const sf::View& view)
{
	m_Window.setView(view);
}

void Application::Destroy()
{
	if(s_Instance)
		delete s_Instance;
}

Application::Application(uint32_t width, uint32_t height, const char* title)
	: m_Window({ width, height }, title, sf::Style::Titlebar | sf::Style::Close)
{
	// m_Window.setFramerateLimit(60);
}

Application::~Application()
{
	delete m_Scene;
}
