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

    void RenderViewPort() override;

private:
    TopDownWorldRenderer* topDownWorldRenderer = nullptr;
};
