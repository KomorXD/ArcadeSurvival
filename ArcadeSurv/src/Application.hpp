#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Scene;

class Application
{
	public:
		void Run();

		sf::RenderWindow& GetWindow();
		void SetScene(Scene* scene);

		static void Init(uint32_t width, uint32_t height, const char* title);
		static void Destroy();
		
		static inline Application& GetInstance() { return *s_Instance; }

	private:
		Application(uint32_t width, uint32_t height, const char* title);
		~Application();
		
		sf::RenderWindow m_Window;
		Scene* m_Scene;

		static inline Application* s_Instance;
};