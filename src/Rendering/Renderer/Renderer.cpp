#include "Renderer.h"

#include "Rendering/Color/DLColor.h"


void Renderer::Init()
{
    renderedTexture.GenerateOpenGlTexture();
}

void Renderer::SetRenderSize(const unsigned width, const unsigned height)
{
    renderWidth = width;
    renderHeight = height;
}

Texture& Renderer::GetRenderedTexture()
{
    return renderedTexture;
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2, DLColor color)
{

}
