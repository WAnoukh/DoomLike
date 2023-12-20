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

void MinimapRenderer::CreateWorldFeatures()
{
    World* world = GetWorldToRender();
    if (world == nullptr)
    {
        return;
    }
    for (Edge* edge : world->GetEdges())
    {
        WFEdge* wfEdge = new WFEdge();
        wfEdge->SetEdge(edge);
        AddWorldFeature(wfEdge);
    }
}

void MinimapRenderer::CreateGridFeatures()
{
    for (int i = -50; i < 50; ++i)
    {

        WFLine* line = new WFLine(vec2(i, -50), vec2(i, 50));
        WFLine* line2 = new WFLine(vec2(-50, i), vec2(50, i));
        line->SetColor(DLColor::WHITE * 0.2f);
        line2->SetColor(DLColor::WHITE * 0.2f);
        AddWorldFeature(line);
        AddWorldFeature(line2);
    }
}

void MinimapRenderer::CreatePlayerFeature()
{
    World* world = GetWorldToRender();
    if (world == nullptr)
    {
        std::cerr << "MinimapRenderer::CreatePlayerFeature : world is null" << std::endl;
        return;
    }
    Entity& player = world->GetPlayer();
    WFPlayer* wfPlayer = new WFPlayer(&player);
    AddWorldFeature(wfPlayer);
}



