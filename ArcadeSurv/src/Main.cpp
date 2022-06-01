#include "Application.hpp"
#include "Scenes/MainMenuScene.hpp"

#include <Windows.h>

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

    Application::Init(1600, 900, "lol");
    Application::GetInstance().PushScene(std::make_unique<MainMenuScene>());
    Application::GetInstance().Run();
    Application::Destroy();
    
    return 0;
}