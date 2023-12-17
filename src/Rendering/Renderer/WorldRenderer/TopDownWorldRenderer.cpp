#include "TopDownWorldRenderer.h"

#include <iostream>
#include <list>

#include "Rendering/Color/DLColor.h"
#include "Rendering/Textures/Texture.h"
#include "Rendering/Textures/TextureDrawer.h"
#include "Rendering/Color/DLColor.h"

void TopDownWorldRenderer::Init()
{
    GetRenderedTexture().CreateBlankTexture(128,128, GL_RGB);
    WorldRendererBase::Init();
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
    if(inFrustumSize.x <= 0 || inFrustumSize.y <= 0)
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
    Texture& texture = GetRenderedTexture();
    texture.Fill(DLColor::BLACK);
    DrawCoordinateSystem(vec2(0.5f,0.5f));
    DrawGrid();
    DrawEdges(true);
    DrawPlayer();
    std::cout << "position "<< position.x << " " << position.y << std::endl;
    texture.SendDataToOpenGl();
}

void TopDownWorldRenderer::DrawPlayer()
{
    World* world = GetWorldToRender();
    if(world == nullptr)
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
    if(world == nullptr)
    {
        std::cerr << "TopDownWorldRenderer::DrawEdges : World to render is null" << std::endl;
        return;
    }
    const std::list<Edge*>&  edges = world->GetEdges();
    for (const Edge* edge : edges)
    {
        const vec2 start = edge->GetStart();
        const vec2 end = edge->GetEnd();
        const ivec2 startScreenPosition = WorldSpaceToScreenSpace(start);
        const ivec2 endScreenPosition = WorldSpaceToScreenSpace(end);
        TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
        textureDrawer.SetBindTexture(&GetRenderedTexture());
        textureDrawer.DrawLine(startScreenPosition, endScreenPosition, DLColor::WHITE);
        if(drawEdges)
        {
            textureDrawer.DrawCircle(startScreenPosition, 3, DLColor::BLUE);
            textureDrawer.DrawCircle(endScreenPosition, 3, DLColor::BLUE);
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
        textureDrawer.DrawLine(WorldSpaceToScreenSpace(vec2(i, -50)), WorldSpaceToScreenSpace(vec2(i, 50)), color);
        textureDrawer.DrawLine(WorldSpaceToScreenSpace(vec2(-50, i)), WorldSpaceToScreenSpace(vec2(50, i)), color);
    }
}

void TopDownWorldRenderer::DrawCoordinateSystem(vec2 position)
{
    TextureDrawer& textureDrawer = TextureDrawer::GetInstance();
    textureDrawer.SetBindTexture(&GetRenderedTexture());
    textureDrawer.DrawLine(WorldSpaceToScreenSpace(position), WorldSpaceToScreenSpace(position + vec2(1, 0)), DLColor::RED);
    textureDrawer.DrawLine(WorldSpaceToScreenSpace(position), WorldSpaceToScreenSpace(position + vec2(0, 1)), DLColor::GREEN);
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
