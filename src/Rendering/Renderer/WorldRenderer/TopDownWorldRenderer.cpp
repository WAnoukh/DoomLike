#include "TopDownWorldRenderer.h"

#include <iostream>

#include "Rendering/Color/DLColor.h"
#include "Rendering/Textures/Texture.h"
#include "Rendering/Textures/TextureDrawer.h"

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
    DrawPlayer();
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
    textureDrawer.DrawCircle(playerScreenPosition, 6, DLColor::RED);
    textureDrawer.DrawLine(playerScreenPosition, player.GetRotation(), 10, DLColor::YELLOW);
}

vec2 TopDownWorldRenderer::WorldSpaceToScreenSpace(vec2 inPosition)
{
    vec2 screenSpacePosition = inPosition - position;
    screenSpacePosition = screenSpacePosition / frustumSize;
    const Texture& texture = GetRenderedTexture();
    screenSpacePosition += texture.GetSize()/2.0f;
    return screenSpacePosition;
}
