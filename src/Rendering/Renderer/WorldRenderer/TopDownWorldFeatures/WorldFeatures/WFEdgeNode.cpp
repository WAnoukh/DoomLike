#include "WFEdgeNode.h"

#include <iostream>

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"
#include "UI/Tools/WorldEditor/TWallNode.h"

void WFEdgeNode::Draw(TopDownWorldRenderer* renderer)
{
    if(renderer == nullptr)
    {
        std::cerr << "WFEdgeNode::Draw : renderer is null" << std::endl;
        return;
    }
    
    if(edgeNode == nullptr)
    {
        std::cerr << "WFEdgeNode::Draw : edgeNode is null" << std::endl;
        return;
    }
    vec2 start, end;
    if(!edgeNode->TryGetPosition(start))
    {
        std::cerr << "WFEdgeNode::Draw : edgeNode->TryGetPosition failed" << std::endl;
        return;
    }
    renderer->DrawCircle(start, 5, nodeColor);
    
    for(auto neighbor : neighbors)
    {
        if(neighbor == nullptr)
        {
            std::cerr << "WFEdgeNode::Draw : neighbor is null" << std::endl;
            continue;
        }
        if(neighbor->edgeNode->TryGetPosition(end))
        {
            //ToDo: draw line
            //renderer->DrawLine(start,end,edgeColor);
        }
    }
}

void WFEdgeNode::SetEdgeNode(TEdgeNode* inEdgeNode)
{
    edgeNode = inEdgeNode;
}

void WFEdgeNode::SetEdgeColor(DLColor inEdgeColor)
{
    edgeColor = inEdgeColor;
}

void WFEdgeNode::SetNodeColor(DLColor inNodeColor)
{
    nodeColor = inNodeColor;
}

void WFEdgeNode::AddNeighbor(WFEdgeNode* neighbor)
{
    neighbors.insert(neighbor);
}
