#include "TopDownWorldRenderer.h"

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
    frustumSize = inFrustumSize;
}

void TopDownWorldRenderer::SetRotation(float inRotation)
{
    rotation = inRotation;
}

void TopDownWorldRenderer::Render()
{
    //TODO: implementer ca
}
