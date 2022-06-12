#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <stack>

struct Stats
{
	int32_t waveNo;
	int32_t enemiesOnWave;
	float	timeAlive;
};

class Scene;

class Application
{
	public:
		void Run();

		void PushScene(std::unique_ptr<Scene>&& scene);
		void ChangeScene(std::unique_ptr<Scene>&& scene);
		void PopScene();

		void SetUsername(const std::string& name);
		void SaveStats(Stats stats);

		sf::RenderWindow& GetWindow();

		void SetWindowView(const sf::View& view);
		void CloseWindow();

		inline sf::Vector2u GetWindowSize() const { return m_Window.getSize(); }

		static void Init(uint32_t width, uint32_t height, const char* title);
		static void Destroy();
		
		static inline Application& GetInstance() { return *s_Instance; }

	private:
		Application(uint32_t width, uint32_t height, const char* title);
		~Application();
		
		sf::RenderWindow  m_Window;
		std::stack<std::unique_ptr<Scene>> m_Scenes;

		std::string m_PlayerName;

		static inline Application* s_Instance;
};