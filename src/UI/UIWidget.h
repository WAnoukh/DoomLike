#pragma once
#include "Application/Window.h"

class UIWidget
{
public:
    virtual ~UIWidget() = default;

    virtual void Init() = 0;
    virtual void RenderUI() = 0;
    virtual void Tick(float DeltaTime) = 0;

    virtual void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset) = 0;
    virtual void MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods) = 0;
    virtual void MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos) = 0;
};
