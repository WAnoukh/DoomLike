#include "MinimapRenderer.h"

#include "Scene/World/World.h"
#include "TopDownWorldFeatures/WorldFeatures/WFEdge.h"

void MinimapRenderer::Render()
{
    Texture& texture = GetRenderedTexture();
    texture.Fill(DLColor::BLACK);
    TopDownWorldRenderer::Render();
}

void MinimapRenderer::SetWorldToRender(World* inViewedWorld)
{
    TopDownWorldRenderer::SetWorldToRender(inViewedWorld);
    CreateGridFeatures();
    CreateWorldFeatures();
    CreatePlayerFeature();
}



