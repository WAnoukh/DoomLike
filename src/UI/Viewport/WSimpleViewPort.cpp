#include "WSimpleViewPort.h"

#include <iostream>

#include "Rendering/Renderer/Renderer.h"

void WSimpleViewPort::Tick(float deltaTime)
{
}

void WSimpleViewPort::ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset)
{
}

void WSimpleViewPort::MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action,
    int mods)
{
}

void WSimpleViewPort::MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos)
{
}

void WSimpleViewPort::Init()
{
    WViewPortBase::Init();
}

void WSimpleViewPort::RenderUI()
{
    WViewPortBase::RenderUI();
}

void WSimpleViewPort::RenderViewPort()
{
    if(renderer == nullptr)
    {
        std::cerr << "WTopDownWorldViewPort::RenderViewPort : topDownWorldRenderer is nullptr" << std::endl;
        return;
    }
    renderer->Render();
}

void WSimpleViewPort::SetRenderer(Renderer* inRenderer)
{
    renderer = inRenderer;
    if(renderer)
    {
        SetViewPortTexture(renderer->GetRenderedTexture().GetTextureId());
    }
}
