#pragma once

#include <list>

#include "InputManager.h"
#include "Window.h"
#include "Rendering/Renderer/WorldRenderer/GameRenderer.h"
#include "Rendering/Textures/Texture.h"
#include "Scene/World/Entities/PlayerController.h"

class WSimpleViewport;
class WWorldViewport;
class BasicRoom_WorldExemple;
class TopDownWorldRenderer;
class Renderer;
class UIWidget;
class Texture;

using namespace std;

class Application
{
public:
    Application(): Window(*this)
    {
    }

    static inline Application* instance = nullptr;

    static Application& GetInstance();

    void Init();
    
    int Run();

    unsigned int GetInitialScreenWidth() const { return INITIAL_SCR_WIDTH; };
    unsigned int GetInitialScreenHeight() const { return INITIAL_SCR_HEIGHT; };

    void framebufferSizeEvent();

    void AskForLayoutRefresh();

    void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset);

    void MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods);

    void MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos);

    void KeyboardKeyCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int key, int scancode, int action,
                                  int mods);

    InputManager& GetInputManager() { return inputManager; }

    //Texture Editing
    Texture& GetActiveTexture() { return activeTexture; }

    void AddWidget(UIWidget* widget);

private:
    static const unsigned int INITIAL_SCR_WIDTH = 1000;
    static const unsigned int INITIAL_SCR_HEIGHT = 1000;
    static const unsigned int TEXTURE_W = 1600;
    static const unsigned int TEXTURE_H = 1024;
    bool LayoutNeedRefresh = true;
    bool mouseRightPressed = false;
    Window Window;

    double lastX = 0.0f;
    double lastY = 0.0f;


    void Render();

    void Tick(float deltaTime);

    //Texture Editing
    Texture activeTexture;

    list<UIWidget*> UIWidgets = list<UIWidget*>();

    TopDownWorldRenderer* topDownWorldRenderer = nullptr;
    BasicRoom_WorldExemple* basicRoom_WorldExemple = nullptr;
    GameRenderer* gameRenderer = nullptr;
    WWorldViewport* topDownWorldViewPort = nullptr;
    WSimpleViewport* gameViewPort = nullptr;
    PlayerController playerController;
    InputManager inputManager;
};
