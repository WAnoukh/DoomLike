#include "GameRenderer.h"

#include "Rendering/Color/DLColor.h"

void GameRenderer::Render()
{
    Texture& texture = GetRenderedTexture();
    texture.CreateBlankTexture(128,128, GL_RGB);
    texture.Fill(DLColor::RED);
    texture.SendDataToOpenGl();
}

void GameRenderer::Init()
{
    WorldRendererBase::Init();
}
