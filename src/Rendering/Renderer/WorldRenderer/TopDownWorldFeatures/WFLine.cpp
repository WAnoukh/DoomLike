#include "WFLine.h"

#include <iostream>

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"

void WFLine::Draw(TopDownWorldRenderer* renderer)
{
    if(renderer == nullptr)
    {
        std::cerr << "WFLine::Draw : renderer is null" << std::endl;
        return;
    }
    renderer->DrawLine(start,end,color);
}

void WFLine::SetStart(glm::vec2 inStart)
{
    start = inStart;
}

void WFLine::SetEnd(glm::vec2 inEnd)
{
    end = inEnd;
}

void WFLine::SetPositions(glm::vec2 inStart, glm::vec2 inEnd)
{
    SetStart(inStart);
    SetEnd(inEnd);
}

void WFLine::SetColor(DLColor inColor)
{
    color = inColor;
}