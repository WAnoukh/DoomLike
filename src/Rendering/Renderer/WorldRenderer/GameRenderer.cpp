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
    GetRenderedTexture().CreateBlankTexture(180 * 4, 128 * 4, GL_RGB);
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
    Player& player = worldToRender->GetPlayer();
    const int width = renderedTexture.GetWidth();
    const int height = renderedTexture.GetHeight();
    Texture& wallTexture = *GetWorldToRender()->WallTexture;
    //Raycasting
    for (int column = 0; column < width; column++)
    {
        const float rate = static_cast<float>(column) / static_cast<float>(width) - 0.5f;
        const float rayOrientation = player.GetRotation() - atan(rate * fov);
        const auto ray = Ray(player.GetPosition(), rayOrientation);
        HitResult hitResult;
        if (worldToRender->RayCastOnEdges(ray, hitResult, true))
        {
            const float distToEdgeStart = glm::distance(hitResult.point, hitResult.edge->GetStart());
            float perpDist = hitResult.distance * cos(rayOrientation - player.GetRotation());
            const float lineHeight = 50.0f / perpDist;
            int row = 0;
            const int floorHeight = static_cast<int>((static_cast<float>(height) - lineHeight) / 2);
            const int ceilingHeight = static_cast<int>((static_cast<float>(height) + lineHeight) / 2);
            int floorRow = max(floorHeight, 0);
            for (row; row <= floorRow; row++)
            {
                renderedTexture.EditPixel(column, row, DLRawColor::BLACK);
            }
            int ceilingRow = min(ceilingHeight, height - 1);
            for (row; row <= ceilingRow; row++)
            {
                int x = static_cast<int>((int)(distToEdgeStart*50) % (wallTexture.GetWidth()-1));
                int y = static_cast<int>((row - floorHeight)/(lineHeight) * (wallTexture.GetHeight()-1));
                DLRawColor color = wallTexture.GetPixelColor(x, y);
                color.Divide((1+hitResult.distance));
                renderedTexture.EditPixel(column,row, color);
            }
            for (row; row < height; row++)
            {
                renderedTexture.EditPixel(column, row, DLRawColor::BLACK);
            }
        }
        else
        {
            renderedTexture.EditColumnStrip(column, 0, renderedTexture.GetHeight()-1, DLRawColor::BLACK);
        }
    }
}
