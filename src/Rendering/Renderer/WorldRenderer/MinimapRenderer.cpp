#include "MinimapRenderer.h"

#include <iostream>

#include "Rendering/Textures/TextureDrawer.h"
#include "Scene/World/World.h"
#include "Scene/World/WorldGeometry/Edge.h"
#include "TopDownWorldFeatures/WFEdge.h"
#include "TopDownWorldFeatures/WFLine.h"
#include "TopDownWorldFeatures/WFPlayer.h"
#include "TopDownWorldFeatures/WorldFeature.h"

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



