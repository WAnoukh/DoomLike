#include "WFCircle.h"

#include <iostream>

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"

void WFCircle::Draw(TopDownWorldRenderer* renderer)
{
    if(renderer == nullptr)
    {
        std::cerr << "WFCircle::Draw : renderer is null" << std::endl;
        return;
    }
    renderer->DrawCircle(center,radius,color);
}

void WFCircle::SetCenter(glm::vec2 inCenter)
{
    center = inCenter;
}

void WFCircle::SetRadius(int inRadius)
{
    radius = inRadius;
}

void WFCircle::SetColor(DLColor inColor)
{
    color = inColor;
}