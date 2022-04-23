#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Scene;

class Application
{
	public:
		void Run();

		sf::RenderWindow& GetWindow();
		void SetScene(Scene* scene);
		void SetWindowView(const sf::View& view);
		void CloseWindow();

		inline sf::Vector2u GetWindowSize() const { return m_Window.getSize(); }

		static void Init(uint32_t width, uint32_t height, const char* title);
		static void Destroy();
		
		static inline Application& GetInstance() { return *s_Instance; }

	private:
		Application(uint32_t width, uint32_t height, const char* title);
		~Application();
		
		sf::RenderWindow m_Window;
		Scene* m_Scene = nullptr;

		static inline Application* s_Instance;
};