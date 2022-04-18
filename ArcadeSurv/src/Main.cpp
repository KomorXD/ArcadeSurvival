#include "Application.hpp"
#include "Scenes/GameScene.hpp"

int main()
{
    Application::Init(1280, 720, "lol");
    Application::GetInstance().SetScene(new GameScene());
    Application::GetInstance().Run();
    Application::Destroy();
    
    return 0;
}