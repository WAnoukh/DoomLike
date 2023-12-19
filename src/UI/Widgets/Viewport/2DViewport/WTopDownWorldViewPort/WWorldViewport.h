#pragma once
#include "UI/Widgets/Viewport/2DViewport/WViewport2D.h"

class TopDownWorldRenderer;

class WWorldViewport : public WViewport2D
{
public:
    WWorldViewport() = default;
    WWorldViewport(TopDownWorldRenderer& inTopDownWorldRenderer);
    ~WWorldViewport() override = default;

    //Getters
    const TopDownWorldRenderer* GetTopDownWorldRenderer() const;

    //Setters
    void SetTopDownWorldRenderer(TopDownWorldRenderer* inTopDownWorldRenderer);

    void Init() override;

    void Tick(float deltaTime) override;

    void RenderViewPort() override;

    void RenderUI() override;

    void ApplyPanning(const float x, const float y) override;

private:
    TopDownWorldRenderer* topDownWorldRenderer = nullptr;
};
