#pragma once
#include "TopDownWorldRenderer.h"
#include "TopDownWorldFeatures/WorldFeature.h"

class Edge;

class MinimapRenderer : public TopDownWorldRenderer
{
public:

    void Render() override;

    void SetWorldToRender(World* inViewedWorld) override;
};

