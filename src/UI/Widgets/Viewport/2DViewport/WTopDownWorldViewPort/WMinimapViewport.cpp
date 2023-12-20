#include "WMinimapViewport.h"

#include <iostream>

#include "Rendering/Renderer/WorldRenderer/MinimapRenderer.h"
#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"

WMinimapViewport::WMinimapViewport(MinimapRenderer& inMinimapRenderer)
{
    SetMinimapRenderer(&inMinimapRenderer);
}

const MinimapRenderer* WMinimapViewport::GetMinimapRenderer() const
{
    return minimapRenderer;
}

void WMinimapViewport::SetMinimapRenderer(MinimapRenderer* inMinimapRenderer)
{
    minimapRenderer = inMinimapRenderer;
    if(minimapRenderer)
    {
        SetViewPortTexture(minimapRenderer->GetRenderedTexture().GetTextureId());
    }
}

void WMinimapViewport::Init()
{
    WViewport2D::Init();
}

void WMinimapViewport::Tick(float deltaTime)
{
    WViewport2D::Tick(deltaTime);
    minimapRenderer->SetFrustumSize(vec2(GetDisplayedZoom()));
}

void WMinimapViewport::RenderViewPort()
{
    if(minimapRenderer == nullptr)
    {
        std::cerr << "WTopDownWorldViewPort::RenderViewPort : topDownWorldRenderer is nullptr" << std::endl;
        return;
    }
    minimapRenderer->Render();
}

void WMinimapViewport::RenderUI()
{
    WViewport2D::RenderUI();
    if(minimapRenderer == nullptr)
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

void WMinimapViewport::ApplyPanning(const float x, const float y)
{
    vec2 position = minimapRenderer->GetPosition();
    const auto windowSize = vec2(GetWindowSize().x, GetWindowSize().y);
    const auto panWorld =vec2(x,y)/windowSize;
    const vec2 worldPanning = panWorld * minimapRenderer->GetFrustumSize();
    position -= worldPanning * vec2 (1,-1);
    return minimapRenderer->SetPosition(position);
}
