#include "Renderer.h"

#include "Rendering/Color/DLColor.h"


void Renderer::Init()
{
    renderedTexture.GenerateOpenGlTexture();
}

Texture& Renderer::GetRenderedTexture()
{
    return renderedTexture;
}

unsigned Renderer::GetRenderHeight() const
{
    return renderedTexture.GetHeight();
}

unsigned Renderer::GetRenderWidth() const
{
    return renderedTexture.GetHeight();
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2, DLColor color)
{

}
