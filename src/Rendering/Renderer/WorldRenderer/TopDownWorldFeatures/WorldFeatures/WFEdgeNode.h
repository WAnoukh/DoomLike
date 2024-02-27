#pragma once
#include <set>

#include "Rendering/Color/DLColor.h"
#include "Rendering/Renderer/WorldRenderer/TopDownWorldFeatures/WorldFeature.h"

class TEdgeNode;

class WFEdgeNode : public WorldFeature
{
public:

    void Draw(TopDownWorldRenderer* renderer) override;
    
    void SetEdgeNode(TEdgeNode* inEdgeNode);
    void SetEdgeColor(DLColor inEdgeColor);
    void SetNodeColor(DLColor inNodeColor);

    void AddNeighbor(WFEdgeNode* neighbor);

private:
    TEdgeNode* edgeNode = nullptr;
    std::set<WFEdgeNode*> neighbors;
    DLColor edgeColor = DLColor::WHITE;
    DLColor nodeColor = DLColor::BLUE;
};
