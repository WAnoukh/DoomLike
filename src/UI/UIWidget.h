#pragma once
#include "DLObject.h"
#include "Application/Window.h"

class UIWidget : public DLObject
{
public:
    virtual ~UIWidget() = default;
    
    virtual void RenderUI() = 0;

    virtual void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset) = 0;
    virtual void MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods) = 0;
    virtual void MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos) = 0;
};
