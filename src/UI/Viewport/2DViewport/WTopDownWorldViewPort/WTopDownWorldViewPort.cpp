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

void WTopDownWorldViewPort::Tick(float deltaTime)
{
    WViewPort2D::Tick(deltaTime);
    vec2 renderSize = -topDownWorldRenderer->GetRenderedTexture().GetSize();
    topDownWorldRenderer->SetFrustumSize(vec2(GetDisplayedZoom()));
    vec2 offset = GetDisplayedOffset();
    vec2 offsetPosition = topDownWorldRenderer->GetPosition() ;
    //topDownWorldRenderer->SetPosition(offsetPosition);
    const auto frustumSize = topDownWorldRenderer->GetFrustumSize();
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

void WTopDownWorldViewPort::RenderUI()
{
    WViewPort2D::RenderUI();
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

void WTopDownWorldViewPort::ApplyPanning(const float x, const float y)
{
    vec2 position = topDownWorldRenderer->GetPosition();
    const auto windowSize = vec2(GetWindowSize().x, GetWindowSize().y);
    const auto panWorld =vec2(x,y)/windowSize;
    const vec2 worldPanning = panWorld * topDownWorldRenderer->GetFrustumSize();
    position -= worldPanning * vec2 (1,-1);
    return topDownWorldRenderer->SetPosition(position);
}
