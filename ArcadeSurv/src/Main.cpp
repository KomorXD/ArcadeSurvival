#include "Application.hpp"
#include "Scenes/MainMenuScene.hpp"

int main()
{
    Application::Init(1280, 720, "lol");
    Application::GetInstance().PushScene(std::make_unique<MainMenuScene>());
    Application::GetInstance().Run();
    Application::Destroy();
    
    return 0;
}