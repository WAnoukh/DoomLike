#pragma once
#include "UI/Widgets/Viewport/2DViewport/WViewport2D.h"

class MinimapRenderer;
class TopDownWorldRenderer;

class WMinimapViewport : public WViewport2D
{
public:
    WMinimapViewport() = default;
    WMinimapViewport(MinimapRenderer& inMinimapRenderer);
    ~WMinimapViewport() override = default;

    //Getters
    const MinimapRenderer* GetMinimapRenderer() const;

    //Setters
    void SetMinimapRenderer(MinimapRenderer* inMinimapRenderer);

    void Init() override;

    void Tick(float deltaTime) override;

    void RenderViewPort() override;

    void RenderUI() override;

    void ApplyPanning(const float x, const float y) override;

private:
    MinimapRenderer* minimapRenderer = nullptr;
};
