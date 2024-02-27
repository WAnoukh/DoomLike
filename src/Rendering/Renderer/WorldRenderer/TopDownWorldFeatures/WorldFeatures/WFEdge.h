#pragma once
#include "Rendering/Renderer/WorldRenderer/TopDownWorldFeatures/WorldFeature.h"
#include "Rendering/Color/DLColor.h"

class Edge;

class WFEdge : public WorldFeature
{
public:
    ~WFEdge() override = default;

    void Draw(TopDownWorldRenderer* renderer) override;
    

    void SetEdge(Edge* inEdge);
    void SetLineColor(DLColor inLineColor);

private:
    Edge* edge = nullptr;
    DLColor LineColor = DLColor::WHITE;
};
