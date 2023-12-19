#include "WWorldViewport.h"

#include <iostream>

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"

WWorldViewport::WWorldViewport(TopDownWorldRenderer& inTopDownWorldRenderer)
{
    SetTopDownWorldRenderer(&inTopDownWorldRenderer);
}

const TopDownWorldRenderer* WWorldViewport::GetTopDownWorldRenderer() const
{
    return topDownWorldRenderer;
}

void WWorldViewport::SetTopDownWorldRenderer(TopDownWorldRenderer* inTopDownWorldRenderer)
{
    topDownWorldRenderer = inTopDownWorldRenderer;
    if(topDownWorldRenderer)
    {
        SetViewPortTexture(topDownWorldRenderer->GetRenderedTexture().GetTextureId());
    }
}

void WWorldViewport::Init()
{
    WViewport2D::Init();
}

void WWorldViewport::Tick(float deltaTime)
{
    WViewport2D::Tick(deltaTime);
    topDownWorldRenderer->SetFrustumSize(vec2(GetDisplayedZoom()));
}

void WWorldViewport::RenderViewPort()
{
    if(topDownWorldRenderer == nullptr)
    {
        std::cerr << "WTopDownWorldViewPort::RenderViewPort : topDownWorldRenderer is nullptr" << std::endl;
        return;
    }
    topDownWorldRenderer->Render();
}

void WWorldViewport::RenderUI()
{
    WViewport2D::RenderUI();
    if(topDownWorldRenderer == nullptr)
    {
        std::cerr << "WTopDownWorldViewPort::RenderUI : topDownWorldRenderer is nullptr" << std::endl;
        return;
    }
    ImGui::Begin("TopDownWorldRenderer Settings");
    float frustumSize = GetDisplayedZoom();
    ImGui::InputFloat("frustrum", &frustumSize, 0.01f, 100);
    SetZoom(frustumSize);
    ImGui::End();
}

void WWorldViewport::ApplyPanning(const float x, const float y)
{
    vec2 position = topDownWorldRenderer->GetPosition();
    const auto windowSize = vec2(GetWindowSize().x, GetWindowSize().y);
    const auto panWorld =vec2(x,y)/windowSize;
    const vec2 worldPanning = panWorld * topDownWorldRenderer->GetFrustumSize();
    position -= worldPanning * vec2 (1,-1);
    return topDownWorldRenderer->SetPosition(position);
}
