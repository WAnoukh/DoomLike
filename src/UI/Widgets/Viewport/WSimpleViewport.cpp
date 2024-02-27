#include "WSimpleViewport.h"

#include <iostream>

#include "Rendering/Renderer/Renderer.h"

void WSimpleViewport::Tick(float deltaTime)
{
}

void WSimpleViewport::ScrollCallBackEvent(bool guiWantToCapture, double xOffset, double yOffset)
{
}

void WSimpleViewport::MouseButtonCallBackEvent(bool guiWantToCapture, int button, int action,
                                               int mods)
{
}

void WSimpleViewport::MousePositionCallBackEvent(bool guiWantToCapture, double xPos, double yPos)
{
}

void WSimpleViewport::Init()
{
    WViewportBase::Init();
}

void WSimpleViewport::RenderUI()
{
    WViewportBase::RenderUI();
}

void WSimpleViewport::RenderViewPort()
{
    if(renderer == nullptr)
    {
        std::cerr << "WTopDownWorldViewPort::RenderViewPort : topDownWorldRenderer is nullptr" << std::endl;
        return;
    }
    renderer->Render();
}

void WSimpleViewport::SetRenderer(Renderer* inRenderer)
{
    renderer = inRenderer;
    if(renderer)
    {
        SetViewPortTexture(renderer->GetRenderedTexture().GetTextureId());
    }
}
