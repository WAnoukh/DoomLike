#include "WTopDownWorldViewPort.h"

#include <iostream>

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"

WTopDownWorldViewPort::WTopDownWorldViewPort(TopDownWorldRenderer& inTopDownWorldRenderer)
{
    SetTopDownWorldRenderer(&inTopDownWorldRenderer);
}

const TopDownWorldRenderer* WTopDownWorldViewPort::GetTopDownWorldRenderer() const
{
    return topDownWorldRenderer;
}

void WTopDownWorldViewPort::SetTopDownWorldRenderer(TopDownWorldRenderer* inTopDownWorldRenderer)
{
    topDownWorldRenderer = inTopDownWorldRenderer;
    if(topDownWorldRenderer)
    {
        SetViewPortTexture(topDownWorldRenderer->GetRenderedTexture().GetTextureId());
    }
}

void WTopDownWorldViewPort::Init()
{
    WViewPort2D::Init();
}

void WTopDownWorldViewPort::RenderViewPort()
{
    if(topDownWorldRenderer == nullptr)
    {
        std::cerr << "WTopDownWorldViewPort::RenderViewPort : topDownWorldRenderer is nullptr" << std::endl;
        return;
    }
    topDownWorldRenderer->Render();
    SetViewPortTexture(topDownWorldRenderer->GetRenderedTexture().GetTextureId());
}
