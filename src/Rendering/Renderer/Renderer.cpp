#include "Renderer.h"

void Renderer::SetRenderSize(unsigned width, unsigned height)
{
    renderWidth = width;
    renderHeight = height;
}

Texture& Renderer::GetRenderedTexture()
{
    return renderedTexture;
}
