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
    GetRenderedTexture().CreateBlankTexture(128, 128, GL_RGB);
}

void GameRenderer::RenderWorld()
{
    Texture& renderedTexture = GetRenderedTexture();
    World* worldToRender = GetWorldToRender();
    Entity& player = worldToRender->GetPlayer();
    const std::list<Edge*> edges = worldToRender->GetEdges();
    //Raycasting
    for (int column = 0; column < renderedTexture.GetWidth(); column++)
    {
        const float rayOrientation = player.GetRotation() - ((static_cast<float>(column) / renderedTexture.GetWidth()) - (1.0f / 2.0f)) * fov;
        const auto ray = Ray(player.GetPosition(), rayOrientation);
        HitResult hitResult;
        if (worldToRender->RayCastOnEdges(ray, hitResult, true))
        {
            float perpDist = hitResult.distance * cos(rayOrientation - player.GetRotation());
            float lineHeight = 50 / perpDist;
            for (int row = 0; row < renderedTexture.GetHeight(); row++)
            {
                if (row <= (renderedTexture.GetHeight() - lineHeight) / 2)
                {
                    renderedTexture.EditPixel(column, row, DLColor::BLACK);
                }
                else if (row <= (renderedTexture.GetHeight() + lineHeight) / 2)
                {
                    renderedTexture.EditPixel(column, row, DLColor::WHITE);
                }
                else
                {
                    renderedTexture.EditPixel(column, row, DLColor::BLACK);
                }
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
