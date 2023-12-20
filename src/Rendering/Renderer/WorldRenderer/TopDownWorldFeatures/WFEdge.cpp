#include "WFEdge.h"

#include <iostream>

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"
#include "Rendering/Textures/TextureDrawer.h"
#include "Scene/World/WorldGeometry/Edge.h"

void WFEdge::Draw(TopDownWorldRenderer* renderer)
{
    if(renderer == nullptr)
    {
        std::cerr << "WFEdge::Draw : renderer is nullptr" << std::endl;
        return;
    }
    if(edge == nullptr)
    {
        std::cerr << "WFEdge::Draw : edge is nullptr" << std::endl;
        return;
    }
    renderer->DrawLine(edge->GetStart(),edge->GetEnd(),LineColor);
}

void WFEdge::SetEdge(Edge* inEdge)
{
    edge = inEdge;
}

void WFEdge::SetLineColor(DLColor inLineColor)
{
    LineColor = inLineColor;
}