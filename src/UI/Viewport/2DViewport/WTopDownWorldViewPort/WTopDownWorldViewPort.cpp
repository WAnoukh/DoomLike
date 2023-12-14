#include "WTopDownWorldViewPort.h"

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"

WTopDownWorldViewPort::WTopDownWorldViewPort(const TopDownWorldRenderer& inTopDownWorldRenderer)
{
    SetTopDownWorldRenderer(&inTopDownWorldRenderer);
}

const TopDownWorldRenderer* WTopDownWorldViewPort::GetTopDownWorldRenderer() const
{
    return topDownWorldRenderer;
}

void WTopDownWorldViewPort::SetTopDownWorldRenderer(const TopDownWorldRenderer* inTopDownWorldRenderer)
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
