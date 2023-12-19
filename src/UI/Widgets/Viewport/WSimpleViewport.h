#pragma once
#include "WViewportBase.h"

class World;

class WSimpleViewport : public WViewportBase
{
public:
    WSimpleViewport(const char* name = "ViewportBase") : WViewportBase(name)
    {
    }
    ~WSimpleViewport() override = default;

    void Tick(float deltaTime) override;
    void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset) override;
    void MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods) override;
    void MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos) override;
    void Init() override;
    void RenderUI() override;
    void RenderViewPort() override;

    void SetRenderer(Renderer* inRenderer);

private:
    Renderer* renderer = nullptr;
};
