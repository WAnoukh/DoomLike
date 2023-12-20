#include "TopDownWorldRenderer.h"

#include <iostream>
#include <list>

#include "Application/Application.h"
#include "Rendering/Color/DLColor.h"
#include "Rendering/Textures/Texture.h"
#include "Rendering/Textures/TextureDrawer.h"
#include "Scene/World/World.h"
#include "Scene/World/Rays/Ray.h"
#include "Scene/World/WorldGeometry/Edge.h"
#include "TopDownWorldFeatures/WFEdge.h"
#include "TopDownWorldFeatures/WFLine.h"
#include "TopDownWorldFeatures/WFPlayer.h"
#include "TopDownWorldFeatures/WorldFeature.h"

void TopDownWorldRenderer::Init()
{
    WorldRendererBase::Init();
    GetRenderedTexture().CreateBlankTexture(128, 128, GL_RGB);
}

vec2 TopDownWorldRenderer::GetPosition() const
{
    return position;
}

vec2 TopDownWorldRenderer::GetFrustumSize() const
{
    return frustumSize;
}

float TopDownWorldRenderer::GetRotation() const
{
    return rotation;
}

void TopDownWorldRenderer::SetPosition(vec2 inPosition)
{
    position = inPosition;
}

void TopDownWorldRenderer::SetFrustumSize(vec2 inFrustumSize)
{
    if (inFrustumSize.x <= 0 || inFrustumSize.y <= 0)
    {
        std::cerr << "TopDownWorldRenderer::SetFrustumSize : Frustum size must be strictly positive" << std::endl;
        return;
    }
    frustumSize = inFrustumSize;
}

void TopDownWorldRenderer::SetRotation(float inRotation)
{
    rotation = inRotation;
}

void TopDownWorldRenderer::Render()
{
    /*
    texture.Fill(DLColor::BLACK);
    DrawCoordinateSystem(vec2(0.5f, 0.5f));
    DrawGrid();
    DrawEdges(true);
    DrawPlayer();
    Entity& player = GetWorldToRender()->GetPlayer();
    auto ray = Ray(player.GetPosition(), player.GetRotation());
    HitResult hitResult;
    if (GetWorldToRender()->RayCastOnEdges(ray, hitResult, true))
    {
        TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
        textureDrawer.SetBindTexture(&GetRenderedTexture());
        textureDrawer.DrawCircle(WorldSpaceToScreenSpace(hitResult.point), 3, DLColor::GREEN);
    }
    */
    Texture& texture = GetRenderedTexture();
    DrawWorldFeatures();
    texture.SendDataToOpenGl();
}

void TopDownWorldRenderer::DrawWorldFeatures()
{
    for (WorldFeature* feature : worldFeatures)
    {
        feature->Draw(this);
    }
}

void TopDownWorldRenderer::DrawPlayer()
{
    World* world = GetWorldToRender();
    if (world == nullptr)
    {
        std::cerr << "TopDownWorldRenderer::DrawPlayer : World to render is null" << std::endl;
        return;
    }
    const Entity& player = world->GetPlayer();
    const vec2 playerPosition = player.GetPosition();
    const ivec2 playerScreenPosition = WorldSpaceToScreenSpace(playerPosition);
    TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
    textureDrawer.SetBindTexture(&GetRenderedTexture());
    textureDrawer.DrawLine(playerScreenPosition, player.GetRotation(), 10, DLColor::YELLOW);
    textureDrawer.DrawCircle(playerScreenPosition, 4, DLColor::RED);
}

void TopDownWorldRenderer::DrawEdges(bool drawEdges)
{
    World* world = GetWorldToRender();
    if (world == nullptr)
    {
        std::cerr << "TopDownWorldRenderer::DrawEdges : World to render is null" << std::endl;
        return;
    }
    const std::list<Edge*>& edges = world->GetEdges();
    for (const Edge* edge : edges)
    {
        const vec2 start = edge->GetStart();
        const vec2 end = edge->GetEnd();
        TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
        textureDrawer.SetBindTexture(&GetRenderedTexture());
        DrawLine(start, end, DLColor::WHITE);
        if (drawEdges)
        {
            DrawCircle(start, 3, DLColor::BLUE);
            DrawCircle(end, 3, DLColor::BLUE);
        }
    }
}

void TopDownWorldRenderer::DrawGrid()
{
    TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
    textureDrawer.SetBindTexture(&GetRenderedTexture());
    for (int i = -50; i < 50; ++i)
    {
        DLColor color = DLColor(0.2f);
        DrawLine(vec2(i, -50), vec2(i, 50), color);
        DrawLine(vec2(-50, i), vec2(50, i), color);
    }
}

void TopDownWorldRenderer::DrawCoordinateSystem(vec2 InPosition)
{
    TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
    textureDrawer.SetBindTexture(&GetRenderedTexture());
    DrawLine(InPosition, InPosition + vec2(1, 0), DLColor::RED);
    DrawLine(InPosition, InPosition + vec2(0, 1), DLColor::GREEN);
}

void TopDownWorldRenderer::DrawLine(vec2 startWorld, vec2 endWorld, DLColor color)
{
    TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
    textureDrawer.SetBindTexture(&GetRenderedTexture());
    textureDrawer.DrawLine(WorldSpaceToScreenSpace(startWorld), WorldSpaceToScreenSpace(endWorld), color);
}

void TopDownWorldRenderer::DrawLine(vec2 startWorld, float angle, float length, DLColor color)
{
    TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
    textureDrawer.SetBindTexture(&GetRenderedTexture());
    textureDrawer.DrawLine(WorldSpaceToScreenSpace(startWorld), angle, length, color);
}

void TopDownWorldRenderer::DrawCircle(vec2 centerWorld, int radius, DLColor color)
{
    vec2 centerScreen = WorldSpaceToScreenSpace(centerWorld);
    TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
    textureDrawer.SetBindTexture(&GetRenderedTexture());
    textureDrawer.DrawCircle(centerScreen, radius, color);
}

void TopDownWorldRenderer::CreateWorldFeatures()
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

void TopDownWorldRenderer::CreateGridFeatures()
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

void TopDownWorldRenderer::CreatePlayerFeature()
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

vec2 TopDownWorldRenderer::WorldSpaceToScreenSpace(vec2 inPosition) const
{
    vec2 screenSpacePosition = inPosition - position;
    const auto textureSize = vec2(GetRenderHeight(), GetRenderWidth());
    screenSpacePosition = (screenSpacePosition / (frustumSize) + vec2(0.5f)) * textureSize;
    return screenSpacePosition;
}

vec2 TopDownWorldRenderer::ScreenSpaceToWorldSpace(vec2 inPosition) const
{
    const auto textureSize = vec2(GetRenderHeight(), GetRenderWidth());
    vec2 screenSpacePosition = (inPosition / textureSize - vec2(0.5f)) * frustumSize;
    screenSpacePosition += position;
    return screenSpacePosition;
}

vec2 TopDownWorldRenderer::ScreenDeltaToWorldDelta(vec2 inDelta) const
{
    const auto textureSize = vec2(GetRenderHeight(), GetRenderWidth());
    vec2 screenSpaceDelta = (inDelta / textureSize) * frustumSize;
    return screenSpaceDelta;
}

const list<WorldFeature*>& TopDownWorldRenderer::GetWorldFeatures()
{
    return worldFeatures;
}

void TopDownWorldRenderer::AddWorldFeature(WorldFeature* worldFeature)
{
    worldFeatures.push_back(worldFeature);
}
