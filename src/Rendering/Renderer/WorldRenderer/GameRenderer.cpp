#include "GameRenderer.h"

#include "Rendering/Color/DLColor.h"
#include "Scene/World/World.h"
#include "Scene/World/Rays/Ray.h"

void GameRenderer::Render()
{
    RenderWorld();
    GetRenderedTexture().SendDataToOpenGl();
}

void GameRenderer::Init()
{
    WorldRendererBase::Init();
    GetRenderedTexture().CreateBlankTexture(180 *10, 128 * 10, GL_RGB);
}

float GameRenderer::GetFov() const
{
    return fov;
}

void GameRenderer::SetFov(float inFov)
{
    fov = inFov;
}

void GameRenderer::RenderWorld()
{
    Texture& renderedTexture = GetRenderedTexture();
    World* worldToRender = GetWorldToRender();
    Entity& player = worldToRender->GetPlayer();
    const std::list<Edge*> edges = worldToRender->GetEdges();
    const int width = renderedTexture.GetWidth();
    const int height = renderedTexture.GetHeight();
    //Raycasting
    for (int column = 0; column < width; column++)
    {
        const float rate = static_cast<float>(column) / static_cast<float>(width) - 0.5f;
        const float rayOrientation = player.GetRotation() - atan(rate * fov);
        const auto ray = Ray(player.GetPosition(), rayOrientation);
        HitResult hitResult;
        if (worldToRender->RayCastOnEdges(ray, hitResult, true))
        {
            float perpDist = hitResult.distance * cos(rayOrientation - player.GetRotation());
            const float lineHeight = 50.0f / perpDist;
            int row = 0;
            const int floorHeight = static_cast<int>((static_cast<float>(height) - lineHeight) / 2);
            const int ceilingHeight = static_cast<int>((static_cast<float>(height) + lineHeight) / 2);
            for (row; row <= floorHeight; row++)
            {
                renderedTexture.EditPixel(column, row, DLColor::BLACK);
            }
            for (row; row <= ceilingHeight; row++)
            {
                renderedTexture.EditPixel(column, row, DLColor::WHITE * (1 / hitResult.distance));
            }
            for (row; row < height; row++)
            {
                renderedTexture.EditPixel(column, row, DLColor::BLACK);
            }
        }
        else
        {
            for (int row = 0; row < renderedTexture.GetHeight(); row++)
            {
                renderedTexture.EditPixel(column, row, DLColor::BLACK);
            }
        }
    }
}
