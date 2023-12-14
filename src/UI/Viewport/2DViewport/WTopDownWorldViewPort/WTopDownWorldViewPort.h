#pragma once
#include "UI/Viewport/2DViewport/WViewPort2D.h"

class TopDownWorldRenderer;

class WTopDownWorldViewPort : public WViewPort2D
{
public:
    WTopDownWorldViewPort() = default;
    WTopDownWorldViewPort(const TopDownWorldRenderer& inTopDownWorldRenderer);
    ~WTopDownWorldViewPort() override = default;

    //Getters
    const TopDownWorldRenderer* GetTopDownWorldRenderer() const;

    //Setters
    void SetTopDownWorldRenderer(const TopDownWorldRenderer* inTopDownWorldRenderer);

    void Init() override;

private:
    const TopDownWorldRenderer* topDownWorldRenderer = nullptr;
};
