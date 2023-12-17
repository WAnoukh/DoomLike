#pragma once
#include "UI/Viewport/2DViewport/WViewPort2D.h"

class TopDownWorldRenderer;

class WTopDownWorldViewPort : public WViewPort2D
{
public:
    WTopDownWorldViewPort() = default;
    WTopDownWorldViewPort(TopDownWorldRenderer& inTopDownWorldRenderer);
    ~WTopDownWorldViewPort() override = default;

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
